#include <iostream>
using namespace std;

void intersection(int a[];int b[];int m,int n){
    cout<<"交集："<<endl;
    for (int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(a[i]==b[j]){
                cout<<a[i]<<" ";
            }
        }
    }
    cout<<endl;
}

void union(int a[];int b[];int m,int n){
    cout<<"并集："<<endl;
    for (int i=0;i<m;i++){
        bool same=False;
        for(int j=0;j<n;j++){
            if(a[i]==b[j]){
                same=True;
                break;
            }
            else{
                cout<<a[i]<<" "<<b[j]<<" ";
            }
        }
        if(same){
            cout<<a[i]<<" ";
            same=False;
        }
    }
    cout<<endl;
}

void difference(int a[];int b[];int m,int n){
    cout<<"差集："<<endl;
    for (int i=0;i<m;i++){
        bool same=False;
        for(int j=0;j<n;j++){
            if(a[i]==b[j]){
                same=True;
                break;
            }
            else{
                cout<<a[i]<<" "<<b[j];
            }
        }
        if(same){
            cout<<a[i]<<" ";
            same=False;
        }
    }
    cout<<endl;
}

int main(){
    a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    b[20]={2,4,6,8,10,12,14,16,18,20,21,22,24,25,26,27,28,29,30};
    intersection(a,b,20,20);
    difference(a,b,20,20);
}