//��main�������ڵ��ļ��а���ͷ�ļ�header1.h:
#include <iostream>
#include"example2_header1.h"
#include "example2_header2.h"
//ע��Ҫ��˫���ţ���Ϊ�ļ�һ���Ƿ����û�Ŀ¼�е�
using namespace std;
int
main( )
{Student stud1(101,"Wang",18); //���������stud1
stud1.get_data( );
cout<<fun(5,3)<<endl;
return 0;
}