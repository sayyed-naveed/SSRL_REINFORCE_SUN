
/*****************************************************************************
******************************************************************************

			SynapseImmediateReinforceController 
			facilitates the adaptive components by providing 
			the remaining implementations for Sigma Updates
			and setting noise using the Stochastic Synapse 
			method for the immediate reward situations. 

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _SYNAPSEIMMEDIATEREINFORCECONTROLLER_H
#define _SYNAPSEIMMEDIATEREINFORCECONTROLLER_H

#include "SUNImmediateReinforceController.h"

#include<vector>

using namespace std;

class SynapseImmediateReinforceController : public SUNImmediateReinforceController
{
public:
	SynapseImmediateReinforceController(NetworkAttributes networkAttributes);
	~SynapseImmediateReinforceController();

protected:
	virtual bool UpdateSigma(vector<double> inputs, vector<double> hiddenOutputs,	double reward);

	virtual bool SetNoise();

	virtual bool SetNetworkSigma();

private:

};

#endif
