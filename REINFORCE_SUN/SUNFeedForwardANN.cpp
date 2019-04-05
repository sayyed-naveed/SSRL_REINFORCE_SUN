
/*****************************************************************************
******************************************************************************

		Implementation for SUN[Synapse, Unit, Network]FeedForwardANN

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "SUNFeedForwardANN.h"

#include<iostream>

SUNFeedForwardANN::SUNFeedForwardANN(NetworkAttributes networkAttributes)
	: FeedForwardANN(networkAttributes)
{
}
SUNFeedForwardANN ::~SUNFeedForwardANN()
{
}

vector<double> SUNFeedForwardANN::ExecuteStep(vector<double> inputs, vector<vector<double>> weightsMatrix, vector<vector<double>> noiseMatrix, int matrixSize, vector<double> & hiddenOutputs)
{
	vector<double>	outputs;

	if (m_WeightMatrixSize != matrixSize)
	{
		cout << "ERROR: Matrix size is not appropriate!" << endl;
		return outputs;
	}

	hiddenOutputs.clear();

	//hidden layer output
	for (int i = 0; i < m_NetworkAttributes.numHiddenLayers; i++)
	{
		for (int j = 0; j < m_NetworkAttributes.numHiddenUnitsPerLayer; j++)
		{
			double netValue					= 0;
			vector<double> neuronWeights	= weightsMatrix[i * m_NetworkAttributes.numHiddenUnitsPerLayer + j];

			for (unsigned int k = 0; k < neuronWeights.size(); k++)
			{
				netValue += neuronWeights[k] * inputs[k];
			}
			netValue = netValue / inputs.size();

			double output = ActivateValue(netValue, m_NetworkAttributes.hiddenActvFunction);
			outputs.push_back(output);
			// Maintain a list of all the hidden outputs
			// This is required for the update equations
			hiddenOutputs.push_back(output);
		}
		inputs.clear();
		inputs = outputs;
		outputs.clear();
	}

	//output layer
	for (int i = 0; i < m_NetworkAttributes.numOutputs; i++)
	{
		double netValue					= 0;
		vector<double> neuronWeights	= weightsMatrix[m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer + i];
		vector<double> synapseNoise		= noiseMatrix[m_NetworkAttributes.numHiddenLayers * m_NetworkAttributes.numHiddenUnitsPerLayer + i];

		assert(neuronWeights.size() == synapseNoise.size());

		for (unsigned int j = 0; j < neuronWeights.size(); j++)
		{
			netValue += ((neuronWeights[j] + synapseNoise[j]) * inputs[j]);
		}
		netValue = netValue / inputs.size();
		double output = ActivateValue(netValue, m_NetworkAttributes.outputActvFunction);
		outputs.push_back(output);
	}

	return outputs;
}
