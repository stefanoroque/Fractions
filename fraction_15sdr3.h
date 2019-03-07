/*
 * fraction_15sdr3.h
 *
 *  Created on: Oct 14, 2018
 *      Author: stefanoroque
 *   Student #: 20009317
 */

#ifndef FRACTION_15SDR3_H_
#define FRACTION_15SDR3_H_

#include <string>
#include <iostream>

using namespace std;

// Class that will create the actual fractions
class Fraction {
	int n;
	int d;

	// Friend functions for comparison
	friend int compare(const Fraction& lhs, const Fraction& rhs);
	friend bool operator == (const Fraction lhs, const Fraction rhs);
	friend bool operator != (const Fraction lhs, const Fraction rhs);
	friend bool operator > (const Fraction lhs, const Fraction rhs);
	friend bool operator < (const Fraction lhs, const Fraction rhs);
	friend bool operator >= (const Fraction lhs, const Fraction rhs);
	friend bool operator <= (const Fraction lhs, const Fraction rhs);

	friend istream& operator >> (istream& in, Fraction& fract);
public:
	Fraction();    // Default constructor
	Fraction(int a);  // Single parameter constructor
	Fraction(int a, int b);  // Two parameter constructor

	static int gcd(int n, int m);

	int numerator() const;  // Accessor for the numerator
	int denominator() const;  //Accessor for the denominator

	// Overloading for member functions
	Fraction& operator ++ ();		// Pre-increment
	Fraction operator ++ (int); 	// Post-increment
	Fraction& operator += (Fraction& rhs);
};  // End of Fraction class

// Operator overloading for non-member functions
ostream& operator << (ostream& out, const Fraction& fract);
Fraction operator + (const Fraction& lhs, const Fraction& rhs);
Fraction operator - (const Fraction& lhs, const Fraction& rhs);
Fraction operator * (const Fraction& lhs, const Fraction& rhs);
Fraction operator / (const Fraction& lhs, const Fraction& rhs);
Fraction operator - (const Fraction& fract);


// This exception class is thrown if the user attempts to create a fraction with a zero value denominator
class FractionException{
	string message;
public:
	FractionException(string);
	string what();
};  // End of FractionException class

// Function that finds the index of a character in a string
int find_char_index(string str, char c);

#endif /* FRACTION_15SDR3_H_ */
