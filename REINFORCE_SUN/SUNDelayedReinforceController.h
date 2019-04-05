
/*****************************************************************************
******************************************************************************

			SUNDelayedReinforceController is an Abstract class that 
			facilitates the adaptive components by providing 
			necessary Methods such as Weight Update
			and Backpropagation, and Executing trials for Delayed
			reward situations.

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _SUNDELAYEDREINFORCECONTROLLER_H
#define _SUNDELAYEDREINFORCECONTROLLER_H

#include "SUNAdaptiveController.h"

#include<vector>

using namespace std;

class SUNDelayedReinforceController : public SUNAdaptiveController
{
public:
	SUNDelayedReinforceController(NetworkAttributes networkAttributes);
	~SUNDelayedReinforceController();

	virtual bool ExecuteTrials(		int							ds, 
									vector<vector <double>> &	rewardData);

protected:
	virtual bool ComputeReward(
									vector<double>				currOutputs, 
									vector<double>				targetOutputs, 
									double &					reward);
	virtual bool UpdateWeights(
									vector<double>				inputs,
									vector<double>				hiddenOutputs,
									double						reward);

	virtual bool Backpropagate(
									vector<double>				inputs, 
									vector<double>				hiddenOutputs);

	virtual bool UpdateMean();

private:

};

#endif
