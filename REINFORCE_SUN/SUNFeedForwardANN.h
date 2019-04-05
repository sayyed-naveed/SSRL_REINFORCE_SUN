
/*****************************************************************************
******************************************************************************

					SUNFeedForwardANN inherits and overrides the 
					basic functionality of the FeedForwardANN.
					It mainly overrides Network Step Execution
					to additionally account for noise component.

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/

#pragma once
#ifndef _SUNFEEDFORWARDANN_H
#define _SUNFEEDFORWARDANN_H

#include "FeedForwardANN.h"

#include<vector>

using namespace std;

class SUNFeedForwardANN : FeedForwardANN
{
public:
	SUNFeedForwardANN(NetworkAttributes networkAttributes);
	~SUNFeedForwardANN();

	virtual vector<double> ExecuteStep(	vector<double>			inputs, 
										vector<vector<double>>	weightsMatrix, 
										vector<vector<double>>	noiseMatrix, 
										int						matrixSize,
										vector<double>	&		hiddenOutputs);

protected:

private:

};

#endif