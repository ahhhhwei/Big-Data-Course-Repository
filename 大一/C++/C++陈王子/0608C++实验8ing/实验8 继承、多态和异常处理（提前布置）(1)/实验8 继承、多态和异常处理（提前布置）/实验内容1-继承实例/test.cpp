#include "point.h"
#include "circle.h"
#include "cylinder.h"
//²âÊÔÖ÷º¯Êı
int main()
{ 
   Point point(3.5,6.4), *p;
   Circle circle(4,5,6), *cir;
   Cylinder cylinder(5,6,8), *cyl;
   
   cout<<point;
   cout<<circle;
   cout<<cylinder;
   
   p=&point;
   cir=&circle;
   cyl=&cylinder;
   cout<<(*p);
   cout<<(*cir);
   cout<<(*cyl);
  
   //+++++++++++++++++++
   cir->area();
   cir=&cylinder;
   cir->area();
   //+++++++++++++++++++

   return 0;
}
