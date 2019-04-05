
/*****************************************************************************
******************************************************************************

	Implementation for SUN[Synapse, Unit, Network]AdaptiveController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "Util.h"
#include "SUNAdaptiveController.h"

#include <time.h>
#include <random>

SUNAdaptiveController::SUNAdaptiveController(NetworkAttributes networkAttributes)
	: m_SUNFeedFwdANN(networkAttributes)
{
	double initValue = 0.0;

	m_NetworkAttributes = networkAttributes;
	m_MatrixSize		= CalculateMatrixSize();

	SUNAdaptiveController::ConstructMatrix(m_WeightMatrix, initValue, m_NetworkAttributes);
	SUNAdaptiveController::ConstructMatrix(m_NoiseMatrix, initValue, m_NetworkAttributes);
	SUNAdaptiveController::ConstructMatrix(m_WeightUpdateMatrix, initValue, m_NetworkAttributes);

	SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);
	SUNAdaptiveController::SetMatrix(m_NoiseMatrix, initValue);

	m_CummReward	= initValue;
	m_AvgReward		= initValue;
}
SUNAdaptiveController ::~SUNAdaptiveController()
{
}

string SUNAdaptiveController::GetDirName()
{
	return m_DirName;
}

bool SUNAdaptiveController::ConstructMatrix(vector<vector<double>> & matrix, double initValue, NetworkAttributes networkAttributes)
{
	bool result = true;

	int outputLayerWeightsStartIndex = 0;

	// Clean the matrix weight if its being re-assigned
	int lastLayerNum = networkAttributes.numInputs;
	matrix.clear();

	// First layer of hidden neurons
	for (int i = 0; i < networkAttributes.numHiddenUnitsPerLayer; i++)
	{
		std::vector<double> neuronConn;
		for (int j = 0; j < networkAttributes.numInputs; j++)
		{
			neuronConn.push_back(initValue);
		}
		matrix.push_back(neuronConn);
		lastLayerNum = networkAttributes.numHiddenUnitsPerLayer;
	}

	// Rest of the layers
	for (int i = 0; i < networkAttributes.numHiddenLayers - 1; i++)
	{
		for (int j = 0; j < networkAttributes.numHiddenUnitsPerLayer; j++)
		{
			std::vector<double> neuronConn;
			for (int k = 0; k < networkAttributes.numHiddenUnitsPerLayer; k++)
			{
				neuronConn.push_back(initValue);
			}
			matrix.push_back(neuronConn);
		}
	}
	// Saving the next index to resume from
	outputLayerWeightsStartIndex =		networkAttributes.numHiddenUnitsPerLayer 
									*	networkAttributes.numInputs
									+	networkAttributes.numHiddenUnitsPerLayer 
									*	networkAttributes.numHiddenUnitsPerLayer 
									*	(networkAttributes.numHiddenLayers - 1);


	// The output layer
	for (int i = 0; i < networkAttributes.numOutputs; i++)
	{
		std::vector<double> neuronConn;
		for (int j = 0; j < lastLayerNum; j++)
		{
			neuronConn.push_back(initValue);
		}
		matrix.push_back(neuronConn);
	}

	return result;
}

bool SUNAdaptiveController::SetMatrix(vector<vector<double>> & matrix, double value)
{
	bool result = true;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			matrix[i][j] = value;
		}
	}

	return result;
}

bool SUNAdaptiveController::RandomInitMatrix(double lowLimit, double upperLimit, vector<vector<double>> & matrix)
{
	bool result = true;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			matrix[i][j] = Util::roundDecimal(Util::getUniformRandom(lowLimit, upperLimit), RAND_DCML_PLACES);
		}
	}

	return result;
}

bool SUNAdaptiveController::SetUnitValue(vector<double> & unit, double value)
{
	bool	result = true;

	for (unsigned int j = 0; j < unit.size(); j++)
	{
		unit[j] = value;
	}

	return result;
}

double SUNAdaptiveController::GetSampledNoise(double mean, double stdDev)
{
	double noise = 0.0;

	assert(stdDev >= 0);
	assert(mean >= 0);

	if (stdDev > 0)
	{
		noise = Util::getNormalRandom(mean, stdDev);
	}

	return noise;
}

int SUNAdaptiveController::CalculateMatrixSize()
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

bool SUNAdaptiveController::ResetDataMembers()
{
	bool	result		= true;
	double	initValue	= 0.0;

	SUNAdaptiveController::RandomInitMatrix(m_NetworkAttributes.initWeightsLowLmt, m_NetworkAttributes.initWeightsUpLmt, m_WeightMatrix);
	SUNAdaptiveController::RandomInitMatrix(SIGMA_LOW_CAP, SIGMA_UPP_CAP, m_StdDevMatrix);
	SUNAdaptiveController::SetMatrix(m_MeanMatrix, initValue);
	SUNAdaptiveController::SetMatrix(m_NoiseMatrix, initValue);
	
	SetNetworkSigma();
	SetNoise();

	m_CummReward	= initValue;
	m_AvgReward		= initValue;

	return result;
}

