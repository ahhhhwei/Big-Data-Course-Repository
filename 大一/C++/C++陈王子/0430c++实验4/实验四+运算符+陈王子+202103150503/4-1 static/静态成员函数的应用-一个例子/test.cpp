#include "A.hpp"
int A::c=0;
int main()
{
   A  a, b(a);
   a.get_obj_num();
   a.ff(b);
  
   a.gg();
   a.get_obj_num();
   return 0;
}
