#include "Fraction.h"
#include <cmath>
#include <sstream>

// Greatest common factor.
long long Fraction::gcd(long long numerator, long long denominator) {
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
		// The g is greatest common divisor of two numbers.
		auto g = gcd(abs(numerator), denominator);
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
	// When denominator is 1, do not output it.
	os << frac_temp.numerator;
	if (frac_temp.denominator != 1)
		os << "/" << frac_temp.denominator;
	return os;
}

std::istream& operator >> (std::istream &is, Fraction &frac) {
	is >> frac.numerator;
	// read denominator if and only if next char is '/'.
	if (is.get() != '/') {
		return is;
	}
	is >> frac.denominator;
	// use get() to clear the break.
	is.get();
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

// Absolute value of a fraction.
Fraction Fraction::Frac_abs(Fraction &temp_frac) {
	return (temp_frac >= 0) ? temp_frac : (0 - temp_frac);
}

// Input a Fraction's numerator.
void Fraction::cin_num(long long temp_a) {
	this->numerator = temp_a;
}

// Input a Fraction's denminator.
void Fraction::cin_den(long long temp_a) {
	this->denominator = temp_a;
}

// Temporary output.
string Fraction::cout_temp_addition_for_transmission() const {
	std::ostringstream out;
	out << *this;

	return out.str();
}          
