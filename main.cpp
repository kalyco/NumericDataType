#include <iostream>
using namespace std;

#include "Jumbo.h"
	
int main() { 
  
  Jumbo total(0);	// (test integer constructor)
  
  while (true) { 
    string instr;  // user input 
    
    cout << "Running sum is: " << total.str() << endl << endl; // (test str() function)
    
    cout << "Add:  "; 	
    cin >> instr;
    
    Jumbo a = total; // create a from running total (test copy constructor)
    Jumbo b(instr); // create b from input (test string constructor)
    Jumbo c = a.add(b); // create c from adding a and b (test add function)
    
    total = c; // assign to total (test assignment operator)
  }
  return 0;
}

