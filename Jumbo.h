#ifndef JUMBO_H 
#define JUMBO_H

#include <iostream> 

using namespace std; 

class Jumbo { 
  
 private:

  /* You decicde what goes here */
  
 public:
  
  // Create from an existing integer value 
  Jumbo( unsigned int value ); 	
  
  // Create from a string representation (e.g. '73287473284237842947328432423789427')
  Jumbo( const string& ); 
		
  // Add the argument Jumbo to `this' one and return the result
  Jumbo add(const Jumbo&) const;		

  // Convert value to a string for printing 
  string str() const;

};

#endif
