
/******************************************************************************
 ******************************************************************************

This file contains the 'main' function. Program execution begins and ends there

**************************Author: Syed Naveed H Shah***************************
*******************************************************************************/

#include "pch.h"
#include "Globals.h"
#include "DatasetGenImmediateReinforceController.h"
#include "DatasetGenDelayedReinforceController.h"
#include "Experiment.h"

#include <iostream>

bool isChoiceKinematic(RunType eChoice)
{
	bool result = false;

	if (	
			eChoice == RunType::e3_3_NonLinear_FwdKinematics
		||	eChoice == RunType::e3_3_NonLinear_InvKinematics
		||	eChoice == RunType::e12_3_NonLinear_FwdKinematics
		||	eChoice == RunType::e12_3_NonLinear_InvKinematics
		||	eChoice == RunType::e3_12_NonLinear_FwdKinematics
		||	eChoice == RunType::e3_12_NonLinear_InvKinematics
		||	eChoice == RunType::e12_12_NonLinear_FwdKinematics
		||	eChoice == RunType::e12_12_NonLinear_InvKinematics
		||	eChoice == RunType::e21_21_NonLinear_FwdKinematics
		||	eChoice == RunType::e21_21_NonLinear_InvKinematics
		||	eChoice == RunType::e30_30_NonLinear_FwdKinematics
		||	eChoice == RunType::e30_30_NonLinear_InvKinematics
		||	eChoice == RunType::e3_21_NonLinear_FwdKinematics
		||	eChoice == RunType::e3_21_NonLinear_InvKinematics
		||	eChoice == RunType::e3_30_NonLinear_FwdKinematics
		||	eChoice == RunType::e3_30_NonLinear_InvKinematics
		||	eChoice == RunType::e21_3_NonLinear_FwdKinematics
		||	eChoice == RunType::e21_3_NonLinear_InvKinematics
		||	eChoice == RunType::e30_3_NonLinear_FwdKinematics
		||	eChoice == RunType::e30_3_NonLinear_InvKinematics
		||	eChoice == RunType::e6_6_NonLinear_FwdKinematics
		||	eChoice == RunType::e6_6_NonLinear_InvKinematics
		||	eChoice == RunType::e3_6_NonLinear_FwdKinematics
		||	eChoice == RunType::e6_3_NonLinear_InvKinematics
		||	eChoice == RunType::e24_6_NonLinear_InvKinematics
		)
	{
		result = true;
	}

	return result;
}

