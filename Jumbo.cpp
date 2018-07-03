// Jumbo.cpp

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <istream>
#include <cmath> 
#include "Jumbo.h"

using namespace std;

Jumbo::Jumbo(unsigned int value)
{
	mLen = setLen(value);
	mLL = SLinkedList();
	setLen(value);
	createList(value);
}

Jumbo::Jumbo(const string& s)
{
	mLL = SLinkedList();
  istringstream iss (s);
	if (iss) {
		string val;
  	while (std::getline(iss, val)) {
			iss >> val;
			mLen = val.length();
			for (int i=0; i < mLen; i++) {
				int v = val[i] - 48;
				mLL.addBack(v);
			}
		}	
	} else {
		cerr << "no input found";
	}
	cout << str() << endl;
}

void Jumbo::cleanup()
{
}

// Destructor
Jumbo::~Jumbo()
{
	if (mLen > 0) {
  	cleanup();
	}	
}

// Copy constructor
Jumbo::Jumbo(const Jumbo& other) {
	copy(other);
}

void Jumbo::copy(const Jumbo & other)
{
	if (other.mLen > 0) {
		cleanup();
	}
	mLen = other.mLen;
	mLL = other.mLL;
}

// Assignment operator
Jumbo& Jumbo::operator=(const Jumbo & other) {
  if (this != &other) {
    copy(other);
  }
  return *this;
}

Jumbo Jumbo::add(const Jumbo& other) const {
	string bString = mLen >= other.mLen ? str() : other.str();
	string sString = mLen < other.mLen ? str() : other.str();
	if (sString == "0") return bString;

	unsigned long smallest = min(mLen, other.mLen);
	unsigned long biggest = max(mLen, other.mLen);
	unsigned long diff = (biggest - smallest);
	char * total = new char[biggest];
	for (int i=0; i < biggest; i++) {
		total[i] = '0';
	}
	for (int i=0; i < smallest + 1; i++) {
		int bIdx = biggest - i; // start backwards
		int sIdx = smallest - i;
		int sum = getASCIISum(bString[bIdx], sString[sIdx]);
		if (sum == 0) {
			total[i] = '0';
		} else {
			addToTotal(sum, bIdx, total);
		}
	}
	// for (int i=0; i < biggest; i++) {
	// 	cout << total[i] << endl;
	// }	
	setRemainder(diff, total, bString);
	Jumbo t(total);
	delete[] total;
	return t;
}

void Jumbo::addToTotal(int sum, int i, char * s) const {
	if (i < 0) {
		s[i] = '0' + s[i] + (sum % 10);
		return;
	}
	if (s[i] != '1' && s[i] != '0') {
		s[i] = '0';
	}
	s[i -1] = s[i-1] + (sum / 10);
	int t = s[i] + (sum % 10) - 48;
	if (t == 10 || t == 0) {
		if (t == 10) s[i-1] = '1';
		s[i] = '0';
	} else {
		s[i] = s[i] + sum % 10;
	}
}

void Jumbo::setRemainder(int len, char * res, string str) const {
	const char *cstr = str.c_str();
	addToTotal(cstr[len-1], len-1, res);
	for (int i = 0; i < len; i++) {
		res[i] = cstr[i];
	}
}

string Jumbo::str() const {
	string vals;
	string empty = "0";
	if (mLen == 0 && (mLL.front() == 0)) return empty;
	for (int i=0; i < mLen; i++) {
		int v = mLL.nth(i);
		vals.append(to_string(v));
	}
	return vals;
}

void Jumbo::createList(string s) {
	unsigned int nValue = 0; // convert to int if string
	stringstream sInt(s);
	sInt >> nValue;
	createList(nValue);
}

void Jumbo::createList(unsigned int n) {
	if (mLen == 0 || n == 0) {
		mLL.addFront(0);
		return;
	}
	int divisor = 1;
	for (int i=0; i < mLen; i++) {
		divisor = divisor * 10;
	}
	while (n > 0) {
		mLL.addFront(n/divisor);
		n = n%divisor;
		divisor = divisor / 10;
	}
}

int Jumbo::setLen(unsigned int n) {
	int len = 0;
	while(n > 0) {
		n = n/10;
		len++;
	}
	return len;
}

int Jumbo::getLen() const {
	return mLen;
}

int Jumbo::convertToASCII(char s) const {
	int a = s;
	return a - 48;
}

int Jumbo::getASCIISum(char c1, char c2) const {
	return convertToASCII(c1) + convertToASCII(c2);
}	