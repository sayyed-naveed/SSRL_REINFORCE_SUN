
/*****************************************************************************
******************************************************************************

			UnitDelayedReinforceController
			facilitates the adaptive components by providing
			the remaining implementations for Sigma Updates
			and setting noise using the Stochastic Unit
			method for the delayed reward situations.

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _UNITDELAYEDREINFORCECONTROLLER_H
#define _UNITDELAYEDREINFORCECONTROLLER_H

#include "SUNDelayedReinforceController.h"

#include<vector>

using namespace std;

class UnitDelayedReinforceController : public SUNDelayedReinforceController
{
public:
	UnitDelayedReinforceController(NetworkAttributes networkAttributes);
	~UnitDelayedReinforceController();

protected:
	virtual bool UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs, double reward);

	virtual bool SetNoise();

	virtual bool SetNetworkSigma();

private:

};

#endif
