#include "Double.h"

Double::Double() {
	minusExponent = pow(2, maxExponent - 1) - 1;

	this->mantissa = SetNum(maxMantissa, 0);
	this->mantissa[2] = '1';
	this->exponent = SetNum(maxExponent, 1);
	this->sign = 0;
	this->originalNumber = -1e9;
	Log();
}

Double::Double(double num) {
	originalNumber = num;
	minusExponent = pow(2, maxExponent - 1) - 1;
	if (num == 0) {
		InitZero();
	}
	else
	if (abs(num) == INFINITY) {
		InitInf(num);
	}
	else {
		sign = (num < 0);
		num = abs(num);

		InitNum(num);
	}
	Log();
}

Double::Double(bool sign, std::string exponent, std::string mantissa) :
	sign(sign),
	exponent(exponent),
	mantissa(mantissa) {
	minusExponent = pow(2, maxExponent - 1) - 1;
	originalNumber = -1e9;
	while (this->exponent.size() > maxExponent) this->exponent.erase(this->exponent.begin());
	while (this->mantissa.size() > maxMantissa) this->mantissa.erase(this->mantissa.begin());
	Log();
}

double Double::GetDouble()
{
	double mant = 1;
	double powT = 0.5;
	for (int i = 1; i < mantissa.size(); i++) {
		mant += int(mantissa[i]-'0') * powT;
		powT /= 2;
	}
	int exp = 0;
	powT = 1;
	for (int i = exponent.size() - 1; i >= 0; i--) {
		exp += int(exponent[i] - '0') * powT;
		powT *= 2;
	}
	exp -= minusExponent;
	if (exp == maxExponent + 1) return NAN;
	//std::cout << std::fixed << std::setprecision(400) << pow(-1, sign) << " " << pow(2, exp) << " " << mant <<" " << exp << std::endl;
	return pow(-1,sign)*pow(2, exp) * mant;
}

void Double::InitZero() {
	this->mantissa = SetNum(maxMantissa, 0);
	this->exponent = SetNum(maxExponent, 0);
	this->sign = 0;
}

void Double::InitInf(double num) {
	this->mantissa = SetNum(maxMantissa, 0);
	this->exponent = SetNum(maxExponent, 1);
	this->sign = (num < 0);
}

void Double::InitNum(double num) {
	int a = num;
	double mantisaN = num - a;
	std::string exponent = SetExponent(a);
	std::string mantisa = SetMantissa(mantisaN);

	int exp = exponent.size() - 1;
	if (exponent == "") {
		exp = 1;
		while (mantisa[0] == '0') {
			mantisa.erase(mantisa.begin());
			exp++;
		}
		exp *= -1;
	}
	exp += minusExponent;
	std::string fullNum = exponent + mantisa;

	while (fullNum.size() > maxMantissa) 
		fullNum.erase(fullNum.end() - 1);
	
	this->mantissa = fullNum;
	this->exponent = ExponentToBinary(exp);
}

std::string Double::ExponentToBinary(int exp) {
	std::string bin;
	while (exp > 0) {
		bin = char(exp % 2 + '0') + bin;
		exp /= 2;
	}
	return bin;
}

std::string Double::SetNum(int size, int num)
{
	std::string ans;
	while (size--) {
		ans += char(num + '0');
	}
	return ans;
}

std::string Double::SetExponent(int num) {
	std::string bin;
	while (num > 0) {
		bin = char(num % 2 + '0') + bin;
		num /= 2;
	}
	int exponent = bin.size() - 1;
	if (exponent > maxExponent) {
		std::cout << "Max Exponent\n ";
	}
	return bin;
}

std::string Double::SetMantissa(double num) {
	if (num == 0) return "";
	std::string bin;
	while (num!=1) {
		num *= 2;
		if (num - 1 > 0) {
			bin += '1';
			num -= 1;
		}
		else bin += '0';
	}
	return bin;
}

void Double::Log() {
	while (exponent.size() < maxExponent) exponent += '0';
	while (mantissa.size() < maxMantissa) mantissa += '0';

	if (originalNumber != -1e9)
	std::cout << "Original number: " << originalNumber << "\n";
	std::cout << "Sign:     " << sign << '\n';
	std::cout << "Exponent: " << exponent << '\n';
	mantissa.erase(mantissa.begin());
	std::cout << "Mantissa: (1)" << mantissa << '\n';
	mantissa = '1' + mantissa;
	std::cout << "Conversion: "  << GetDouble() << '\n';
	for (int i=0; i<30; i++) std::cout << char(196);
	std::cout << '\n';
}