#ifndef UTIL
#define	UTIL

#include <fstream>
#include <vector>
#include <iostream>
#include <bitset>
#include <math.h>
#include <iomanip>

using namespace std;

fstream	outStream;


void OpenFile(string path)
{
	outStream.open(path, std::ios::out);
	if (!outStream.is_open())
	{
		cout << "Error opening file!" << endl;
	}
}

void CloseFile()
{
	if (outStream.is_open())
	{
		outStream.flush();
		outStream.close();
	}
}

void WriteVector(vector<double> vecVal, string title)
{
	if (vecVal.size() == 0)
	{
		cout << "Error: Vector of Size 0 can't be logged!" << endl;
	}

	outStream << title << "\t";

	for (int i = 0; i < vecVal.size(); i++)
	{
		outStream << vecVal[i];
		if (i < vecVal.size() - 1)
			outStream << "\t ";
	}
	outStream << endl;
}

static double roundDecimal(double value, int digits)
{
	double result = 0.0;
	if (value != 0.0)
	{
		double factor = value > 0.0 ? 0.5 : -0.5;
		//result = (floor(value * intPow(10, digits) + factor) / intPow(10, digits));
		result = value * pow(10, digits);
		result = result + factor;
		result = (int)result;
		result = result / pow(10, digits);
	}
	return result;
}

bool GetBin(int number, int numDigits, vector<double>& binary)
{
	bool			result = true;
	vector<double>	bin;
	int				quo = 0;
	int				rem = 0;
	int				remDigits = numDigits;

	if (number < 0 || numDigits < 1)
		return false;

	quo = number;
	while (quo > 1)
	{
		rem = quo % 2;
		quo = quo / 2;

		bin.push_back(rem);
		remDigits--;
	}
	bin.push_back(quo);
	for (int i = remDigits - 1; i > 0; i--)
	{
		bin.push_back(0);
	}
	//std::reverse(bin.begin(), bin.end());

	binary = bin;

	return result;
}

