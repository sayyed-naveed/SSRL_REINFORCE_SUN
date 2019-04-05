
/*****************************************************************************
******************************************************************************

	Implementation for SUN[Synapse, Unit, Network]DelayedReinforceController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "SUNDelayedReinforceController.h"

SUNDelayedReinforceController::SUNDelayedReinforceController(NetworkAttributes networkAttributes)
	: SUNAdaptiveController(networkAttributes)
{
	double initValue = 0.0;

	SUNAdaptiveController::ConstructMatrix(m_StdDevMatrix, initValue, networkAttributes);
	SUNAdaptiveController::ConstructMatrix(m_MeanMatrix, initValue, networkAttributes);

	SUNAdaptiveController::RandomInitMatrix(SIGMA_LOW_CAP, SIGMA_UPP_CAP, m_StdDevMatrix);
	SUNAdaptiveController::SetMatrix(m_MeanMatrix, initValue);
}
SUNDelayedReinforceController ::~SUNDelayedReinforceController()
{
}

bool SUNDelayedReinforceController::ExecuteTrials(int ds, vector<vector <double>> & rewardData)
{
	bool result = true;

	return result;
}

bool SUNDelayedReinforceController::ComputeReward(vector<double> currOutputs, vector<double> targetOutputs, double & reward)
{
	bool result = true;

	return result;
}

bool SUNDelayedReinforceController::UpdateWeights(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool result = true;

	return result;
}

bool SUNDelayedReinforceController::Backpropagate(vector<double> inputs, vector<double> hiddenOutputs)
{
	bool result = true;

	return result;
}

bool SUNDelayedReinforceController::UpdateMean()
{
	bool result = true;

	return result;
}