bool SetNetworkBasicAttributes(short runChoice, NetworkAttributes & networkAttributes)
{
	bool result = true;
	
	switch (runChoice)
	{
		case (short)RunType::e3_3:
			networkAttributes.numInputs					= 4; // Includes Bias unit
			networkAttributes.numOutputs				= 3;
			networkAttributes.numHiddenLayers			= 0;
			networkAttributes.numHiddenUnitsPerLayer	= 0;
		break;
		case (short)RunType::e30_30:
			networkAttributes.numInputs					= 31; // Includes Bias unit
			networkAttributes.numOutputs				= 30;
			networkAttributes.numHiddenLayers			= 0;
			networkAttributes.numHiddenUnitsPerLayer	= 0;
		break;
		case (short)RunType::e3_3_NonLinear:
			networkAttributes.numInputs					= 4; // Includes Bias unit
			networkAttributes.numOutputs				= 3;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 20;
		break;
		case (short)RunType::e30_30_NonLinear:
			networkAttributes.numInputs					= 31; // Includes Bias unit
			networkAttributes.numOutputs				= 30;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 31;
		break;
		case (short)RunType::e3_3_NonLinear_FwdKinematics:
		case (short)RunType::e3_3_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 4; // Includes Bias unit
			networkAttributes.numOutputs				= 3;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 20;
		break;
		case (short)RunType::e12_3_NonLinear_FwdKinematics:
		case (short)RunType::e12_3_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 13; // Includes Bias unit
			networkAttributes.numOutputs				= 3;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 13;
		break;
		case (short)RunType::e3_12_NonLinear_FwdKinematics:	
		case (short)RunType::e3_12_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 4; // Includes Bias unit
			networkAttributes.numOutputs				= 12;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 12;
		break;
		case (short)RunType::e12_12_NonLinear_FwdKinematics:
		case (short)RunType::e12_12_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 13; // Includes Bias unit
			networkAttributes.numOutputs				= 12;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 13;
		break;
		case (short)RunType::e21_21_NonLinear_FwdKinematics:
		case (short)RunType::e21_21_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 22; // Includes Bias unit
			networkAttributes.numOutputs				= 21;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 22;
		break;
		case (short)RunType::e30_30_NonLinear_FwdKinematics:
		case (short)RunType::e30_30_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 31; // Includes Bias unit
			networkAttributes.numOutputs				= 30;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 31;
		break;
		case (short)RunType::e3_21_NonLinear_FwdKinematics:
		case (short)RunType::e3_21_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 4; // Includes Bias unit
			networkAttributes.numOutputs				= 21;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 21;
		break;
		case (short)RunType::e3_30_NonLinear_FwdKinematics:
		case (short)RunType::e3_30_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 4; // Includes Bias unit
			networkAttributes.numOutputs				= 30;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 30;
		break;
		case (short)RunType::e21_3_NonLinear_FwdKinematics:
		case (short)RunType::e21_3_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 22; // Includes Bias unit
			networkAttributes.numOutputs				= 3;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 22;
		break;
		case (short)RunType::e30_3_NonLinear_FwdKinematics:
		case (short)RunType::e30_3_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 31; // Includes Bias unit
			networkAttributes.numOutputs				= 3;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 31;
		break;
		case (short)RunType::e6_6_NonLinear_FwdKinematics:
		case (short)RunType::e6_6_NonLinear_InvKinematics:
			networkAttributes.numInputs					= 7; // Includes Bias unit
			networkAttributes.numOutputs				= 6;
			networkAttributes.numHiddenLayers			= 1;
			networkAttributes.numHiddenUnitsPerLayer	= 7;
		break;
		case (short)RunType::e3_6_NonLinear_FwdKinematics:
			networkAttributes.numInputs = 4; // Includes Bias unit
			networkAttributes.numOutputs = 6;
			networkAttributes.numHiddenLayers = 1;
			networkAttributes.numHiddenUnitsPerLayer = 20;
		break;
		case (short)RunType::e6_3_NonLinear_InvKinematics:
			networkAttributes.numInputs = 7; // Includes Bias unit
			networkAttributes.numOutputs = 3;
			networkAttributes.numHiddenLayers = 1;
			networkAttributes.numHiddenUnitsPerLayer = 7;
		break;
		case (short)RunType::e24_6_NonLinear_InvKinematics:
			networkAttributes.numInputs = 25; // Includes Bias unit
			networkAttributes.numOutputs = 6;
			networkAttributes.numHiddenLayers = 1;
			networkAttributes.numHiddenUnitsPerLayer = 25;
		break;
		
		default:
			std::cout << "Choice not supported!! \n";
		break;
	}

	return result;
}

bool RunImmediateReinforce(short runChoice, short envChoice, short stateActionChoice)
{
	bool				result				= true;
	NetworkAttributes	networkAttributes	=	{
													0,		// To be set later
													0,		// To be set later
													0,		// To be set later
													0,		// To be set later
													ACTV_LAMBDA, 
													ActivationTypes::eSigmoid, // To be set later
													ActivationTypes::eSigmoid,
													0.0,	// To be set later
													0.0		// To be set later
												};

	SetNetworkBasicAttributes(runChoice, networkAttributes);

	// Generate Datasets
	switch (stateActionChoice)
	{
		case (short)IOType::eDiscreteContinuous:
		{
			networkAttributes.outputActvFunction	= ActivationTypes::eSigmoid;
			networkAttributes.initWeightsLowLmt		= WEIGHT_DC_GEN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_DC_GEN_UPLMT;
			DatasetGenImmediateReinforceController	gen(networkAttributes);

			isChoiceKinematic((RunType)runChoice) ?
														gen.LoadDataset((RunType)runChoice, (EnvType)envChoice)
														: 
														gen.GenerateDiscreteContinuousDS((EnvType)envChoice);

			// Set initial weight values for the learning algorithm
			networkAttributes.initWeightsLowLmt		= WEIGHT_DC_LEARN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_DC_LEARN_UPLMT;
			break;
		}
		case (short)IOType::eContinuousContinuous:
		{
			networkAttributes.outputActvFunction	= ActivationTypes::eSigmoid;
			networkAttributes.initWeightsLowLmt		= WEIGHT_CC_GEN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_CC_GEN_UPLMT;
			DatasetGenImmediateReinforceController	gen(networkAttributes);

			isChoiceKinematic((RunType)runChoice) ?
													gen.LoadDataset((RunType)runChoice, (EnvType)envChoice)
													: 
													gen.GenerateContinuousContinuousDS((EnvType)envChoice);

			// Set initial weight values for the learning algorithm
			networkAttributes.initWeightsLowLmt		= WEIGHT_CC_LEARN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_CC_LEARN_UPLMT;
			break;
		}
		case (short)IOType::eContinuousDiscrete:
		{
			networkAttributes.outputActvFunction	= ActivationTypes::eStep;
			networkAttributes.initWeightsLowLmt		= WEIGHT_CD_GEN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_CD_GEN_UPLMT;
			DatasetGenImmediateReinforceController	gen(networkAttributes);

			isChoiceKinematic((RunType)runChoice) ?
													gen.LoadDataset((RunType)runChoice, (EnvType)envChoice)
													: 
													gen.GenerateContinuousDiscreteDS((EnvType)envChoice);

			// Set initial weight values for the learning algorithm
			networkAttributes.initWeightsLowLmt		= WEIGHT_CD_LEARN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_CD_LEARN_UPLMT;
			break;
		}
		case (short)IOType::eDiscreteDiscrete:
		{
			networkAttributes.outputActvFunction	= ActivationTypes::eStep;
			networkAttributes.initWeightsLowLmt		= WEIGHT_DD_GEN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_DD_GEN_UPLMT;
			DatasetGenImmediateReinforceController	gen(networkAttributes);

			isChoiceKinematic((RunType)runChoice) ?
													gen.LoadDataset((RunType)runChoice, (EnvType)envChoice)
													: 
													gen.GenerateDiscreteDiscreteDS((EnvType)envChoice);

			// Set initial weight values for the learning algorithm
			networkAttributes.initWeightsLowLmt		= WEIGHT_DD_LEARN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_DD_LEARN_UPLMT;
			break;
		}
		default:
			std::cout << "Choice not supported!! \n";
		break;
	}

	// Run Experiments to learn datasets
	Experiment exp(networkAttributes, ReinforceType::eImmediate, (EnvType)envChoice, (IOType)stateActionChoice);
	exp.Run();

	return result;
}

