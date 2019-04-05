
/*****************************************************************************
******************************************************************************

	Implementation for SUN[Network]DelayedReinforceController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "NetworkDelayedReinforceController.h"

NetworkDelayedReinforceController::NetworkDelayedReinforceController(NetworkAttributes networkAttributes)
	: SUNDelayedReinforceController(networkAttributes)
{
	m_DirName = DIR_STOCH_NETW;
}
NetworkDelayedReinforceController::~NetworkDelayedReinforceController()
{
}

bool NetworkDelayedReinforceController::UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool result = true;

	return result;
}

bool NetworkDelayedReinforceController::SetNoise()
{
	bool result = true;

	return result;
}

bool NetworkDelayedReinforceController::SetNetworkSigma()
{
	bool	result = true;

	return result;
}