// How to Program
// Debugging Problem (dog.hpp)

#ifndef DOG_HPP
#define DOG_HPP

#include "dog.hpp"

class Dog : public Animal {
public:
   Person( const int, const int, const char * = "Toto");
   void Print() const;
   void setName( const char * );
private:
   char name[ 30 ];
};

#endif

