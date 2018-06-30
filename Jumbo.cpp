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
	:mLen(0)
{
	mLL = new SLinkedList;
	cout << "setlen" << value << endl;
	setLen(value);
	createList(value);
}

Jumbo::Jumbo(const string& s)
{
  istringstream iss (s);
	if (iss) {
		string val;
  	while (std::getline(iss, val)) {
			iss >> val;
			cout << val << endl;
			// if (iss.eof()) {
			// 	break;
			// }
			mLen = val.length();
			mLL = new SLinkedList;
			for (int i=0; i<mLen; i++) {
				mLL->addBack(val[i] - 48); // from ASCII chars
			}
		}	
	} else {
		cerr << "no input found";
	}
}

void Jumbo::cleanup()
{
 delete mLL; 
}

// Destructor
Jumbo::~Jumbo()
{
  cleanup();
	delete this;
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
    copy(other);
  }
  return *this;
}

Jumbo Jumbo::add(const Jumbo& other) const {
	const string oAddend = other.str();
	string mAddend = str();
	int oLen = other.mLen;
	int smallest = mLen < oLen ? mLen : oLen; // Size of numbers to add
	int biggest = (mLen > oLen ? mLen : oLen) + 1; // Size of str array
	char * total = new char[biggest];
	for (int i=0; (mLen >= i && oLen > i); i++) {
		int idx = smallest - i;
		int sum = getASCIISum(oAddend[idx], mAddend[idx]);
		if (sum == 0) {
			total[idx] = '0';
		} else {
			addToTotal(sum, idx, total);
		}
		stringstream ss;
		string remainder = getRemainder(mAddend, oAddend);
		ss << remainder;
		ss >> total;
	}
	Jumbo t(total);
	delete[] total;
	return t;
}

void Jumbo::addToTotal(int sum, int i, char * s) const {
	if (i == 0) {
		s[i] = '0' + s[i] + (sum % 10);
		return;
	}
	s[i -1] = '0' + (sum / 10);
	s[i] = s[i] + (sum % 10);
}

string Jumbo::getRemainder(string s1, string s2) const {
	string bigger = s1.length() > s2.length() ? s1 : s2;
	int diff = bigger == s1 ? s1.length() - s2.length() : s2.length() - s1.length();
	return bigger.substr(0, diff + 1);
}

string Jumbo::str() const {
	string vals;
	string empty = "0";
	if (!mLen || mLen == 0) return empty;
	for (int i=0; i < mLen; i++) {
		if (mLL->getSize() >= i || mLL->getSize() == 0) break;
		int v = mLL->nth(i);
		cout << "v: " << v << endl;
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
	if (n == 0) {
		mLL->addFront(n);
		return;
	}
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
	cout << "mLen: " << mLen << endl;
}

int Jumbo::getLen() const {
	return (*this).mLen;
}

int Jumbo::convertToASCII(char s) const {
	int a = s;
	return a - 48;
}

int Jumbo::getASCIISum(char c1, char c2) const {
	return convertToASCII(c1) + convertToASCII(c2);
}	