//=====================================
// б�Ʋ�2---����
//=====================================
#include<iostream>
using namespace std;
//-------------------------------------
int main(){
  string s;
  for(int n, m=0; cin>>s>>n; ){
    while(s.length()<2*n) 
      s += s;  // ��s���ӳ�ֱ�� >= 2n
    if(m++) cout<<"\n";
    for(int i=0; i<n; i++)
      cout<<s.substr(i,n)<<"\n";
  }
}//------------------------------------