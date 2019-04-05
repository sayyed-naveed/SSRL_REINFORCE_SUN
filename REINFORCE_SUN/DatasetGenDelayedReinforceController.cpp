
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
#include "DatasetGenDelayedReinforceController.h"

#include <iostream>
#include <math.h>
#include <time.h>


DatasetGenDelayedReinforceController::DatasetGenDelayedReinforceController(NetworkAttributes networkAttributes)
	: SUNAdaptiveController(networkAttributes)
{
}

DatasetGenDelayedReinforceController::~DatasetGenDelayedReinforceController()
{
}

bool DatasetGenDelayedReinforceController::ExecuteTrials(int ds, vector<vector <double>> & rewardData)
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::ComputeReward(vector<double> currOutputs, vector<double> targetOutputs, double & reward)
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::UpdateWeights(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::UpdateSigma(vector<double>	inputs, vector<double> hiddenOutputs, double reward)
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::Backpropagate(vector<double> inputs, vector<double> hiddenOutputs)
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::UpdateMean()
{
	bool result = true;

	return result;
}


bool DatasetGenDelayedReinforceController::SetNoise()
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::SetNetworkSigma()
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::GenerateDiscreteContinuousDS(EnvType envType)
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::GenerateContinuousContinuousDS(EnvType envType)
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::GenerateContinuousDiscreteDS(EnvType envType)
{
	bool result = true;

	return result;
}

bool DatasetGenDelayedReinforceController::GenerateDiscreteDiscreteDS(EnvType envType)
{
	bool result = true;

	return result;
}