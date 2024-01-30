#include <iostream>
 
using namespace std;
 
int main()
{
    int a[10]= {1,5,8,9,12,15,17,18,20,25};
 
    int t=10;
 
    int* newA=new int[11];
 
    int i=0,flag=0;
    do
    {
        if(a[i]<=t)
            newA[i++]=a[i];
        else
        {
            if(flag)
                newA[i++]=a[i-flag];
            else
            {
                newA[i++]=t;
                flag=1;
            }
        }
    }
    while(i<11);
 
    for(int i=0; i<11; i++)
        cout << newA[i] << " ";
 
    delete [] newA;
 
    return 0;
}