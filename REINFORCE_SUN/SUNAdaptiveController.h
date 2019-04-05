
/*****************************************************************************
******************************************************************************

			SUNAdaptiveController is an Abstract class that 
			facilitates the adaptive components by enforcing 
			necessary Methods such as Weight/Sigma Updates
			and Backpropagation. It forces its extenders
			to implement their own versions of Updating Sigma
			and Setting Noise Matrix. This class also provides
			few static methods to faciliate repetative tasks.

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _SUNADAPTIVECONTROLLER_H
#define _SUNADAPTIVECONTROLLER_H

#include "SUNFeedForwardANN.h"

#include<vector>

using namespace std;

class SUNAdaptiveController
{
public:
	SUNAdaptiveController(NetworkAttributes networkAttributes);
	~SUNAdaptiveController();

	virtual bool	ExecuteTrials(		int							ds, 
										vector<vector <double>> &	rewardData)	= 0;

	string			GetDirName();

	static bool		ConstructMatrix(
										vector<vector<double>>	&	matrix,
										double						initValue,
										NetworkAttributes			networkAttributes);

	static bool		SetMatrix(
										vector<vector<double>>	&	matrix, 
										double						value);

	static bool		RandomInitMatrix(
										double						lowLimit, 
										double						upperLimit,
										vector<vector<double>>	&	matrix);

	static bool		SetUnitValue(
										vector<double>			&	unit, 
										double						value);

protected:
	virtual bool	ComputeReward(
										vector<double>				currOutput, 
										vector<double>				targetOutput, 
										double &					reward)			= 0;

	virtual bool	UpdateWeights(
										vector<double>				inputs, 
										vector<double>				hiddenOutputs, 
										double						reward)			= 0;

	virtual bool	UpdateSigma(
										vector<double>				inputs, 
										vector<double>				hiddenOutputs, 
										double						reward)			= 0;

	virtual bool	Backpropagate(
										vector<double>				inputs, 
										vector<double>				hiddenOutputs)	= 0;

	virtual bool	UpdateMean()			= 0;

	virtual bool	SetNoise()				= 0;

	virtual bool	SetNetworkSigma()		= 0;

	double			GetSampledNoise(
										double						mean, 
										double						stdDev);

	int				CalculateMatrixSize();

	bool			ResetDataMembers();

	vector<vector<double>>	m_WeightMatrix;
	vector<vector<double>>	m_MeanMatrix;
	vector<vector<double>>	m_StdDevMatrix;
	vector<vector<double>>	m_NoiseMatrix;

	int						m_MatrixSize;
	NetworkAttributes		m_NetworkAttributes;
	SUNFeedForwardANN		m_SUNFeedFwdANN;

	vector<vector<double>>	m_WeightUpdateMatrix;
	double					m_CummReward;
	double					m_AvgReward;

	string					m_DirName;

private:

};

#endif
