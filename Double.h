#pragma once
#include <math.h>
#include <iostream>
#include <string>
#include <iomanip>
class Double
{
	bool sign;
	std::string exponent;
	std::string mantissa;

	int minusExponent;
	int maxMantissa = 13;
	int maxExponent = 11;

	double originalNumber;

	void InitNum(double num);
	void InitInf(double num);
	void InitZero();
	std::string SetExponent(int num);
	std::string SetMantissa(double num);
	std::string ExponentToBinary(int exp);
	std::string SetNum(int size, int num);

public:
	Double();
	Double(double num);
	Double(bool sign, std::string exponent, std::string mantissa);

	void Log();
	double GetDouble();
};

