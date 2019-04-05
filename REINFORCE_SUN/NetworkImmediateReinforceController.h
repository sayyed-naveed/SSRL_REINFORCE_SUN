
/*****************************************************************************
******************************************************************************

			NetworkImmediateReinforceController 
			facilitates the adaptive components by providing
			the remaining implementations for Sigma Updates
			and setting noise using the Stochastic Network
			method for the immediate reward situations.

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _NETWORKIMMEDIATEREINFORCECONTROLLER_H
#define _NETWORKIMMEDIATEREINFORCECONTROLLER_H

#include "SUNImmediateReinforceController.h"

#include<vector>

using namespace std;

class NetworkImmediateReinforceController : public SUNImmediateReinforceController
{
public:
	NetworkImmediateReinforceController(NetworkAttributes networkAttributes);
	~NetworkImmediateReinforceController();

protected:
	virtual bool UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward);

	virtual bool SetNoise();

	virtual bool SetNetworkSigma();

private:

};

#endif
