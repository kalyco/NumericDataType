// Jumbo.cpp

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "Jumbo.h"

using namespace std;

Jumbo::Jumbo(unsigned int value)
{
	setLen(value);
	createList(value);
}

Jumbo::Jumbo(const string& s)
{
	mLen = s.length();
	createList(s);
}

// Destructor
Jumbo::~Jumbo()
{
  cleanup();
}

void Jumbo::cleanup()
{
  mLL->removeAll();
}

// Copy constructor
Jumbo::Jumbo(const Jumbo& other) {
	copy(other);
}

void Jumbo::copy(const Jumbo & other)
{
	if (other.mLen > 0) {
		cleanup();
		mLen = other.mLen;
		mLL = other.mLL;
	}	
}

// Assignment operator
Jumbo& Jumbo::operator=(const Jumbo & other) {
  if (this != &other) {
    cleanup();
    copy(other);
  }
  return *this;
}


Jumbo Jumbo::add(const Jumbo& other) const {
	const string oAddend = other.str();
	string mAddend = str();

	int oLen = other.mLen;
	int smallest = mLen < oLen ? mLen : oLen; // Size of numbers to add
	int biggest = (mLen > oLen ? mLen : oLen) + 1; // Size of array
	bool overTen = false;
	for (int i=biggest; i > 0; i--) {
		int oAscii = convertToASCII(oAddend, i);
		int mAscii = convertToASCII(mAddend, i);
		int sum = oAscii + mAscii;
		mAddend[i-1] += sum / 10;
		mAddend[i] += sum % 10;
	}
	return mAddend;
}

void Jumbo::reverseList() {
	mLL->reverse();
}

string Jumbo::str() const{
	string vals;
	for (int i=0; i < mLen; i++) {
		unsigned int v = mLL->nth(i);
		vals.append(to_string(v));
	}
	return vals;
}

void Jumbo::createList(const string& s) {
	unsigned int nValue = 0; // convert to int if string
	stringstream sInt(s);
	sInt >> nValue;
	createList(nValue);
}

void Jumbo::createList(unsigned int n) {
	int divisor = 1;
	for (int i=0; i < mLen; i++) {
		divisor = divisor * 10;
	}
	while (n > 0) {
		mLL->addBack(n/divisor);
		n = n%divisor;
		divisor = divisor / 10;
	}
}

void Jumbo::setLen(unsigned int n) {
	int len = 0;
	while(n > 0) {
		n = n/10;
		len++;
	}
	mLen = len;
}

int Jumbo::getLen() const {
	return (*this).mLen;
}

int Jumbo::convertToASCII(string s, int idx) const {
	return static_cast<int>(s[idx]) - 48;
}