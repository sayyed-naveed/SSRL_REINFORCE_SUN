
/*****************************************************************************
******************************************************************************

	Implementation for SUN[Unit]DelayedReinforceController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "UnitDelayedReinforceController.h"

UnitDelayedReinforceController::UnitDelayedReinforceController(NetworkAttributes networkAttributes)
	: SUNDelayedReinforceController(networkAttributes)
{
	m_DirName = DIR_STOCH_UNIT;
}
UnitDelayedReinforceController ::~UnitDelayedReinforceController()
{
}

bool UnitDelayedReinforceController::UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool result = true;

	return result;
}
bool UnitDelayedReinforceController::SetNoise()
{
	bool result = true;

	return result;
}

bool UnitDelayedReinforceController::SetNetworkSigma()
{
	bool	result = true;

	return result;
}