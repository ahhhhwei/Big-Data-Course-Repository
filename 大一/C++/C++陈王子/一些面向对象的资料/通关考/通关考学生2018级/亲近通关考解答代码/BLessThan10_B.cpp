//=====================================
// lessThan10.cpp
//=====================================
#include<iostream>
using namespace std;
//-------------------------------------
int main(){
  for(int a,b; cin>>a>>b; )
    if(a+b>10)
      cout<<"Refuse\n";
    else
      cout<<a+b<<"\n";
}//------------------------------------
 