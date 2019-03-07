/*
 * fraction_15sdr3.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: stefanoroque
 *   Student #: 20009317
 */

#include "fraction_15sdr3.h"

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

// Constructor for the FileException class
FractionException::FractionException(string message) : message(message){
}
string FractionException::what(){
	return message;
}


// Default constructor
Fraction::Fraction() : n(0), d(1) {}
// Single argument constructor
Fraction::Fraction(int x) : n(x), d(1) {}
// Two argument constructor
Fraction::Fraction(int x, int y) {
	int normalized_x;
	int normalized_y;
	int greatest_common_d;

	if (y == 0) {
		throw FractionException("Illegal denominator (denominator of a fraction cannot be 0)");
	}

	// Make sure the denominator is always positive
	if (y < 0) {
			normalized_x = x * -1;
			normalized_y = y * -1;
	}
	else {
		normalized_x = x;
		normalized_y = y;
	}

	// Make sure fraction is stored in normalized state
	if((normalized_x != 0) && (normalized_y != 0)) {
		greatest_common_d = gcd(normalized_x, normalized_y);
		n = normalized_x / greatest_common_d;
		d = normalized_y / greatest_common_d;
	}
	else {
		n = normalized_x;
		d = normalized_y;
	}
}

int Fraction::gcd(int n, int m) {
	n = abs(n);
	m = abs(m);

	if (m <= n && (n % m) == 0) {
		return m;
	}
	else if (n < m) {
		return gcd (m, n);
	}
	else {
		return gcd(m, n%m);
	}
}

int Fraction::numerator() const{
	return n;
}

int Fraction::denominator() const{
	return d;
}

ostream& operator << (ostream& out, const Fraction& fract) {
	out << fract.numerator() << "/" << fract.denominator();
	return out;
}

istream& operator >> (istream& in, Fraction& fract){
	string str;
	in >> str;

	int index = find_char_index(str, '/');

	if(index != -1){
		// Fraction was entered
		int x, y;
		// Get numbers on either side of the '/' character
		x = stoi(str.substr(0, index));
		y = stoi(str.substr(index + 1, str.length()-1));
		fract.n = x;
		fract.d = y;
		return in;
	}
	// int was entered
	fract.n = stoi(str);
	fract.d = 1;
	return in;
}

int find_char_index(string str, char c) {
	for(int i = 0; i < str.length(); i++){
		if(str[i] == c)
			return i;
	}
	return -1;  // Character not found
}


Fraction operator + (const Fraction& lhs, const Fraction& rhs) {
	return Fraction((lhs.numerator() * rhs.denominator()) + (lhs.denominator() * rhs.numerator()), lhs.denominator() * rhs.denominator());
}

Fraction operator - (const Fraction& lhs, const Fraction& rhs){
	return Fraction((lhs.numerator() * rhs.denominator()) - (lhs.denominator() * rhs.numerator()), lhs.denominator() * rhs.denominator());
}

Fraction operator * (const Fraction& lhs, const Fraction& rhs){
	return Fraction(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

Fraction operator / (const Fraction& lhs, const Fraction& rhs) {
	return Fraction(lhs.numerator() * rhs.denominator(), lhs.denominator() * rhs.numerator());
}

Fraction operator - (const Fraction& fract) {
	return Fraction(-fract.numerator(), fract.denominator());
}

Fraction& Fraction::operator ++ () {  // Pre-increment
	n = n + d;
	return *this;
}

Fraction Fraction::operator ++ (int unused) {  // Post-increment
	Fraction clone(n, d);
	n = n + d;
	return clone;
}

Fraction& Fraction::operator += (Fraction& rhs){
	*this = *this + rhs;
	return *this;
}

int compare(const Fraction& lhs, const Fraction& rhs){

	double x;
	double y;
	double lhs_num;
	double lhs_denom;
	double rhs_num;
	double rhs_denom;

	lhs_num = lhs.numerator();
	lhs_denom = lhs.denominator();
	rhs_num = rhs.numerator();
	rhs_denom = rhs.denominator();

	// Get fractions into a decimal format
	x = lhs_num / lhs_denom;
	y = rhs_num / rhs_denom;

	if (x > y) {  // lhs > rhs
		return 1;
	}
	else if (x < y) {  // lhs < rhs
		return -1;
	}
	else {  // lhs = rhs
		return 0;
	}
}

bool operator == (const Fraction lhs, const Fraction rhs){
	if (compare(lhs, rhs) == 0) {
		return true;
	}
	return false;
}

bool operator != (const Fraction lhs, const Fraction rhs){
	if (compare(lhs, rhs) != 0) {
		return true;
	}
	return false;
}

bool operator > (const Fraction lhs, const Fraction rhs){
	if (compare(lhs, rhs) == 1) {
		return true;
	}
	return false;
}

bool operator < (const Fraction lhs, const Fraction rhs){
	if (compare(lhs, rhs) == -1) {
		return true;
	}
	return false;
}

bool operator >= (const Fraction lhs, const Fraction rhs){
	if ((compare(lhs, rhs) == 1) || (compare(lhs, rhs) == 0)) {
		return true;
	}
	return false;
}

bool operator <= (const Fraction lhs, const Fraction rhs){
	if ((compare(lhs, rhs) == -1) || (compare(lhs, rhs) == 0)) {
		return true;
	}
	return false;
}
