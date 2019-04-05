
/*****************************************************************************
 ***** Implementation of Dataset Generation for all four combinations of *****
 *****************************State Action pairs******************************

						 DISCRETE		CONTINUOUS
						 CONTINUOUS		CONTINUOUS
						 CONTINUOUS		DISCRETE
						 DISCRETE		DISCRETE

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "Util.h"
#include "DatasetGenImmediateReinforceController.h"

#include <iostream>
#include <math.h>
#include <time.h>


IOMapping DatasetGenImmediateReinforceController::s_IOMappings[NUM_DATASETS][NUM_TRIALS] = {};

DatasetGenImmediateReinforceController::DatasetGenImmediateReinforceController(NetworkAttributes networkAttributes)
	: SUNAdaptiveController(networkAttributes)
{
}

DatasetGenImmediateReinforceController::~DatasetGenImmediateReinforceController()
{
}

bool DatasetGenImmediateReinforceController::ExecuteTrials(int ds, vector<vector <double>> & rewardData)
{
	bool result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::ComputeReward(vector<double> currOutputs, vector<double> targetOutputs, double & reward)
{
	bool result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::UpdateWeights(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::UpdateSigma(vector<double>	inputs, vector<double> hiddenOutputs, double reward)
{
	bool result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::Backpropagate(vector<double> inputs, vector<double> hiddenOutputs)
{
	bool result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::UpdateMean()
{
	bool result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::SetNoise()
{
	bool result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::SetNetworkSigma()
{
	bool result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::LoadDiscreteContinuousDS(RunType runChoice, EnvType envType)
{
	bool	result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::LoadDataset(RunType runChoice, EnvType envType)
{
	bool		result		=	true;
	int			numInputs	=	IS_BIAS_UNIT ? m_NetworkAttributes.numInputs - 1 : m_NetworkAttributes.numInputs;
	int			numOutputs	=	m_NetworkAttributes.numOutputs;
	Logger *	pLogger		=	nullptr;
	string		lastDirName;
	string		fileName;

	Logger::GetLastDirFileName(runChoice, lastDirName, fileName);

	for (int ds = 0; ds < NUM_DATASETS; ds++)
	{
		Logger::PrepareKinematicsLoggerObject(&pLogger, lastDirName, ds, fileName);

		LoadInputOutputMap(pLogger, numInputs, numOutputs, ds, NUM_TRIALS, IS_BIAS_UNIT);

		Logger::DestructLoggerObject(pLogger);
	}

	return result;
}

bool DatasetGenImmediateReinforceController::LoadContinuousDiscreteDS(RunType runChoice, EnvType envType)
{
	bool	result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::LoadDiscreteDiscreteDS(RunType runChoice, EnvType envType)
{
	bool	result = true;

	return result;
}

bool DatasetGenImmediateReinforceController::GenerateDiscreteContinuousDS(EnvType envType)
{
	bool		result			= true;
	int			numInputs		= IS_BIAS_UNIT ? m_NetworkAttributes.numInputs - 1 : m_NetworkAttributes.numInputs;
	Logger *	pLoggerInputs	= nullptr;
	Logger *	pLoggerOutputs	= nullptr;
	Logger *	pLoggerWeights	= nullptr;

	for (int ds = 0; ds < NUM_DATASETS; ds++)
	{
		if (DEBUG_ON)
		{
			Logger::PrepareDebugLoggerObject(&pLoggerInputs, true, "", ds, FILE_NAME_INPUTS_GEN);
			Logger::PrepareDebugLoggerObject(&pLoggerOutputs, true, "", ds, FILE_NAME_OUTPUTS_GEN);
			Logger::PrepareDebugLoggerObject(&pLoggerWeights, true, "", ds, FILE_NAME_WEIGHTS_GEN);
		}

		SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);

		// Generate Inputs
		//GenerateRandomizedDiscreteInputs(numInputs, NUM_TRIALS);
		GenerateRandomizedDiscreteInputsB(numInputs, NUM_TRIALS);
		if (IS_BIAS_UNIT)
		{
			AddBiasInput();
		}
		AppendMappings(ds, NUM_TRIALS);
		ClearData();
		// Fill in outputs
		for (int trial = 0; trial < NUM_TRIALS; trial++)
		{
			// Just to satisfy the signature
			// Dataset generation doesn't use this vector
			vector<double>	hiddenOutputs;
			
			DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output =
				m_SUNFeedFwdANN.ExecuteStep(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input, m_WeightMatrix, m_NoiseMatrix, m_MatrixSize, hiddenOutputs);

			if (DEBUG_ON)
			{
				pLoggerInputs->WriteVector(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input, to_string(trial));
				pLoggerOutputs->WriteVector(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output, to_string(trial));
				pLoggerWeights->WriteVectors(m_WeightMatrix, to_string(trial));
			}

			if ((trial + 1) == (NUM_TRIALS / 2) && envType == EnvType::eDynamic)
			{
				// Make sure to reset weight half way through the trials
				SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);
			}
		}
		if (DEBUG_ON)
		{
			pLoggerWeights->WriteVectors(m_WeightMatrix, to_string(NUM_TRIALS));

			Logger::DestructLoggerObject(pLoggerInputs);
			Logger::DestructLoggerObject(pLoggerOutputs);
			Logger::DestructLoggerObject(pLoggerWeights);
		}
	}

	return result;
}
bool DatasetGenImmediateReinforceController::GenerateContinuousContinuousDS(EnvType envType)
{
	bool		result			= true;
	int			numInputs		= IS_BIAS_UNIT ? m_NetworkAttributes.numInputs - 1 : m_NetworkAttributes.numInputs;
	Logger *	pLoggerInputs	= nullptr;
	Logger *	pLoggerOutputs	= nullptr;
	Logger *	pLoggerWeights	= nullptr;


	for (int ds = 0; ds < NUM_DATASETS; ds++)
	{
		if (DEBUG_ON)
		{
			Logger::PrepareDebugLoggerObject(&pLoggerInputs, true, "", ds, FILE_NAME_INPUTS_GEN);
			Logger::PrepareDebugLoggerObject(&pLoggerOutputs, true, "", ds, FILE_NAME_OUTPUTS_GEN);
			Logger::PrepareDebugLoggerObject(&pLoggerWeights, true, "", ds, FILE_NAME_WEIGHTS_GEN);
		}

		SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);
	
		// Generate Inputs
		GenerateRandomizedContinuousInputs(numInputs, NUM_TRIALS);
		if (IS_BIAS_UNIT)
		{
			AddBiasInput();
		}
		AppendMappings(ds, NUM_TRIALS);
		ClearData();
		// Fill in outputs
		for (int trial = 0; trial < NUM_TRIALS; trial++)
		{
			// Just to satisfy the signature
			// Dataset generation doesn't use this vector
			vector<double>	hiddenOutputs;

			DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output =
				m_SUNFeedFwdANN.ExecuteStep(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input, m_WeightMatrix, m_NoiseMatrix, m_MatrixSize, hiddenOutputs);

			if (DEBUG_ON)
			{
				pLoggerInputs->WriteVector(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input, to_string(trial));
				pLoggerOutputs->WriteVector(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output, to_string(trial));
				pLoggerWeights->WriteVectors(m_WeightMatrix, to_string(trial));
			}

			if ((trial + 1) == (NUM_TRIALS / 2) && envType == EnvType::eDynamic)
			{
				// Make sure to reset weight half way through the trials
				SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);
			}
		}
		if (DEBUG_ON)
		{
			pLoggerWeights->WriteVectors(m_WeightMatrix, to_string(NUM_TRIALS));

			Logger::DestructLoggerObject(pLoggerInputs);
			Logger::DestructLoggerObject(pLoggerOutputs);
			Logger::DestructLoggerObject(pLoggerWeights);
		}
	}

	return result;
}
bool DatasetGenImmediateReinforceController::GenerateContinuousDiscreteDS(EnvType envType)
{
	bool		result			= true;
	int			numInputs		= IS_BIAS_UNIT ? m_NetworkAttributes.numInputs - 1 : m_NetworkAttributes.numInputs;
	Logger *	pLoggerInputs	= nullptr;
	Logger *	pLoggerOutputs	= nullptr;
	Logger *	pLoggerWeights	= nullptr;

	for (int ds = 0; ds < NUM_DATASETS; ds++)
	{
		if (DEBUG_ON)
		{
			Logger::PrepareDebugLoggerObject(&pLoggerInputs, true, "", ds, FILE_NAME_INPUTS_GEN);
			Logger::PrepareDebugLoggerObject(&pLoggerOutputs, true, "", ds, FILE_NAME_OUTPUTS_GEN);
			Logger::PrepareDebugLoggerObject(&pLoggerWeights, true, "", ds, FILE_NAME_WEIGHTS_GEN);
		}

		SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);

		// Generate Inputs
		GenerateRandomizedContinuousInputs(numInputs, NUM_TRIALS);
		if (IS_BIAS_UNIT)
		{
			AddBiasInput();
		}
		AppendMappings(ds, NUM_TRIALS);
		ClearData();
		// Fill in outputs
		for (int trial = 0; trial < NUM_TRIALS; trial++)
		{
			// Just to satisfy the signature
			// Dataset generation doesn't use this vector
			vector<double>	hiddenOutputs;

			DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output =
				m_SUNFeedFwdANN.ExecuteStep(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input, m_WeightMatrix, m_NoiseMatrix, m_MatrixSize, hiddenOutputs);

			if (DEBUG_ON)
			{
				pLoggerInputs->WriteVector(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input, to_string(trial));
				pLoggerOutputs->WriteVector(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output, to_string(trial));
				pLoggerWeights->WriteVectors(m_WeightMatrix, to_string(trial));
			}

			if ((trial + 1) == (NUM_TRIALS / 2) && envType == EnvType::eDynamic)
			{
				// Make sure to reset weight half way through the trials
				SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);
			}
		}
		if (DEBUG_ON)
		{
			pLoggerWeights->WriteVectors(m_WeightMatrix, to_string(NUM_TRIALS));

			Logger::DestructLoggerObject(pLoggerInputs);
			Logger::DestructLoggerObject(pLoggerOutputs);
			Logger::DestructLoggerObject(pLoggerWeights);
		}
	}

	return result;
}
bool DatasetGenImmediateReinforceController::GenerateDiscreteDiscreteDS(EnvType envType)
{
	bool		result			= true;
	int			numInputs		= IS_BIAS_UNIT ? m_NetworkAttributes.numInputs - 1 : m_NetworkAttributes.numInputs;
	Logger *	pLoggerInputs	= nullptr;
	Logger *	pLoggerOutputs	= nullptr;
	Logger *	pLoggerWeights	= nullptr;

	for (int ds = 0; ds < NUM_DATASETS; ds++)
	{
		if (DEBUG_ON)
		{
			Logger::PrepareDebugLoggerObject(&pLoggerInputs, true, "", ds, FILE_NAME_INPUTS_GEN);
			Logger::PrepareDebugLoggerObject(&pLoggerOutputs, true, "", ds, FILE_NAME_OUTPUTS_GEN);
			Logger::PrepareDebugLoggerObject(&pLoggerWeights, true, "", ds, FILE_NAME_WEIGHTS_GEN);
		}

		SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);

		// Generate Inputs
		//GenerateRandomizedDiscreteInputs(numInputs, NUM_TRIALS);
		GenerateRandomizedDiscreteInputsB(numInputs, NUM_TRIALS);
		if (IS_BIAS_UNIT)
		{
			AddBiasInput();
		}
		AppendMappings(ds, NUM_TRIALS);
		ClearData();
		// Fill in outputs
		for (int trial = 0; trial < NUM_TRIALS; trial++)
		{
			// Just to satisfy the signature
			// Dataset generation doesn't use this vector
			vector<double>	hiddenOutputs;

			DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output =
				m_SUNFeedFwdANN.ExecuteStep(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input, m_WeightMatrix, m_NoiseMatrix, m_MatrixSize, hiddenOutputs);

			if (DEBUG_ON)
			{
				pLoggerInputs->WriteVector(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input, to_string(trial));
				pLoggerOutputs->WriteVector(DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output, to_string(trial));
				pLoggerWeights->WriteVectors(m_WeightMatrix, to_string(trial));
			}

			if ((trial + 1) == (NUM_TRIALS / 2) && envType == EnvType::eDynamic)
			{
				// Make sure to reset weight half way through the trials
				SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);
			}
		}
		if (DEBUG_ON)
		{
			pLoggerWeights->WriteVectors(m_WeightMatrix, to_string(NUM_TRIALS));

			Logger::DestructLoggerObject(pLoggerInputs);
			Logger::DestructLoggerObject(pLoggerOutputs);
			Logger::DestructLoggerObject(pLoggerWeights);
		}
	}

	return result;
}

bool DatasetGenImmediateReinforceController::LoadInputOutputMap(Logger * pLogger, int numInputs, int numOutputs, int ds, int numTrials, bool isBiasUnit)
{
	bool			result = true;
	vector<double>	input;
	vector<double>	output;
	vector<double>	trialData;

	assert(pLogger != nullptr);

	if (numInputs < 1 || numOutputs < 1 || numTrials < 1 || ds < 0)
		return false;

	for (int trial = 0; trial < numTrials; trial++)
	{
		trialData.clear();
		input.clear();
		output.clear();

		pLogger->ReadVector(trialData);
		// Make sure we trial num from file
		// matched the one we are reading in
		assert(trialData[0] == trial);

		int cursor = 1;
		for (int i = 0; i < numInputs; i++)
		{
			input.push_back(trialData[cursor]);
			cursor++;
		}
		if (isBiasUnit)
		{
			input.push_back(1);
		}
		for (int i = 0; i < numOutputs; i++)
		{
			output.push_back(trialData[cursor]);
			cursor++;
		}

		DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].input	= input;
		DatasetGenImmediateReinforceController::s_IOMappings[ds][trial].output	= output;
	}

	return result;
}

// This method ensures all discrete inputs are sampled
// but is inefficient for large number of inputs
bool DatasetGenImmediateReinforceController::GenerateRandomizedDiscreteInputs(int numInputs, int numTrials)
{
	bool					result	= true;
	int						pos;
	vector<vector<double>>	discreteInputs;

	if (numInputs < 1 || numTrials < 1)
		return false;

	pos = static_cast<int>(pow(2, numInputs));
	if (GenerateDiscreteInputs(numInputs, discreteInputs))
	{
		vector<double>	input;

		for (int t = 0; t < numTrials; t++)
		{
			input = discreteInputs.at(Util::getUniformRandomI(0, pos-1));
			m_NetworkInputs.push_back(input);
		}
	}

	return result;
}

// This method does not guarentee all discrete inputs are sampled
// but is efficient for large number of inputs.
// It is more similar to GenerateRandomizedContinuousInputs
bool DatasetGenImmediateReinforceController::GenerateRandomizedDiscreteInputsB(int numInputs, int numTrials)
{
	bool			result = true;
	vector<double>	input;

	if (numInputs < 1 || numTrials < 1)
		return false;

	for (int t = 0; t < numTrials; t++)
	{
		input.clear();
		for (int i = 0; i < numInputs; i++)
		{
			input.push_back(Util::getUniformRandomI(DISC_INPUT_LOWLMT, DISC_INPUT_UPLMT));
		}
		m_NetworkInputs.push_back(input);
	}

	return result;
}

bool DatasetGenImmediateReinforceController::GenerateRandomizedContinuousInputs(int numInputs, int numTrials)
{
	bool			result = true;
	vector<double>	input;

	if (numInputs < 1 || numTrials < 1)
		return false;

	for (int t = 0; t < numTrials; t++)
	{
		input.clear();
		for (int i = 0; i < numInputs; i++)
		{
			input.push_back(Util::roundDecimal(Util::getUniformRandom(CONT_INPUT_LOWLMT, CONT_INPUT_UPLMT), CONT_INPUT_DCML_PLACES));
		}
		m_NetworkInputs.push_back(input);
	}

	return result;
}

bool DatasetGenImmediateReinforceController::GenerateDiscreteInputs(int numInputs, vector<vector<double>> & discreteInputs)
{
	bool	result = true;
	int		pos;

	if (numInputs < 1)
		return false;

	discreteInputs.clear();
	pos = static_cast<int>(pow(2, numInputs));
	for (int i = 0; i < pos; i++)
	{
		vector<double> binary;
		if (GetBin(i, numInputs, binary))
		{
			discreteInputs.push_back(binary);
		}
	}

	return result;
}

bool DatasetGenImmediateReinforceController::GetBin(int number, int numDigits, vector<double> & binary)
{
	bool			result		= true;
	vector<double>	bin;
	int				quo			= 0;
	int				rem			= 0;
	int				remDigits	= numDigits;

	if (number < 0 || numDigits < 1)
		return false;

	quo = number;
	while (quo > 1)
	{
		rem = quo % 2;
		quo = quo / 2;

		bin.push_back(rem);
		remDigits--;
	}
	bin.push_back(quo);
	for (int i = remDigits-1; i > 0; i--)
	{
		bin.push_back(0);
	}
	std::reverse(bin.begin(), bin.end());

	binary = bin;

	return result;
}

bool DatasetGenImmediateReinforceController::ClearData()
{
	bool	result = true;

	m_NetworkInputs.clear();

	return result;
}

bool DatasetGenImmediateReinforceController::AppendMappings(int datasetIndex, int numTrials)
{
	bool	result = true;

	for (int trial = 0; trial < numTrials; trial++)
	{
		s_IOMappings[datasetIndex][trial].input = m_NetworkInputs[trial];
	}
	//cout << "Dataset: " << datasetIndex << endl;
	//Print();

	return result;
}

bool DatasetGenImmediateReinforceController::SetNoise(double noiseVal)
{
	bool result = true;


	return result;
}

bool DatasetGenImmediateReinforceController::AddBiasInput()
{
	bool result = true;

	for (int trial = 0; trial < m_NetworkInputs.size(); trial++)
	{
		m_NetworkInputs[trial].push_back(1);
	}

	return result;
}

// Debugging Methods

void DatasetGenImmediateReinforceController::Print()
{
	//cout << "Inputs" << endl;
	for (int i = 0; i < m_NetworkInputs.size(); i++)
	{
		vector<double> v = m_NetworkInputs[i];
		cout << i + 1 << ": ";
		for (int j = 0; j < v.size(); j++)
		{
			cout << v[j] << " ";
		}
		cout << endl;
	}
}

