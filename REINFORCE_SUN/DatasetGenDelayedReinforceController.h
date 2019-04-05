
/*****************************************************************************
 **** Class that handles Dataset Generation for all four combinations of *****
 *****************************State Action pairs******************************

						 DISCRETE		CONTINUOUS
						 CONTINUOUS		CONTINUOUS
						 CONTINUOUS		DISCRETE
						 DISCRETE		DISCRETE

********************for Delayed Reinforcement situations**********************
**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _DATASETGENDELAYEDREINFORCECONTROLLER_H
#define _DATASETGENDELAYEDREINFORCECONTROLLER_H

#include "SUNAdaptiveController.h"

#include<vector>

using namespace std;

class DatasetGenDelayedReinforceController : public SUNAdaptiveController
{
public:
	DatasetGenDelayedReinforceController(NetworkAttributes networkAttributes);
	~DatasetGenDelayedReinforceController();

	virtual bool ExecuteTrials(				int							ds,
											vector<vector <double>> &	rewardData);

	virtual bool ComputeReward(
											vector<double>				currOutputs, 
											vector<double>				targetOutputs, 
											double &					reward);
	virtual bool UpdateWeights(
											vector<double>				inputs,
											vector<double>				hiddenOutputs,
											double						reward);

	virtual bool UpdateSigma(
											vector<double>				inputs, 
											vector<double>				hiddenOutputs,
											double						reward);

	virtual bool Backpropagate(
											vector<double>				inputs, 
											vector<double>				hiddenOutputs);

	virtual bool UpdateMean();

	virtual bool SetNoise();
	
	virtual bool SetNetworkSigma();

	bool GenerateDiscreteContinuousDS(EnvType envType);

	bool GenerateContinuousContinuousDS(EnvType envType);

	bool GenerateContinuousDiscreteDS(EnvType envType);

	bool GenerateDiscreteDiscreteDS(EnvType envType);

protected:

private:

};

#endif
