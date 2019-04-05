
/*****************************************************************************
 ************* Class that provides all the Utilities including ***************
 *****************************************************************************

							 Random Number Generation
							 Statistics

**************************Author: Syed Naveed H Shah**************************
******************************************************************************/
#pragma once

#ifndef _UTIL_H
#define _UTIL_H

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <assert.h>
#include <random>

class Util
{
public:

	static double getNormalRandom(double mean, double stdDev)
	{
		double rNum = 0.0;
		random_device rd;
		default_random_engine generator(rd());
		normal_distribution<double> distribution(mean, stdDev);

		rNum = distribution(generator);

		return rNum;
	}

	///
	static double getUniformRandom(const double lowerBound, const double upperBound)
	{
		double rNum = 0.0;
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_real_distribution<> distribution(lowerBound, upperBound);

		rNum = distribution(gen);

		return rNum;
	}

	///
	static double getUniformRandomI(const int lowerBound, const int upperBound)
	{
		double rNum = 0.0;
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
		
		rNum = distribution(generator);

		return rNum;
	}

	///
	static double getRandom(const double lowerBound, const double upperBound, const int decimalPlaces)
	{
		if(upperBound <= lowerBound || decimalPlaces < 0)
			std::cout<<"ERROR: wrong values passed to the random generator"<<std::endl;

		int sign;

		if(upperBound<0)
			sign =-1;
		else
			sign = 1;

		int n = intPow(10, decimalPlaces);
		double r = double(rand())/ double(RAND_MAX);
		
		double a = r*(upperBound-lowerBound) + lowerBound;
				
		a = floor(a*n+0.5);	
		
		double result = a/n;

		assert(result<= upperBound && result >= lowerBound);

		return result*sign;
	}

	///
	static int intPow(int x, int p) {
		if (p == 0) return 1;
		if (p == 1) return x;
		return x * intPow(x, p-1);
	}

	///
	static int getRandomI(const int lowerBound, const int upperBound)
	{
		if(upperBound <= lowerBound)
			std::cout<<"ERROR: wrong values passed to the random generator"<<std::endl;

		int sign;

		if(upperBound<0)
			sign =-1;
		else
			sign = 1;

		
		int result = rand()%(upperBound - lowerBound) + lowerBound;

		assert(result<= upperBound && result >= lowerBound);

		return result*sign;
	}

	///
	static std::vector<int> toIntVector(std::vector<double> t_d)
	{
		std::vector<int> t_i;
		for (unsigned int i=0; i<t_d.size(); i++)
		{
			t_i.push_back((int)t_d[i]);
		}

		return t_i;
	}

	///
	static std::vector<double> toDoubleVector(std::vector<int> t_i)
	{
		std::vector<double> t_d;
		for (unsigned int i=0; i<t_i.size(); i++)
		{
			t_d.push_back((double)t_i[i]);
		}

		return t_d;
	}

	static double getAverage(int t_array[], int t_size)
	{
		double result = 0;
		for (int i = 0; i<t_size;i++)
		{
			result += t_array[i];
		}

		return result/t_size;
	}

	static std::vector<int> zeroVector(int vec_size)
	{	
		std::vector<int> res;
		for (int i=0; i<vec_size; i++)
		{
			res.push_back(0);
		}

		return res;
	}

	static long getFactorial(int number)
	{
		long product = 1;
		for(int i=number; i>1; i--)
			product *= i;
		return product;
	}

	static void findMinMax(double& min, double& max, double a, double b, double c)
	{
		min = max = a;
		if(min > b)
			min = b;
		if(min > c)
			min = c;

		if(max < b)
			max = b;
		if(max < c)
			max = c;

	}

	static double roundDecimal(double value, int digits)
	{
		double result = 0.0;
		if(value != 0.0)
		{
			double factor = value > 0.0 ? 0.5 : -0.5;
			//result = (floor(value * intPow(10, digits) + factor) / intPow(10, digits));
			result = value * intPow(10, digits);
			result = result + factor;
			result = (int)result;
			result = result / intPow(10, digits);
		}
		return result;
	}
};
	//template <typename T>
	//static int Get2DVectorSize(vector<vector<T>> vec)
	//{
	//	int size = 0;

	//	for (int i = 0; i < vec.size(); i++)
	//	{
	//		for (int j = 0; i < vec[i].size(); i++)
	//		{
	//			size++;
	//		}
	//	}
	//	
	//	return size;
	//}

#endif // end _UTIL_H