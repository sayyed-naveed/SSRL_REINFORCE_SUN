
/*****************************************************************************
******************************************************************************

			UnitImmediateReinforceController 
			facilitates the adaptive components by providing
			the remaining implementations for Sigma Updates
			and setting noise using the Stochastic Units
			method for the immediate reward situations.

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _UNITIMMEDIATEREINFORCECONTROLLER_H
#define _UNITIMMEDIATEREINFORCECONTROLLER_H

#include "SUNImmediateReinforceController.h"

#include<vector>

using namespace std;

class UnitImmediateReinforceController : public SUNImmediateReinforceController
{
public:
	UnitImmediateReinforceController(NetworkAttributes networkAttributes);
	~UnitImmediateReinforceController();

protected:
	virtual bool UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward);

	virtual bool SetNoise();

	virtual bool SetNetworkSigma();

private:

};

#endif
