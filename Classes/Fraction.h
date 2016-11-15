#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>

using std::string;

class Fraction
{
public:
// Operator overloading.
	friend Fraction operator+ (const Fraction&, const Fraction&);
	friend Fraction operator+= (Fraction&, const Fraction&);
	friend Fraction operator- (const Fraction&, const Fraction&);
	friend Fraction operator-= (Fraction&, const Fraction&);
	friend Fraction operator* (const Fraction&, const Fraction&);
	friend Fraction operator*= (Fraction&, const Fraction&);
	friend Fraction operator/ (const Fraction&, const Fraction&);
	friend Fraction operator/= (Fraction&, const Fraction&);
	friend std::ostream& operator<< (std::ostream&, const Fraction&);
	friend std::istream& operator>> (std::istream&, Fraction&);
	friend bool operator== (const Fraction&, const Fraction&);
	friend bool operator!= (const Fraction&, const Fraction&);
	friend bool operator< (const Fraction&, const Fraction&);
	friend bool operator<= (const Fraction&, const Fraction&);
	friend bool operator> (const Fraction&, const Fraction&);
	friend bool operator>= (const Fraction&, const Fraction&);

	// Temporary output.
	string cout_temp_addition_for_transmission() const;
	// Absolute value of a fraction.
	static Fraction Frac_abs(Fraction &);
	// Input a Fraction's numerator.
	void cin_num(long long);
	// Input a Fraction's denminator.
	void cin_den(long long);
public:
	// constructor function: numerator = 0, denominator = 1
	Fraction() = default;
	// constructor function: numerator = temp_a, denominator = 1.
	Fraction(long long const &temp_a) : numerator(temp_a) { }
	// constructor function: numerator = temp_a, denominator = 1 and reduction of a fraction.
	Fraction(long long const &temp_a, long long const &temp_b) : numerator(temp_a), denominator(temp_b) {
		rof();
	}
	~Fraction() = default;

private:
	long long numerator = 0;
	long long denominator = 1;

	// Greatest common factor.
	static long long gcd(long long, long long);
	// reduction of a fraction.
	void rof();
};

#endif