bool RunDelayedReinforce(short runChoice, short envChoice, short stateActionChoice)
{
	bool				result = true;
	NetworkAttributes	networkAttributes = {
													0,		// To be set later
													0,		// To be set later
													0,		// To be set later
													0,		// To be set later
													ACTV_LAMBDA,
													ActivationTypes::eSigmoid, // To be set later
													ActivationTypes::eSigmoid,
													0.0,	// To be set later
													0.0		// To be set later
	};

	SetNetworkBasicAttributes(runChoice, networkAttributes);

	// Generate Datasets
	switch (stateActionChoice)
	{
		case (short)IOType::eDiscreteContinuous:
		{
			networkAttributes.outputActvFunction	= ActivationTypes::eSigmoid;
			networkAttributes.initWeightsLowLmt		= WEIGHT_DC_GEN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_DC_GEN_UPLMT;
			DatasetGenDelayedReinforceController	gen(networkAttributes);

			gen.GenerateDiscreteContinuousDS((EnvType)envChoice);

			// Set initial weight values for the learning algorithm
			networkAttributes.initWeightsLowLmt		= WEIGHT_DC_LEARN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_DC_LEARN_UPLMT;
			break;
		}
		case (short)IOType::eContinuousContinuous:
		{
			networkAttributes.outputActvFunction	= ActivationTypes::eSigmoid;
			networkAttributes.initWeightsLowLmt		= WEIGHT_CC_GEN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_CC_GEN_UPLMT;
			DatasetGenDelayedReinforceController	gen(networkAttributes);

			gen.GenerateContinuousContinuousDS((EnvType)envChoice);

			// Set initial weight values for the learning algorithm
			networkAttributes.initWeightsLowLmt		= WEIGHT_CC_LEARN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_CC_LEARN_UPLMT;
			break;
		}
		case (short)IOType::eContinuousDiscrete:
		{
			networkAttributes.outputActvFunction	= ActivationTypes::eStep;
			networkAttributes.initWeightsLowLmt		= WEIGHT_CD_GEN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_CD_GEN_UPLMT;
			DatasetGenDelayedReinforceController	gen(networkAttributes);

			gen.GenerateContinuousDiscreteDS((EnvType)envChoice);

			// Set initial weight values for the learning algorithm
			networkAttributes.initWeightsLowLmt		= WEIGHT_CD_LEARN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_CD_LEARN_UPLMT;
			break;
		}
		case (short)IOType::eDiscreteDiscrete:
		{
			networkAttributes.outputActvFunction	= ActivationTypes::eStep;
			networkAttributes.initWeightsLowLmt		= WEIGHT_DD_GEN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_DD_GEN_UPLMT;
			DatasetGenDelayedReinforceController	gen(networkAttributes);

			gen.GenerateDiscreteDiscreteDS((EnvType)envChoice);

			// Set initial weight values for the learning algorithm
			networkAttributes.initWeightsLowLmt		= WEIGHT_DD_LEARN_LOWLMT;
			networkAttributes.initWeightsUpLmt		= WEIGHT_DD_LEARN_UPLMT;
			break;
		}
		default:
			std::cout << "Choice not supported!! \n";
		break;
	}

	// Run Experiments to learn datasets
	Experiment exp(networkAttributes, ReinforceType::eDelayed, (EnvType)envChoice, (IOType)stateActionChoice);
	exp.Run();

	return result;
}

