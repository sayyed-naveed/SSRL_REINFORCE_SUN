
/*****************************************************************************
******************************************************************************

		Class that provides Feed Forward Neural Network functionality

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _FEEDFORWARD_ANN_H_
#define _FEEDFORWARD_ANN_H_

#include <vector>
#include <assert.h>

using namespace std;

enum class ActivationTypes
{
	eSigmoid	= 0, // For continuous outputs
	eStep		= 1, // For discrete outputs
	eTanh		= 2, // In case we require output in negative range
};

typedef struct
{
	int				numInputs;
	int				numHiddenUnitsPerLayer;
	int				numHiddenLayers;
	int				numOutputs;
	double			actvLambda;
	ActivationTypes	outputActvFunction;
	ActivationTypes	hiddenActvFunction;
	double			initWeightsLowLmt;
	double			initWeightsUpLmt;
} NetworkAttributes;

class FeedForwardANN
{
public:
	FeedForwardANN(NetworkAttributes networkAttributes);
	~FeedForwardANN();

	virtual	vector<double> ExecuteStep(	vector<double>			inputs, 
										vector<vector<double>>	weightsMatrix,
										int						weightMatrixSize);

protected:
	double	ActivateValue(double value, ActivationTypes actvFunction);

	int		CalculateMatrixSize();

	NetworkAttributes		m_NetworkAttributes;
	int						m_WeightMatrixSize;

private:

};

#endif // _FEEDFORWARD_ANN_H_