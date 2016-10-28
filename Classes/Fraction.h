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

	string cout_temp_addition_for_transmission() const;                                      // Temporary output.
	static Fraction Frac_abs(Fraction &);                                                    // Absolute value of a fraction.
	void cin_num(long long);                                                                 // Input a Fraction's numerator.
	void cin_den(long long);                                                                 // Input a Fraction's denminator.
public:
	Fraction() = default;                                                                    // constructor function: numerator = 0, denominator = 1
	Fraction(long long temp_a) : numerator(temp_a) { }                                       // constructor function: numerator = temp_a, denominator = 1.
	Fraction(long long temp_a, long long temp_b) : numerator(temp_a), denominator(temp_b) {  // constructor function: numerator = temp_a, denominator = 1 and reduction of a fraction.
		rof();
	}
	~Fraction() = default;                                                                   // Destructor

private:
	long long numerator = 0;
	long long denominator = 1;

	long long gcd(long long, long long);                                                     // Greatest common factor
	void rof();                                                                              // reduction of a fraction
};

#endif