static vector<double> ConvertToBits(string dirNames, vector<double> data)
{
		vector<double>	result;
		int 			precision		= 0;
		int 			normalizeFac	= 0;
		int 			discInputsCount = 0;
		
		unsigned int ioCount		= 3; // assuming the 3 angles and 3 positions

		/*************************************************************************************
									Discrete Discrete
		**************************************************************************************/
			// 12x12
		if (		dirNames == PATH_FWD_12_12_STATIC_DD
				||	dirNames == PATH_FWD_12_12_DYNAMIC_DD
				||	dirNames == PATH_INV_12_12_STATIC_DD
				||	dirNames == PATH_INV_12_12_DYNAMIC_DD)
		{
			precision 		= 1;
			normalizeFac	= 10;
			discInputsCount	= 4;
			
			for (unsigned int i = 0; i < data.size(); i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}
		}

			// 21x21
		else if (	dirNames == PATH_FWD_21_21_STATIC_DD
				||	dirNames == PATH_FWD_21_21_DYNAMIC_DD
				||	dirNames == PATH_INV_21_21_STATIC_DD
				||	dirNames == PATH_INV_21_21_DYNAMIC_DD)
		{ 
			precision 		= 2;
			normalizeFac	= 100;
			discInputsCount	= 7;
			
			for (unsigned int i = 0; i < data.size(); i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}		
		}

			// 30x30
		else if (	dirNames == PATH_FWD_30_30_STATIC_DD
				||	dirNames == PATH_FWD_30_30_DYNAMIC_DD
				||	dirNames == PATH_INV_30_30_STATIC_DD
				||	dirNames == PATH_INV_30_30_DYNAMIC_DD)
		{
			precision 		= 3;
			normalizeFac	= 1000;
			discInputsCount	= 10;
			
			for (unsigned int i = 0; i < data.size(); i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}		
		}

		/*************************************************************************************
									Continuous Discrete
		**************************************************************************************/
			// 3x12
		else if (	dirNames == PATH_FWD_3_12_STATIC_CD
				||	dirNames == PATH_FWD_3_12_DYNAMIC_CD
				||	dirNames == PATH_INV_3_12_STATIC_CD
				||	dirNames == PATH_INV_3_12_DYNAMIC_CD)
		{
			precision 		= 1;
			normalizeFac	= 10;
			discInputsCount	= 4;
			
			// push the Continuous numbers first
			for (unsigned int j = 0; j < ioCount; j++)
			{
				result.push_back(data[j]);
			}

			for (unsigned int i = ioCount; i < data.size(); i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}
		}

			// 3x21
		else if (	dirNames == PATH_FWD_3_21_STATIC_CD
				||	dirNames == PATH_FWD_3_21_DYNAMIC_CD
				||	dirNames == PATH_INV_3_21_STATIC_CD
				||	dirNames == PATH_INV_3_21_DYNAMIC_CD)
		{
			precision 		= 2;
			normalizeFac	= 100;
			discInputsCount	= 7;
			
			// push the Continuous numbers first
			for (unsigned int j = 0; j < ioCount; j++)
			{
				result.push_back(data[j]);
			}

			for (unsigned int i = ioCount; i < data.size(); i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}
		}

			// 3x30
		else if (	dirNames == PATH_FWD_3_30_STATIC_CD
				||	dirNames == PATH_FWD_3_30_DYNAMIC_CD
				||	dirNames == PATH_INV_3_30_STATIC_CD
				||	dirNames == PATH_INV_3_30_DYNAMIC_CD)
		{
			precision 		= 3;
			normalizeFac	= 1000;
			discInputsCount	= 10;
			
			// push the Continuous numbers first
			for (unsigned int j = 0; j < ioCount; j++)
			{
				result.push_back(data[j]);
			}

			for (unsigned int i = ioCount; i < data.size(); i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}
		}
		/************************************************************************************* 
									Discrete Continuous
		**************************************************************************************/
			// 12x3
		else if (	dirNames == PATH_FWD_12_3_STATIC_DC
				||	dirNames == PATH_FWD_12_3_DYNAMIC_DC
				||	dirNames == PATH_INV_12_3_STATIC_DC
				||	dirNames == PATH_INV_12_3_DYNAMIC_DC)
		{
			precision 		= 1;
			normalizeFac	= 10;
			discInputsCount	= 4;
			
			for (unsigned int i = 0; i < ioCount; i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}
			// push the rest of the numbers
			for (unsigned int j = ioCount; j < data.size(); j++)
			{
				result.push_back(data[j]);			
			}
		}

			// 21x3
		else if (	dirNames == PATH_FWD_21_3_STATIC_DC
				||	dirNames == PATH_FWD_21_3_DYNAMIC_DC
				||	dirNames == PATH_INV_21_3_STATIC_DC
				||	dirNames == PATH_INV_21_3_DYNAMIC_DC)
		{
			precision 		= 2;
			normalizeFac	= 100;
			discInputsCount	= 7;
			
			for (unsigned int i = 0; i < ioCount; i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}
			// push the rest of the numbers
			for (unsigned int j = ioCount; j < data.size(); j++)
			{
				result.push_back(data[j]);			
			}
		}

			// 30x3
		else if (	dirNames == PATH_FWD_30_3_STATIC_DC
				||	dirNames == PATH_FWD_30_3_DYNAMIC_DC
				||	dirNames == PATH_INV_30_3_STATIC_DC
				||	dirNames == PATH_INV_30_3_DYNAMIC_DC)
		{
			precision 		= 3;
			normalizeFac	= 1000;
			discInputsCount	= 10;
			
			for (unsigned int i = 0; i < ioCount; i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}
			// push the rest of the numbers
			for (unsigned int j = ioCount; j < data.size(); j++)
			{
				result.push_back(data[j]);			
			}
		}

			// 24x6
		else if (dirNames == PATH_INV_24_6_DYNAMIC_DC)
		{
			precision 		= 1;
			normalizeFac	= 10;
			discInputsCount	= 4;
			ioCount			= 6; // assuming the 6 (angles) by 6 (position and Orientation)

			for (unsigned int i = 0; i < ioCount; i++)
			{
				vector<double>	binary;
				double 			p 				= roundDecimal(data[i], precision);
				int 			n 				= p < 1.0 ? (int)(p * normalizeFac) : (int)p;
				
				GetBin(n, discInputsCount, binary);
				for (unsigned int j = 0; j < discInputsCount; j++)
				{
					result.push_back(binary[j]);				
				}
			}
			// push the rest of the numbers
			for (unsigned int j = ioCount; j < data.size(); j++)
			{
				result.push_back(data[j]);			
			}
		}

		return result;
}

#endif // UTIL
