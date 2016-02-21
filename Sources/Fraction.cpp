#include "Fraction.h"
#include <cmath>
#include <iostream>

long long Fraction::gcd(const long long numerator, const long long denominator) {  // method of successive division
	if (numerator < denominator)
		return gcd(denominator, numerator);
	if (numerator % denominator != 0)
		return gcd(denominator, numerator % denominator);
	else
		return denominator;
}

void Fraction::rof() {
	if (numerator) {
		long long g = gcd(abs(numerator), denominator);                                 // The g is greatest common divisor of two numbers.
		numerator /= g;
		denominator /= g;
	}
	else {
		denominator = 1;
	}
}

                                                                                  // Operator overloading.
Fraction operator + (const Fraction &frac1, const Fraction &frac2) {
	return Fraction(frac1.numerator * frac2.denominator + frac2.numerator * frac1.denominator, frac2.denominator * frac1.denominator);
}

Fraction operator += (Fraction &frac1, const Fraction &frac2) {
	frac1 = Fraction(frac1.numerator * frac2.denominator + frac2.numerator * frac1.denominator, frac2.denominator * frac1.denominator);
	return frac1;
}

Fraction operator - (const Fraction &frac1, const Fraction &frac2) {
	return Fraction(frac1.numerator * frac2.denominator - frac2.numerator * frac1.denominator, frac2.denominator * frac1.denominator);
}

Fraction operator -= (Fraction &frac1, const Fraction &frac2) {
	frac1 = Fraction(frac1.numerator * frac2.denominator - frac2.numerator * frac1.denominator, frac2.denominator * frac1.denominator);
	return frac1;
}

Fraction operator * (const Fraction &frac1, const Fraction &frac2) {
	return Fraction(frac1.numerator * frac2.numerator, frac2.denominator * frac1.denominator);
}

Fraction operator *= (Fraction &frac1, const Fraction &frac2) {
	frac1 = Fraction(frac1.numerator * frac2.numerator, frac2.denominator * frac1.denominator);
	return frac1;
}

Fraction operator / (const Fraction &frac1, const Fraction &frac2) {
	return Fraction(frac1.numerator * frac2.denominator, frac2.numerator * frac1.denominator);
}

Fraction operator /= (Fraction &frac1, const Fraction &frac2) {
	frac1 = Fraction(frac1.numerator * frac2.denominator, frac2.numerator * frac1.denominator);
	return frac1;
}

std::ostream& operator<< (std::ostream &os, const Fraction &frac) {
	Fraction frac_temp(frac.numerator, frac.denominator);
	os << frac_temp.numerator << "/" << frac_temp.denominator;
	return os;
}
std::istream& operator>> (std::istream &is, Fraction &frac) {
	is >> frac.numerator >> frac.denominator;
	return is;
}
bool operator == (const Fraction &frac1, const Fraction &frac2) {
	return (frac1.numerator * frac2.denominator) == (frac2.numerator * frac1.denominator);
}

bool operator != (const Fraction &frac1, const Fraction &frac2) {
	return !(frac1 == frac2);
}

bool operator < (const Fraction &frac1, const Fraction &frac2) {
	return (frac1.numerator * frac2.denominator) < (frac2.numerator * frac1.denominator);
}

bool operator <= (const Fraction &frac1, const Fraction &frac2) {
	return (frac1 < frac2) || (frac1 == frac2);
}

bool operator > (const Fraction &frac1, const Fraction &frac2) {
	return !(frac1 <= frac2);
}

bool operator >= (const Fraction &frac1, const Fraction &frac2) {
	return !(frac1 < frac2);
}
