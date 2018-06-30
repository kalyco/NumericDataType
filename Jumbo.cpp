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
	cout << "unsigned create" << endl;
	cout << "value: " << value << endl;
	mLL = new SLinkedList;
	setLen(value);
	createList(value);
}

Jumbo::Jumbo(const string& s)
{
	cout << "string create" << endl;
  istringstream iss (s);
	if (iss) {
		string val;
		while(true) {
			iss >> val;
			if (iss.eof()) {
				break;
			}
		}
		mLen = val.length();
		mLL = new SLinkedList;
		for (int i=0; i<mLen; i++) {
			mLL->addBack(val[i] - 48); // from ASCII chars
		}
	} else {
		cerr << "no input found";
	}
}

void Jumbo::cleanup()
{
	cout << "cleanupp" << endl;
  mLL->removeAll();
	cout << "cleaned" << endl;
}

// Destructor
Jumbo::~Jumbo()
{
	cout << "destroid" << endl;
  cleanup();
}

// Copy constructor
Jumbo::Jumbo(const Jumbo& other) {
	cout << "copy" << endl;
	copy(other);
}

void Jumbo::copy(const Jumbo & other)
{
	if (other.mLen > 0) {
		cout << "copy. I've found the loop" << endl;
		cleanup();
		cout << "after cleanup" << endl;
		mLen = other.mLen;
		mLL = other.mLL;
		cout << "after reassign" << endl;
	}	
}

// Assignment operator
Jumbo& Jumbo::operator=(const Jumbo & other) {
	cout << "assign" << endl;
  if (this != &other) {
		cout << "not equal yo" << endl;
    copy(other);
		cout << "after copy" << endl;
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
		cout << "sum" << sum;
		if (sum == 0) {
			total[idx] = '0';
		} else {
			addToTotal(sum, idx, total);
		}
		cout << "total: " << total << endl;
		stringstream ss;
		string remainder = getRemainder(mAddend, oAddend);
		ss << remainder;
		ss >> total;
		cout << "remainder =" << remainder << endl;
		cout << "total" << total << endl;
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
	cout << "add to total" << endl;
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
	if (mLen == 0) return "0";
	for (int i=0; i < mLen; i++) {
		unsigned int v = mLL->nth(i);
		vals.append(to_string(v));
	}
	cout << "vals: " << vals << endl;
	return vals;
}

void Jumbo::createList(string s) {
	cout << "creating list";
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