int main()
{
	short				runChoice			= 0;
	short				reinforceChoice		= 0;
	short				envChoice			= 0;
	short				stateActionChoice	= 0;

	std::cout << "Welcome to William's REINFORCE with SUN Implementation!\n";

	std::cout << "Enter:\n";
	std::cout << "1  - 3  x 3   Linear\n";
	std::cout << "2  - 30 x 30  Linear\n";
	std::cout << "3  - 3  x 3   NonLinear \n";
	std::cout << "4  - 30 x 30  NonLinear \n";
	std::cout << "5  - 3  x 3   NonLinear Forward Kinematics \n";
	std::cout << "6  - 3  x 3   NonLinear Inverse Kinematics \n";
	std::cout << "7  - 12 x 3   NonLinear Forward Kinematics \n";
	std::cout << "8  - 12 x 3   NonLinear Inverse Kinematics \n";
	std::cout << "9  - 3  x 12  NonLinear Forward Kinematics \n";
	std::cout << "10 - 3  x 12  NonLinear Inverse Kinematics \n";
	std::cout << "11 - 12 x 12  NonLinear Forward Kinematics \n";
	std::cout << "12 - 12 x 12  NonLinear Inverse Kinematics \n";
	std::cout << "13 - 21 x 21  NonLinear Forward Kinematics \n";
	std::cout << "14 - 21 x 21  NonLinear Inverse Kinematics \n";
	std::cout << "15 - 30 x 30  NonLinear Forward Kinematics \n";
	std::cout << "16 - 30 x 30  NonLinear Inverse Kinematics \n";
	std::cout << "17 - 3  x 21  NonLinear Forward Kinematics \n";
	std::cout << "18 - 3  x 21  NonLinear Inverse Kinematics \n";
	std::cout << "19 - 3  x 30  NonLinear Forward Kinematics \n";
	std::cout << "20 - 3  x 30  NonLinear Inverse Kinematics \n";
	std::cout << "21 - 21 x 3   NonLinear Forward Kinematics \n";
	std::cout << "22 - 21 x 3   NonLinear Inverse Kinematics \n";
	std::cout << "23 - 30 x 3   NonLinear Forward Kinematics \n";
	std::cout << "24 - 30 x 3   NonLinear Inverse Kinematics \n";
	std::cout << "25 - 6  x 6   NonLinear Forward Kinematics \n";
	std::cout << "26 - 6  x 6   NonLinear Inverse Kinematics \n";
	std::cout << "27 - 3  x 6   NonLinear Forward Kinematics \n";
	std::cout << "28 - 6  x 3   NonLinear Inverse Kinematics \n";
	std::cout << "29 - 24  x 6  NonLinear Inverse Kinematics \n";
	std::cin >> runChoice;

	std::cout << "Enter:\n";
	std::cout << "1 - Immediate Reinforcement \n";
	std::cout << "2 - Delayed Reinforcement \n";
	std::cin >> reinforceChoice;

	std::cout << "Enter:\n";
	std::cout << "1 - Static Environment \n";
	std::cout << "2 - Dynamic Environment \n";
	std::cin >> envChoice;

	std::cout << "Enter:\n";
	std::cout << "1 - Input: Discrete,   Output: Continuous \n";
	std::cout << "2 - Input: Continuous, Output: Continuous \n";
	std::cout << "3 - Input: Continuous, Output: Discrete \n";
	std::cout << "4 - Input: Discrete,   Output: Discrete \n";
	std::cin >> stateActionChoice;

	// Make sure to setup dir and file info first
	Logger::ConstructBasicDirFilePaths((RunType)runChoice, (EnvType)envChoice, (IOType)stateActionChoice);

	if ((ReinforceType)reinforceChoice == ReinforceType::eImmediate)
	{
		RunImmediateReinforce(runChoice, envChoice, stateActionChoice);
	}
	else
	{
		RunDelayedReinforce(runChoice, envChoice, stateActionChoice);
	}

	return 0;
}
