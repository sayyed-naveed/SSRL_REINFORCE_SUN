
/*****************************************************************************
******************************************************************************
 
						Class that runs all the experiments

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _EXPERIMENT_H
#define _EXPERIMENT_H

#include "SynapseImmediateReinforceController.h"
#include "UnitImmediateReinforceController.h"
#include "NetworkImmediateReinforceController.h"
#include "Logger.h"

#include<vector>

using namespace std;

class Experiment
{
public:
	Experiment(NetworkAttributes networkAttributes, ReinforceType reinforceChoice, EnvType envType, IOType ioType);
	~Experiment();

	bool Run();

protected:
	bool WriteRewardData(string lastDirPathSegment, vector<vector <double>> rewardData, unsigned int dsNum);

	ReinforceType	m_ReinforceType;
	// m_EnvType doesn't matter for now
	// as all SUN Adaptive Controllers
	// act in a Environment agnostic way
	// i.e., it doesn't matter to them 
	// if it is static or dynamic environment
	// as long as the dataset is generated 
	// appropriately. All these controllers
	// care about is the look up of the 
	// input-output mappings.
	// However it is useful for File IO
	EnvType			m_EnvType; 
	IOType			m_IOType;

private:
	vector<vector<double>>					m_NetworkInputs;

	SynapseImmediateReinforceController		m_StochImmReinforceCtrl;
	UnitImmediateReinforceController		m_UnitImmReinforceCtrl;
	NetworkImmediateReinforceController		m_NetworkImmReinforceCtrl;

};


#endif