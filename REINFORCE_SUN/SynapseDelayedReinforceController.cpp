
/*****************************************************************************
******************************************************************************

	Implementation for SUN[Synapse]DelayedReinforceController

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "SynapseDelayedReinforceController.h"

SynapseDelayedReinforceController::SynapseDelayedReinforceController(NetworkAttributes networkAttributes)
	: SUNDelayedReinforceController(networkAttributes)
{
	m_DirName = DIR_STOCH_SYNP;
}
SynapseDelayedReinforceController ::~SynapseDelayedReinforceController()
{
}

bool SynapseDelayedReinforceController::UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward)
{
	bool result = true;

	return result;
}

bool SynapseDelayedReinforceController::SetNoise()
{
	bool result = true;

	return result;
}
