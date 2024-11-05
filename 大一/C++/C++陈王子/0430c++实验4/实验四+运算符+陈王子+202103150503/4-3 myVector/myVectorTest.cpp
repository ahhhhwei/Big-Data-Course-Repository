#include <iostream>
#include "myVector.hpp"
using namespace std;
int main()
{
	int a[10]={45,36,78,81,12,7,66,35,27,9},b[10]={23,16,76,98,43,88,26,90,41,8};
	int loop;
	myVector aArray,bArray,cArray;
	for(loop=0;loop<aArray.get_size();++loop)
	{	aArray[loop]=a[loop];
	                 bArray[loop]=b[loop]; 
	}
	aArray.display();	
                 bArray.display();
                cin>>cArray; //输入10个整型值
                ++cArray;
                cout<<cArray;
                
                cArray=aArray++;
                cout<<cArray;
                aArray.sort();
                cout<<aArray;

                cArray= -aArray;
                cArray.display();
                
	myVector dArray(aArray+bArray);
	cout<<dArray;

                cArray=aArray-bArray();
                cout<<cArray;
                 return 0;
}
