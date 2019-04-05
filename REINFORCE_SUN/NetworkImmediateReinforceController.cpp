
/*****************************************************************************
******************************************************************************

	Implementation for SUN[Network]ImmediateReinforceController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "NetworkImmediateReinforceController.h"

NetworkImmediateReinforceController::NetworkImmediateReinforceController(NetworkAttributes networkAttributes)
	: SUNImmediateReinforceController(networkAttributes)
{
	m_DirName = DIR_STOCH_NETW;

	SetNetworkSigma();
	SetNoise();
}
NetworkImmediateReinforceController ::~NetworkImmediateReinforceController()
{
}

bool NetworkImmediateReinforceController::UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool			result					= true;
	unsigned int	firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;
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

	// REINFORCE~SUN complete Equation
	//double	sigmaChange = LEARN_RATE_SIGMA * pow(m_StdDevMatrix[firstOutputUnitIndex][0], 2) * (reward - m_AvgReward) * ((pow(m_NoiseMatrix[firstOutputUnitIndex][0], 2) - pow(m_StdDevMatrix[firstOutputUnitIndex][0], 2)) / pow(m_StdDevMatrix[firstOutputUnitIndex][0], 3));
	double	sigmaChange = 0;
	if (m_StdDevMatrix[firstOutputUnitIndex][0] > 0)
	{
		// REINFORCE~SUN Equation
		//sigmaChange = LEARN_RATE_SIGMA * (reward - m_AvgReward) * ((pow(m_NoiseMatrix[firstOutputUnitIndex][0], 2) - pow(m_StdDevMatrix[firstOutputUnitIndex][0], 2)) / m_StdDevMatrix[firstOutputUnitIndex][0]);

		// SSRL
		// \eta_{ \sigma } (r - \overline{ r }) (\overline{ y_{K} } (\lvert \epsilon_{ j } \rvert - \sigma_{ j }))
		sigmaChange = LEARN_RATE_SIGMA * (reward - m_AvgReward) * avgInputs * (abs(m_NoiseMatrix[firstOutputUnitIndex][0]) - LEARN_CUTOFF_SIGMA * m_StdDevMatrix[firstOutputUnitIndex][0]);
	}

	// Add the same sigma value to the entire network
	for (unsigned int j = 0; j < m_NetworkAttributes.numOutputs; j++)
	{
		vector<double> &	neuronSigmas = m_StdDevMatrix[firstOutputUnitIndex + j];

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
bool NetworkImmediateReinforceController::SetNoise()
{
	bool	result					= true;
	// Only set Noise for the Synapses between
	// the Output and the last Hidden layer
	int		firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;

	// Since the noise should be same for the entire network,
	// computing noise for the first synapse and setting it 
	// on the entire network.
	double unitSampledNoise = GetSampledNoise(m_MeanMatrix[firstOutputUnitIndex][0], m_StdDevMatrix[firstOutputUnitIndex][0]);

	for (int i = 0; i < m_NetworkAttributes.numOutputs; i++)
	{
		vector<double> & outputUnitNoises	= m_NoiseMatrix[firstOutputUnitIndex + i];

		SetUnitValue(outputUnitNoises, unitSampledNoise);
	}

	return result;
}

bool NetworkImmediateReinforceController::SetNetworkSigma()
{
	bool	result					= true;
	// Only set Sigma for the Synapses between
	// the Output and the last Hidden layer
	int		firstOutputUnitIndex	= m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer;
	double	networkValue			= m_StdDevMatrix[firstOutputUnitIndex][0];

	for (int i = 0; i < m_NetworkAttributes.numOutputs; i++)
	{
		vector<double> &	outputUnitSigmas = m_StdDevMatrix[firstOutputUnitIndex + i];

		// Since the Sigma should be same for the entire network,
		// getting Sigma from the first synapse and setting it 
		// on the entire network.
		SetUnitValue(outputUnitSigmas, networkValue);
	}

	return result;
}
