
/*****************************************************************************
 *****************************************************************************

									GLOBALS

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once

#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <vector>
#include <string>

using namespace std;

const bool		DEBUG_ON				=	false;
// Experiment details
const int		NUM_DATASETS			=	50;
// 8000  for Static
// 20000 for Dynamic
const int		NUM_TRIALS				=	20000; 
const int		NUM_TIME_STEPS			=	1;
const int		CONT_INPUT_LOWLMT		=	0;
const int		CONT_INPUT_UPLMT		=	1;
const int		CONT_INPUT_DCML_PLACES	=	2;
const int		DISC_INPUT_LOWLMT		=	0;
const int		DISC_INPUT_UPLMT		=	1;
// Initial Weights for Synthetic Data generation
const double	WEIGHT_DC_GEN_LOWLMT	=	-2.0;
const double	WEIGHT_DC_GEN_UPLMT		=	2.0;
const double	WEIGHT_CC_GEN_LOWLMT	=	-2.0;
const double	WEIGHT_CC_GEN_UPLMT		=	2.0;
const double	WEIGHT_CD_GEN_LOWLMT	=	-2.0;
const double	WEIGHT_CD_GEN_UPLMT		=	2.0;
const double	WEIGHT_DD_GEN_LOWLMT	=	-2.0;
const double	WEIGHT_DD_GEN_UPLMT		=	2.0;
// Initial Weights for Learning Algorithms
const double	WEIGHT_DC_LEARN_LOWLMT	=	-2.0;
const double	WEIGHT_DC_LEARN_UPLMT	=	2.0;
const double	WEIGHT_CC_LEARN_LOWLMT	=	-2.0;
const double	WEIGHT_CC_LEARN_UPLMT	=	2.0;
const double	WEIGHT_CD_LEARN_LOWLMT	=	-0.1;
const double	WEIGHT_CD_LEARN_UPLMT	=	0.1;
const double	WEIGHT_DD_LEARN_LOWLMT	=	-0.1;
const double	WEIGHT_DD_LEARN_UPLMT	=	0.1;
// Misc
const int		RAND_DCML_PLACES		=	2;
const int		ACTV_LAMBDA				=	2;
const double	LEARN_RATE_W			=	0.5;
const double	LEARN_RATE_NU			=	0.5;
const double	LEARN_RATE_SIGMA		=	0.5;
const double	LEARN_CUTOFF_SIGMA		=	0.6745;
const double	SIGMA_LOW_CAP			=	0.0;
const double	SIGMA_UPP_CAP			=	1.0;
const double	REWARD_DISCOUNT_FACTOR  =	0.5;
const bool		IS_BIAS_UNIT			=	true;

// Variable Names to construct directory structures for File IO 
const string	PATH_CONCAT				= "\\";
const string	DIR_LOGS				= "..\\Logs";

const string	DIR_STATIC				= "Static";
const string	DIR_DYNAMIC				= "Dynamic";
const string	DIR_DISC_CONT			= "Discrete_Continuous";
const string	DIR_CONT_CONT			= "Continuous_Continuous";
const string	DIR_CONT_DISC			= "Continuous_Discrete";
const string	DIR_DISC_DISC			= "Discrete_Discrete";
const string	DIR_STOCH_SYNP			= "Synapse";
const string	DIR_STOCH_UNIT			= "Unit";
const string	DIR_STOCH_NETW			= "Network";
const string	DIR_DEBUG				= "Debug";
const string	DIR_KINM_DATA			= "Kinematics_Data";
const string	DIR_FWD_KINM_DATA		= "ForwardKinematics";
const string	DIR_INV_KINM_DATA		= "InverseKinematics";
// 3x3 Linear
const string	DIR_3_3					= "3x3_Linear";
// 12x3
const string	DIR_FWD_12_3			= "12x3_FWD_KNM";
const string	DIR_INV_12_3			= "12x3_INV_KNM";
// 3x12
const string	DIR_FWD_3_12			= "3x12_FWD_KNM";
const string	DIR_INV_3_12			= "3x12_INV_KNM";
// 12x12
const string	DIR_FWD_12_12			= "12x12_FWD_KNM";
const string	DIR_INV_12_12			= "12x12_INV_KNM";
// 21x21
const string	DIR_FWD_21_21			= "21x21_FWD_KNM";
const string	DIR_INV_21_21			= "21x21_INV_KNM";
// 30x30
const string	DIR_FWD_30_30			= "30x30_FWD_KNM";
const string	DIR_INV_30_30			= "30x30_INV_KNM";
// 3x21
const string	DIR_FWD_3_21			= "3x21_FWD_KNM";
const string	DIR_INV_3_21			= "3x21_INV_KNM";
// 3x30
const string	DIR_FWD_3_30			= "3x30_FWD_KNM";
const string	DIR_INV_3_30			= "3x30_INV_KNM";
// 21x3
const string	DIR_FWD_21_3			= "21x3_FWD_KNM";
const string	DIR_INV_21_3			= "21x3_INV_KNM";
// 30x3
const string	DIR_FWD_30_3			= "30x3_FWD_KNM";
const string	DIR_INV_30_3			= "30x3_INV_KNM";
// 3x3
const string	DIR_FWD_3_3				= "3x3_FWD_KNM";
const string	DIR_INV_3_3				= "3x3_INV_KNM";
// 6x6
const string	DIR_FWD_6_6				= "6x6_FWD_KNM";
const string	DIR_INV_6_6				= "6x6_INV_KNM";
// 3x6
const string	DIR_FWD_3_6				= "3x6_FWD_KNM";
// 6x3
const string	DIR_INV_6_3				= "6x3_INV_KNM";
// 24x6
const string	DIR_INV_24_6			= "24x6_INV_KNM";

const string	FILE_NAME_DATASET		= "DataSet";
const string	FILE_NAME_REWARD		= "Rewards.txt";
const string	FILE_NAME_WEIGHTS		= "Weights.txt";
const string	FILE_NAME_INPUTS_GEN	= "Inputs_Gen.txt";
const string	FILE_NAME_OUTPUTS_GEN	= "Outputs_Gen.txt";
const string	FILE_NAME_WEIGHTS_GEN	= "Weights_Gen.txt";
const string	FILE_NAME_SIGMA			= "Sigma.txt";
const string	FILE_NAME_NOISE			= "Noise.txt";
const string	FILE_NAME_OUTPUTS		= "Outputs.txt";
const string	FILE_NAME_FWD_KINM		= "ForwardKinematics.txt";
const string	FILE_NAME_INV_KINM		= "InverseKinematics.txt";

enum class RunType
{
	e3_3							= 1,
	e30_30							= 2,
	e3_3_NonLinear					= 3,
	e30_30_NonLinear				= 4,
	// These options were added later 
	// when we started using all 
	// kinematics data
	e3_3_NonLinear_FwdKinematics	= 5,
	e3_3_NonLinear_InvKinematics	= 6,
	e12_3_NonLinear_FwdKinematics	= 7,
	e12_3_NonLinear_InvKinematics	= 8,
	e3_12_NonLinear_FwdKinematics	= 9,
	e3_12_NonLinear_InvKinematics	= 10,
	e12_12_NonLinear_FwdKinematics	= 11,
	e12_12_NonLinear_InvKinematics	= 12,
	e21_21_NonLinear_FwdKinematics	= 13,
	e21_21_NonLinear_InvKinematics	= 14,
	e30_30_NonLinear_FwdKinematics	= 15,
	e30_30_NonLinear_InvKinematics	= 16,
	e3_21_NonLinear_FwdKinematics	= 17,
	e3_21_NonLinear_InvKinematics	= 18,
	e3_30_NonLinear_FwdKinematics	= 19,
	e3_30_NonLinear_InvKinematics	= 20,
	e21_3_NonLinear_FwdKinematics	= 21,
	e21_3_NonLinear_InvKinematics	= 22,
	e30_3_NonLinear_FwdKinematics	= 23,
	e30_3_NonLinear_InvKinematics	= 24,
	e6_6_NonLinear_FwdKinematics	= 25,
	e6_6_NonLinear_InvKinematics	= 26,
	e3_6_NonLinear_FwdKinematics	= 27,
	e6_3_NonLinear_InvKinematics	= 28,
	e24_6_NonLinear_InvKinematics	= 29,
	eMaxCount
};

enum class ReinforceType
{
	eImmediate	= 1,
	eDelayed	= 2
}; 

enum class EnvType
{
	eStatic		= 1,
	eDynamic	= 2
};

enum class IOType : short
{
	eDiscreteContinuous		= 1,
	eContinuousContinuous	= 2,
	eContinuousDiscrete		= 3,
	eDiscreteDiscrete		= 4
};

typedef struct
{
	vector<double> input;
	vector<double> output;
} IOMapping;

enum class RewardDataLogOrder
{
	// Do not touch 
	// the first two indices
	eReward		= 0,
	eAvgReward	= 1,
	eCummReward	= 2,
	eMaxCount
};

#endif