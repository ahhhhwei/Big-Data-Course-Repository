// C++ How to Program
// Debugging Problem (animal.cpp)

#include <iostream>
#include <string>
using std::cout;
using std::endl;


class Animal {
public:
   Animal( const int = 0, const int = 0 );
   void print() const;
   int getHeight() const;
   int getWeight() const;
   void setHeight( int );
   void setWeight( int );
   const char * getName() const;
private:
   int height;
   int weight;
   string name;
};


Animal::Animal( const int h=0, const int w=0)
{
   height = h;
   weight = w;
}

void Animal::print() const
{
   cout << "This animal's height and weight are as follows\n"
        << "Height: " << height << "\tWeight: " << weight << endl << endl;
}

int Animal::getHeight() const { return height; }

int Animal::getWeight() const { return weight; }

void Animal::setHeight( const int h ) { height = h; }

void Animal::setWeight( const int w ) { weight = w; }

const char * Animal::getName() const { return name; }

