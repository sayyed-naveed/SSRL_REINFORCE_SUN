
/*****************************************************************************
******************************************************************************

			SynapseDelayedReinforceController
			facilitates the adaptive components by providing
			the remaining implementations for Sigma Updates
			and setting noise using the Stochastic Synapse
			method for the delayed reward situations.

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _SYNAPSEDELAYEDREINFORCECONTROLLER_H
#define _SYNAPSEDELAYEDREINFORCECONTROLLER_H

#include "SUNDelayedReinforceController.h"

#include<vector>

using namespace std;

class SynapseDelayedReinforceController : public SUNDelayedReinforceController
{
public:
	SynapseDelayedReinforceController(NetworkAttributes networkAttributes);
	~SynapseDelayedReinforceController();

protected:
	virtual bool UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward);

	virtual bool SetNoise();

private:

};

#endif
