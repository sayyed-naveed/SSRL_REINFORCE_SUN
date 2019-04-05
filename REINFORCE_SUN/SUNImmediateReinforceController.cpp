
/*****************************************************************************
******************************************************************************

Implementation for SUN[Synapse, Unit, Network]ImmediateReinforceController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "Logger.h"
#include "Util.h"
#include "SUNImmediateReinforceController.h"
#include "DatasetGenImmediateReinforceController.h"

SUNImmediateReinforceController::SUNImmediateReinforceController(NetworkAttributes networkAttributes)
	: SUNAdaptiveController(networkAttributes)
{
	double initValue = 0.0;

	SUNAdaptiveController::ConstructMatrix(m_StdDevMatrix, initValue, networkAttributes);
	SUNAdaptiveController::ConstructMatrix(m_MeanMatrix, initValue, networkAttributes);

	SUNAdaptiveController::RandomInitMatrix(SIGMA_LOW_CAP, SIGMA_UPP_CAP, m_StdDevMatrix);
	SUNAdaptiveController::SetMatrix(m_MeanMatrix, initValue);
}
SUNImmediateReinforceController ::~SUNImmediateReinforceController()
{
}

bool SUNImmediateReinforceController::ExecuteTrials(int ds, vector<vector <double>> & rewardData)
{
	bool			result	= true;
	double			reward	= 0.0;
	vector <double>	allRewards;
	vector <double>	allAvgRewards;
	Logger			loggerWeight;
	Logger			loggerSigma;
	Logger			loggerNoise;
	Logger			loggerOutputs;

	rewardData.clear();

	ds > 0 ? ResetDataMembers() : 0;

	if (DEBUG_ON)
	{
		string	finalDirPath;
		string	finalFileName;

		Logger::ConstructFullDebugDirFilePaths(finalDirPath, finalFileName, false, m_DirName, to_string(ds), FILE_NAME_WEIGHTS);
		loggerWeight.EnsureDirAndFile(finalDirPath, finalDirPath + finalFileName);

		finalDirPath.clear();
		finalFileName.clear();
		Logger::ConstructFullDebugDirFilePaths(finalDirPath, finalFileName, false, m_DirName, to_string(ds), FILE_NAME_SIGMA);
		loggerSigma.EnsureDirAndFile(finalDirPath, finalDirPath + finalFileName);

		finalDirPath.clear();
		finalFileName.clear();
		Logger::ConstructFullDebugDirFilePaths(finalDirPath, finalFileName, false, m_DirName, to_string(ds), FILE_NAME_NOISE);
		loggerNoise.EnsureDirAndFile(finalDirPath, finalDirPath + finalFileName);

		finalDirPath.clear();
		finalFileName.clear();
		Logger::ConstructFullDebugDirFilePaths(finalDirPath, finalFileName, false, m_DirName, to_string(ds), FILE_NAME_OUTPUTS);
		loggerOutputs.EnsureDirAndFile(finalDirPath, finalDirPath + finalFileName);
	}

	for (unsigned int trial = 0; trial < NUM_TRIALS; trial++)
	{
		if (DEBUG_ON)
		{
			loggerWeight.WriteVectors(m_WeightMatrix, to_string(trial));
			loggerSigma.WriteVectors(m_StdDevMatrix, to_string(trial));
			loggerNoise.WriteVectors(m_NoiseMatrix, to_string(trial));
		}

		vector<double>	inputs			= DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input;
		vector<double>	targetOutputs	= DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output;
		vector<double>	hiddenOutputs;

		// Execute ANN step
		vector<double> currOutputs = m_SUNFeedFwdANN.ExecuteStep(inputs, m_WeightMatrix, m_NoiseMatrix, m_MatrixSize, hiddenOutputs);
		// Compute Reward
		ComputeReward(currOutputs, targetOutputs, reward);
		m_CummReward += reward;
		// Update Weights
		UpdateWeights(inputs, hiddenOutputs, reward);
		// Update Sigma
		UpdateSigma(inputs, hiddenOutputs, reward);
		// Set Noise
		SetNoise();
		// Recompute Average Reward for the next trial
		//m_AvgReward = m_CummReward / (trial + 1);
		m_AvgReward = REWARD_DISCOUNT_FACTOR * reward + (1 - REWARD_DISCOUNT_FACTOR) * m_AvgReward;

		// Load reward Data for FILE IO
		allRewards.push_back(Util::roundDecimal(reward, RAND_DCML_PLACES));
		allAvgRewards.push_back(Util::roundDecimal(m_AvgReward, RAND_DCML_PLACES));
		
		if (DEBUG_ON)
		{
			loggerOutputs.WriteVector(currOutputs, to_string(trial));
		}

	}
	rewardData.push_back(allRewards);
	rewardData.push_back(allAvgRewards);
	rewardData.push_back({ Util::roundDecimal(m_CummReward, RAND_DCML_PLACES) });

	if (DEBUG_ON)
	{
		loggerWeight.WriteVectors(m_WeightMatrix, to_string(NUM_TRIALS));
		loggerSigma.WriteVectors(m_StdDevMatrix, to_string(NUM_TRIALS));
		loggerNoise.WriteVectors(m_NoiseMatrix, to_string(NUM_TRIALS));
	}

	return result;
}

bool SUNImmediateReinforceController::ComputeReward(vector<double> currOutputs, vector<double> targetOutputs, double & reward)
{
	bool	result		= true;
	int		outputCount	= currOutputs.size();

	assert(currOutputs.size() == targetOutputs.size());

	reward = 0.0;
	for (unsigned int j = 0; j < outputCount; j++)
	{
		reward += abs(targetOutputs[j] - currOutputs[j]);
	}

	reward = 1 - (reward / outputCount);

	return result;
}

bool SUNImmediateReinforceController::UpdateWeights(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool			result					= true;
	unsigned int	firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;
	double *		translatedInputs		= nullptr;
	bool			isHiddenLayer			= m_NetworkAttributes.numHiddenLayers > 0;

	SUNAdaptiveController::SetMatrix(m_WeightUpdateMatrix, 0.0);

	translatedInputs = isHiddenLayer ?
		&hiddenOutputs[(m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer) - m_NetworkAttributes.numHiddenUnitsPerLayer]
		:
		&inputs[0];

	// Compute Delta_W for the synapses between
	// the output layer and the translatedInput layer where
	// translatedInput layer can be either input or the 
	// hidden layers outputs
	for (unsigned int j = 0; j < m_NetworkAttributes.numOutputs; j++)
	{
		vector<double> &	neuronWeightUpdates	= m_WeightUpdateMatrix[m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer + j];
		vector<double>		neuronNoises		= m_NoiseMatrix[m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer + j];
		vector<double>		neuronSigma			= m_StdDevMatrix[m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer + j];

		assert(neuronWeightUpdates.size() == neuronNoises.size());

		for (unsigned int k = 0; k < neuronWeightUpdates.size(); k++)
		{
			// REINFORCE~SUN Equation
			//neuronWeightUpdates[k] = (reward - m_AvgReward) * (neuronNoises[k]); // / pow(neuronSigma[k], 2));
			
			// SSRL
			neuronWeightUpdates[k] = (reward - m_AvgReward) * translatedInputs[k] * neuronNoises[k];
		}
	}
	
	// If hidden layers are there Backpropagate
	if (isHiddenLayer)
	{
		Backpropagate(inputs, hiddenOutputs);
	}
	
	// Update all Weights now

	for (int i = 0; i < m_WeightMatrix.size(); i++)
	{
		double learningRate = i >= firstOutputUnitIndex ? LEARN_RATE_W : LEARN_RATE_NU;

		for (int j = 0; j < m_WeightMatrix[i].size(); j++)
		{
			m_WeightMatrix[i][j] += (learningRate * m_WeightUpdateMatrix[i][j]);
		}
	}

	return result;
}

bool SUNImmediateReinforceController::Backpropagate(vector<double> inputs, vector<double> hiddenOutputs)
{
	bool result = true;

	// Delta_{v_{ik}} = \sum_{j=1}^{J}(\delta_{w_{kj}}w_{kj})y_{k}(1-y_{k})x_{i}

	for (int i = 0; i < m_NetworkAttributes.numHiddenLayers; i++)
	{
		unsigned int currHiddenLayerFirstUnitIndex = (m_NetworkAttributes.numHiddenLayers - (i + 1)) * m_NetworkAttributes.numHiddenUnitsPerLayer;

		for (int j = 0; j < m_NetworkAttributes.numHiddenUnitsPerLayer; j++)
		{
			double			derivativeWeightSum = 0.0;
			unsigned int	nextLayerNumUnits = (i == 0) ? m_NetworkAttributes.numOutputs : m_NetworkAttributes.numHiddenUnitsPerLayer;
			unsigned int	nextLayerUnitIndex = currHiddenLayerFirstUnitIndex + m_NetworkAttributes.numHiddenUnitsPerLayer;

			// \sum_{j=1}^{J}(\delta_{w_{kj}}w_{kj})
			for (unsigned int k = 0; k < nextLayerNumUnits; k++)
			{
				derivativeWeightSum += m_WeightUpdateMatrix[nextLayerUnitIndex + k][j] * m_WeightMatrix[nextLayerUnitIndex + k][j];
			}
			unsigned int prevLayerNumUnits = (i + 1) == m_NetworkAttributes.numHiddenLayers ?
				inputs.size()
				:
				m_NetworkAttributes.numHiddenUnitsPerLayer;
			double * prevLayerInputs = (i + 1) == m_NetworkAttributes.numHiddenLayers ?
				&inputs[0]
				:
				&hiddenOutputs[currHiddenLayerFirstUnitIndex - m_NetworkAttributes.numHiddenUnitsPerLayer];
			for (unsigned int k = 0; k < prevLayerNumUnits; k++)
			{
				// y_{ k }(1 - y_{ k })x_ { i }
				m_WeightUpdateMatrix[j][k] = derivativeWeightSum * hiddenOutputs[currHiddenLayerFirstUnitIndex + j] * (1 - hiddenOutputs[currHiddenLayerFirstUnitIndex + j]) * prevLayerInputs[k];
			}
		}
	}

	return result;
}

bool SUNImmediateReinforceController::UpdateMean()
{
	bool result = true;

	return result;
}
