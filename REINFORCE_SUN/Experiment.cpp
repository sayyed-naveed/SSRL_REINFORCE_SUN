
/*****************************************************************************
******************************************************************************

				Implementation for running all the experiments

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "Experiment.h"
#include "Logger.h"

#include <iostream>

using namespace std;

Experiment::Experiment(NetworkAttributes networkAttributes, ReinforceType reinforceChoice, EnvType envType, IOType ioType)
	:	m_StochImmReinforceCtrl(networkAttributes),
		m_UnitImmReinforceCtrl(networkAttributes),
		m_NetworkImmReinforceCtrl(networkAttributes)
{
	m_IOType		= ioType;
	m_EnvType		= envType;
	m_ReinforceType	= reinforceChoice;
}
Experiment::~Experiment()
{
}
bool Experiment::Run()
{
	bool					result		= true;
	vector<vector <double>> rewardData;

	if (m_ReinforceType == ReinforceType::eImmediate)
	{
		for (int ds = 0; ds < NUM_DATASETS; ds++)
		{
			m_StochImmReinforceCtrl.ExecuteTrials(ds, rewardData);
			WriteRewardData(m_StochImmReinforceCtrl.GetDirName(), rewardData, ds);

			m_UnitImmReinforceCtrl.ExecuteTrials(ds, rewardData);
			WriteRewardData(m_UnitImmReinforceCtrl.GetDirName(), rewardData, ds);
			
			m_NetworkImmReinforceCtrl.ExecuteTrials(ds, rewardData);
			WriteRewardData(m_NetworkImmReinforceCtrl.GetDirName(), rewardData, ds);
		}
	}

	return result;
}

bool Experiment::WriteRewardData(string lastDirPathSegment, vector<vector<double>> rewardData, unsigned int dsNum)
{
	bool result = true;

	assert(rewardData.size() == (unsigned int)RewardDataLogOrder::eMaxCount);

	double cummReward = rewardData[(unsigned int)RewardDataLogOrder::eCummReward][0];

	string	finalDirPath;
	string	finalFileName;

	Logger::ConstructFullDirFilePaths(finalDirPath, finalFileName, false, lastDirPathSegment, to_string(dsNum), FILE_NAME_REWARD);

	Logger logger(finalDirPath, finalDirPath + finalFileName, std::ios::out);
	   	  
	logger.WriteString(finalDirPath);
	logger.WriteString("Cummulative Reward: " + to_string(cummReward));
	logger.WriteString("Trial#\tReward\tAvg_Reward");
	logger.WriteVectors(rewardData, 2);

	return result;
}
