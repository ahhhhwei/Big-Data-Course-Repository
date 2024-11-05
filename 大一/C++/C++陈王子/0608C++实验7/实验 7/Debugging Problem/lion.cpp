// C++ How to Program
// Debugging Problem (lion.cpp)

#include <iostream>

using std::cout;
using std::endl;

#include "lion.hpp"


class Lion {
public:
   Lion( const int = 0, const int = 0 );
   void print() const;
};

Lion::Lion( const int h, const int w )
: Animal( h, w ) { }

void Lion::print() const
{
   cout << "This animal is a lion\n";
   print();
}

