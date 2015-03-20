#include <iostream>
#include <string>
#include <vector>
using namespace std;
string IntToString(int integer);
int main()
{
    int i=10;
    cout<<IntToString(i)<<endl;
    return 0;
}
string IntToString(int integer)
{
    int tempinteger=integer;
    int counter=0;
    while(tempinteger>0)
    {
        tempinteger/=10;
        counter++;
    }
    char* mystring=new char[counter+1];
    for(int i=0;i<=counter;i++)
    {
        if(i==counter)
            mystring[i]=0;
        else
        {
            mystring[counter-i-1]=integer%10+'0';
            integer/=10;
        }
    }
    return string(mystring);
}
