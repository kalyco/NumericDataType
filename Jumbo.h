// Jumbo.h

#ifndef JUMBO_H 
#define JUMBO_H

#include "sll.h"
#include <iostream> 

using namespace std; 

class Jumbo {
 private:
  SLinkedList * mLL;
  size_t mLen;

  void copy(const Jumbo & other);
  void cleanup();

  void setLen(unsigned int n);
  void createList(string s);
  void createList(unsigned int n);
  int convertToASCII(char s) const;
  int getASCIISum(char c1, char c2) const;
  string getRemainder(string s1, string s2) const;
  void addToTotal(int sum, int i, char * s) const;

 public:

  // Create from an existing integer value 
  Jumbo( unsigned int value ); 	
  
  // Create from a string representation (e.g. '73287473284237842947328432423789427')
  Jumbo( const string& ); 
  
  // Copy constructor
  Jumbo(const Jumbo & other);
  
  // Destructor
  ~Jumbo();
		
  // Assignment variable
  Jumbo& operator=(const Jumbo & other);

  // Add the argument Jumbo to `this' one and return the result
  Jumbo add(const Jumbo&) const;

  // Convert value to a string for printing 
  string str() const;

  int getLen() const;
};

#endif