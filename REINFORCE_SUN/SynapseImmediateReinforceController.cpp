
/*****************************************************************************
******************************************************************************

	Implementation for SUN[Synapse]ImmediateReinforceController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "SynapseImmediateReinforceController.h"

SynapseImmediateReinforceController::SynapseImmediateReinforceController(NetworkAttributes networkAttributes)
	: SUNImmediateReinforceController(networkAttributes)
{
	m_DirName	= DIR_STOCH_SYNP;

	SetNoise();
}
SynapseImmediateReinforceController ::~SynapseImmediateReinforceController()
{
}
	
bool SynapseImmediateReinforceController::UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool		result					= true;
	int			firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;
	double *	translatedInputs		= nullptr;
	bool		isHiddenLayer			= m_NetworkAttributes.numHiddenLayers > 0;

	translatedInputs = isHiddenLayer ?
		&hiddenOutputs[firstOutputUnitIndex - m_NetworkAttributes.numHiddenUnitsPerLayer]
		:
		&inputs[0];

	// Compute Delta_W for the synapses between
	// the output layer and the translatedInput layer where
	// translatedInput layer can be either input or the 
	// hidden layers outputs
	for (unsigned int j = 0; j < m_NetworkAttributes.numOutputs; j++)
	{
		vector<double> &	neuronSigmas	= m_StdDevMatrix[firstOutputUnitIndex	+ j];
		vector<double>		neuronNoises	= m_NoiseMatrix[firstOutputUnitIndex	+ j];

		assert(neuronSigmas.size() == neuronNoises.size());

		for (unsigned int k = 0; k < neuronSigmas.size(); k++)
		{
			// REINFORCE~SUN complete Equation
			//neuronSigmas[k] += LEARN_RATE_SIGMA * pow(neuronSigmas[k], 2) * (reward - m_AvgReward) * ((pow(neuronNoises[k], 2) - pow(neuronSigmas[k], 2)) / pow(neuronSigmas[k], 3));
			if (neuronSigmas[k] > 0)
			{
				// REINFORCE~SUN Equation
				// neuronSigmas[k] += LEARN_RATE_SIGMA * (reward - m_AvgReward) * ((pow(neuronNoises[k], 2) - pow(neuronSigmas[k], 2)) / neuronSigmas[k]);

				// SSRL
				neuronSigmas[k] +=	LEARN_RATE_SIGMA * (reward - m_AvgReward) * translatedInputs[k] * (abs(neuronNoises[k]) - LEARN_CUTOFF_SIGMA * neuronSigmas[k]);
			}
			
			// Cap sigma if it comes out to be out of expected range
			neuronSigmas[k] =	neuronSigmas[k] < SIGMA_LOW_CAP ? SIGMA_LOW_CAP : neuronSigmas[k];
			//neuronSigmas[k] =	neuronSigmas[k] > SIGMA_UPP_CAP ? SIGMA_UPP_CAP : neuronSigmas[k];
		}
	}

	return result;
}

bool SynapseImmediateReinforceController::SetNoise()
{
	bool	result					= true;
	int		firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;

	// Only set Noise for the Synapses between
	// the Output and the last Hidden layer
	for (int i = 0; i < m_NetworkAttributes.numOutputs; i++)
	{
		vector<double> outputUnitMeans		= m_MeanMatrix[firstOutputUnitIndex + i];
		vector<double> outputUnitSigmas		= m_StdDevMatrix[firstOutputUnitIndex + i];
		vector<double> & outputUnitNoises	= m_NoiseMatrix[firstOutputUnitIndex + i];

		assert(outputUnitMeans.size() == outputUnitSigmas.size());
		assert(outputUnitSigmas.size() == outputUnitNoises.size());

		for (unsigned int j = 0; j < outputUnitNoises.size(); j++)
		{
			// Set sampled noise on the synapse
			outputUnitNoises[j] = GetSampledNoise(outputUnitMeans[j], outputUnitSigmas[j]);
		}
	}

	return result;
}

bool SynapseImmediateReinforceController::SetNetworkSigma()
{
	bool result = true;

	return result;
}
