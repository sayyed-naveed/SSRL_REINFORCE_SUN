
/*****************************************************************************
******************************************************************************

			NetworkDelayedReinforceController
			facilitates the adaptive components by providing
			the remaining implementations for Sigma Updates
			and setting noise using the Stochastic Network
			method for the delayed reward situations.

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _NETWORKDELAYEDREINFORCECONTROLLER_H
#define _NETWORKDELAYEDREINFORCECONTROLLER_H

#include "SUNDelayedReinforceController.h"

#include<vector>

using namespace std;

class NetworkDelayedReinforceController : public SUNDelayedReinforceController
{
public:
	NetworkDelayedReinforceController(NetworkAttributes networkAttributes);
	~NetworkDelayedReinforceController();

protected:
	virtual bool UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward);

	virtual bool SetNoise();

	virtual bool SetNetworkSigma();

private:

};

#endif
