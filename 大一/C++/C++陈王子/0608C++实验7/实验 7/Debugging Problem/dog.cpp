// C++ How to Program
// Debugging Problem (dog.cpp)

#include <iostream>

using std::cout;
using std::endl;

#include "dog.hpp"

Dog::Dog( const int h, const int w, const char * n )
   : Animal( h, w )
{  strcpy( name, n ); }

void Dog::setName( const char * n ) { strcpy( name, n ); }

void Dog::Print() const
{
   cout << "The person is named: " << name << endl;
   print();
}

