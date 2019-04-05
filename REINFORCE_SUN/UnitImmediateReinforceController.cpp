
/*****************************************************************************
******************************************************************************

	Implementation for SUN[Unit]ImmediateReinforceController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "UnitImmediateReinforceController.h"

UnitImmediateReinforceController::UnitImmediateReinforceController(NetworkAttributes networkAttributes)
	: SUNImmediateReinforceController(networkAttributes)
{
	m_DirName = DIR_STOCH_UNIT;

	SetNetworkSigma();
	SetNoise();
}
UnitImmediateReinforceController ::~UnitImmediateReinforceController()
{
}

bool UnitImmediateReinforceController::UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool			result					= true;
	int				firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;
	double *		translatedInputs		= nullptr;
	unsigned int	translatedInputsSize	= 0;
	bool			isHiddenLayer			= m_NetworkAttributes.numHiddenLayers > 0;

	translatedInputs = isHiddenLayer ?
		&hiddenOutputs[firstOutputUnitIndex - m_NetworkAttributes.numHiddenUnitsPerLayer]
		:
		&inputs[0];

	translatedInputsSize = isHiddenLayer ? m_NetworkAttributes.numHiddenUnitsPerLayer : inputs.size();

	// Delta_{\sigma_{ j }} =
	//	\eta_{ \sigma } (r - \overline{ r }) (\overline{ y_{K} } (\lvert \epsilon_{ j } \rvert - \sigma_{ j }))

	//	\overline{ y_{K} }
	double avgInputs = 0.0;
	for (unsigned int k = 0; k < translatedInputsSize; k++)
	{
		avgInputs += translatedInputs[k];
	}
	avgInputs /= translatedInputsSize;


	for (unsigned int j = 0; j < m_NetworkAttributes.numOutputs; j++)
	{
		vector<double> &	neuronSigmas	= m_StdDevMatrix[firstOutputUnitIndex	+ j];
		vector<double>		neuronNoises	= m_NoiseMatrix[firstOutputUnitIndex	+ j];

		// REINFORCE~SUN complete Equation
		//double	sigmaChange = LEARN_RATE_SIGMA * pow(neuronSigmas[0], 2) * (reward - m_AvgReward) * ((pow(neuronNoises[0], 2) - pow(neuronSigmas[0], 2)) / pow(neuronSigmas[0], 3));
		double	sigmaChange = 0;
		if (neuronSigmas[0] > 0)
		{
			// REINFORCE~SUN Equation
			// sigmaChange = LEARN_RATE_SIGMA * (reward - m_AvgReward) * ((pow(neuronNoises[0], 2) - pow(neuronSigmas[0], 2)) / neuronSigmas[0]);

			// SSRL
			// \eta_{ \sigma } (r - \overline{ r }) (\overline{ y_{K} } (\lvert \epsilon_{ j } \rvert - \sigma_{ j }))
			sigmaChange = LEARN_RATE_SIGMA * (reward - m_AvgReward) * avgInputs * (abs(neuronNoises[0]) - LEARN_CUTOFF_SIGMA * neuronSigmas[0]);
		}

		assert(neuronSigmas.size() == neuronNoises.size());

		// Add the same sigma value to the entire unit
		for (unsigned int k = 0; k < neuronSigmas.size(); k++)
		{
			neuronSigmas[k] += sigmaChange;
			// Cap sigma if it comes out to be out of expected range
			neuronSigmas[k] = neuronSigmas[k] < SIGMA_LOW_CAP ? SIGMA_LOW_CAP : neuronSigmas[k];
			//neuronSigmas[k] = neuronSigmas[k] > SIGMA_UPP_CAP ? SIGMA_UPP_CAP : neuronSigmas[k];
		}
	}

	return result;
}

bool UnitImmediateReinforceController::SetNoise()
{
	bool	result					= true;
	// Only set Noise for the Synapses between
	// the Output and the last Hidden layer
	int		firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;

	for (int i = 0; i < m_NetworkAttributes.numOutputs; i++)
	{
		vector<double> outputUnitMeans		= m_MeanMatrix[firstOutputUnitIndex		+ i];
		vector<double> outputUnitSigmas		= m_StdDevMatrix[firstOutputUnitIndex	+ i];
		vector<double> & outputUnitNoises	= m_NoiseMatrix[firstOutputUnitIndex	+ i];

		assert(outputUnitMeans.size() == outputUnitSigmas.size());
		assert(outputUnitSigmas.size() == outputUnitNoises.size());

		// Since the noise should be same for the entire unit,
		// computing noise for the first synapse and using it 
		// for the entire unit as all synapses for this unit
		// share the same Sigma and Mean values.
		double unitSampledNoise = GetSampledNoise(outputUnitMeans[0], outputUnitSigmas[0]);

		SetUnitValue(outputUnitNoises, unitSampledNoise);
	}

	return result;
}

bool UnitImmediateReinforceController::SetNetworkSigma()
{
	bool	result					= true;
	// Only set Sigma for the Synapses between
	// the Output and the last Hidden layer
	int		firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;

	for (int i = 0; i < m_NetworkAttributes.numOutputs; i++)
	{
		vector<double> &	outputUnitSigmas	= m_StdDevMatrix[firstOutputUnitIndex + i];
		double				unitValue			= m_StdDevMatrix[firstOutputUnitIndex + i][0];

		// Since the Sigma should be same for the entire unit,
		// getting Sigma from the first synapse and setting it 
		// on the entire unit as all synapses for this unit
		// should share the same Sigma and Mean values.
		SetUnitValue(outputUnitSigmas, unitValue);
	}

	return result;
}