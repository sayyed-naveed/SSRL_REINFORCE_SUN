
/*****************************************************************************
 **** Class that handles Dataset Generation for all four combinations of *****
 *****************************State Action pairs******************************

						 DISCRETE		CONTINUOUS
						 CONTINUOUS		CONTINUOUS
						 CONTINUOUS		DISCRETE
						 DISCRETE		DISCRETE 

********************for Immediate Reinforcement situations**********************
**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _DATASETGENIMMEDIATEREINFORCECONTROLLER_H
#define _DATASETGENIMMEDIATEREINFORCECONTROLLER_H

#include "SUNAdaptiveController.h"
#include "Logger.h"

#include <vector>

using namespace std;

class DatasetGenImmediateReinforceController : public SUNAdaptiveController
{
public:
	DatasetGenImmediateReinforceController(NetworkAttributes networkAttributes);
	~DatasetGenImmediateReinforceController();

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

	virtual bool Backpropagate(				vector<double>				inputs, 
											vector<double>				hiddenOutputs);

	virtual bool UpdateMean();
	
	virtual bool SetNoise();

	virtual bool SetNetworkSigma();

	bool LoadDiscreteContinuousDS(			RunType						runChoice, 
											EnvType						envType);

	bool LoadDataset(						RunType						runChoice,
											EnvType						envType);

	bool LoadContinuousDiscreteDS(			RunType						runChoice, 
											EnvType						envType);

	bool LoadDiscreteDiscreteDS(			RunType						runChoice, 
											EnvType						envType);

	bool GenerateDiscreteContinuousDS(		EnvType						envType);

	bool GenerateContinuousContinuousDS(	EnvType						envType);

	bool GenerateContinuousDiscreteDS(		EnvType						envType);

	bool GenerateDiscreteDiscreteDS(		EnvType						envType);

	bool LoadInputOutputMap(				Logger *					pLogger, 
											int							numInputs, 
											int							numOutputs, 
											int							ds, 
											int							numTrials, 
											bool						isBiasUnit);

	bool GenerateRandomizedDiscreteInputs(	int							numInputs, 
											int							numTrials);
	
	bool GenerateRandomizedDiscreteInputsB(	int							numInputs, 
											int							numTrials);
	
	bool GenerateRandomizedContinuousInputs(int							numInputs, 
											int							numTrials);

	bool GenerateDiscreteInputs(			int							power, 
											vector<vector<double>> &	discreteInputs);

	bool AppendMappings(					int							datasetIndex,
											int							numTrials);

	bool ClearData();

	void Print();
	
	static IOMapping		s_IOMappings[NUM_DATASETS][NUM_TRIALS];

protected:
	bool GetBin(							int number, 
											int numDigits, 
											vector<double> & binary);

	bool SetNoise(							double noiseVal);

	bool AddBiasInput();

	vector<vector<double>>	m_NetworkInputs;

private:

};

#endif
