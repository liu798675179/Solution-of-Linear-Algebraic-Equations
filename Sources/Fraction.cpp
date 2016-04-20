#include "Fraction.h"
#include <cmath>
#include <iostream>

long long Fraction::gcd(long long numerator, long long denominator) {  // method of successive division
	long long temp;
	if (numerator < denominator) {
		temp = denominator;
		denominator = numerator;
		numerator = temp;
	}
	while (denominator != 0) {
		temp = numerator % denominator;
		numerator = denominator;
		denominator = temp;
	}
	return numerator;
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
	os << frac_temp.numerator;						// When denominator is 1, do not output it.
	if (frac_temp.denominator != 1)
		os << "/" << frac_temp.denominator;
	return os;
}

std::istream& operator>> (std::istream &is, Fraction &frac) {
	is >> frac.numerator;
	if (is.get() != '/') {							// read denominator if and only if next char is '/'
		return is;
	}
	else {
		is >> frac.denominator;
	}
	is.get();								// use get() to clear the break
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

Fraction Fraction::Frac_abs(Fraction &temp_frac) {                                       // Absolute value of a fraction.
	return (temp_frac >= 0) ? temp_frac : (0 - temp_frac);
}
