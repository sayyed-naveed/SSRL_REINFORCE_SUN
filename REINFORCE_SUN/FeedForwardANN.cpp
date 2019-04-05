
/*****************************************************************************
******************************************************************************

					Implementation for Feed Forward Neural Network

**************************Author: Syed Naveed **************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "FeedForwardANN.h"

#include <iostream>

FeedForwardANN::FeedForwardANN(NetworkAttributes networkAttributes)
{
	m_NetworkAttributes = networkAttributes;
	m_WeightMatrixSize = CalculateMatrixSize();
}

FeedForwardANN::~FeedForwardANN()
{

}

vector<double> FeedForwardANN::ExecuteStep(vector<double> inputs, vector<vector<double>> weightsMatrix, int weightMatrixSize)
{
	vector<double>	outputs;

	if (m_WeightMatrixSize != weightMatrixSize)
	{
		cout << "ERROR: Matrix size is not appropriate!" << endl;
		return outputs;
	}

	//hidden layer output
	for (int i = 0; i < m_NetworkAttributes.numHiddenLayers; i++)
	{
		for (int j = 0; j < m_NetworkAttributes.numHiddenUnitsPerLayer; j++)
		{
			double netValue					= 0;
			vector<double> neuronWeights	= weightsMatrix[i*m_NetworkAttributes.numHiddenUnitsPerLayer + j];
			for (unsigned int k = 0; k < neuronWeights.size(); k++)
			{
				netValue += neuronWeights[k] * inputs[k];
			}
			double output = ActivateValue(netValue, m_NetworkAttributes.hiddenActvFunction);
			outputs.push_back(output);
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
		for (unsigned int j = 0; j < neuronWeights.size(); j++)
		{
			netValue += neuronWeights[j] * inputs[j];
		}
		double output = ActivateValue(netValue, m_NetworkAttributes.outputActvFunction);
		outputs.push_back(output);
	}

	return outputs;
}

double FeedForwardANN::ActivateValue(double netValue, ActivationTypes actvFunction)
{
	double	actvVal = netValue;

	switch (actvFunction)
	{
		case ActivationTypes::eSigmoid:
			// Range: 0 to 1
			actvVal = 1 / (1 + exp(-m_NetworkAttributes.actvLambda * netValue));
			// If slow use: f(x) = x / (1 + abs(x)) i.e., 
			// actvVal = (-m_ActvLambda * netValue) / (1 + abs((-m_ActvLambda * netValue)));
		break;
		case ActivationTypes::eStep:
			// Range: 0 or 1 (Used for Binary Classification)
			//actvVal = 1 / (1 + exp(-m_NetworkAttributes.actvLambda * netValue));
			// If slow use: f(x) = x / (1 + abs(x)) i.e., 
			// actvVal = (-m_ActvLambda * netValue) / (1 + abs((-m_ActvLambda * netValue)));
			actvVal = netValue > 0 ? 1 : 0;
		break;
		case ActivationTypes::eTanh:
			// Range: -1 to +1
			actvVal = tanh(netValue);
		break;
		default:
			cout << "Activation Function not supported!! \n";
		break;
	}

	return actvVal;
}

int FeedForwardANN::CalculateMatrixSize()
{
	int	weightNum = 0;
	int	lastLayerNumber;

	lastLayerNumber = m_NetworkAttributes.numInputs;

	for (int i = 0; i < m_NetworkAttributes.numHiddenLayers; i++)
	{
		weightNum += m_NetworkAttributes.numHiddenUnitsPerLayer * lastLayerNumber;
		lastLayerNumber = m_NetworkAttributes.numHiddenUnitsPerLayer;
	}

	weightNum += lastLayerNumber * m_NetworkAttributes.numOutputs;

	return weightNum;
}