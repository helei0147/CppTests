#include <iostream>
#include <string>
using namespace std;
int BDtoNumber(string tempstring,int& offset);
bool IsNumber(char tempchar);
int ToNumber(int hole,bool isBlow,bool isKeydown);
string IntToString(int integer);
int keylist[48];
string IndexString(int number);
const string numberList[]= {"1","#1",
                            "2","#2","3","4","#4","5","#5","6","#6","7","8","#8"
                           };
int main()
{
    int keylist1[]= {0,1,2,3,4,5,5,6,7,8,9,10,12,13,11,12};
    int keylist2[16];
    int keylist3[16];
    for(int i=0; i<16; i++)
    {
        keylist2[i]=keylist1[i]+12;
        keylist3[i]=keylist2[i]+12;
    }
    for(int i=0;i<16;i++)
    {
        keylist[i]=keylist1[i];
        keylist[i+16]=keylist2[i];
        keylist[i+32]=keylist3[i];
    }//initialization
    string tempstring;
/*    cin>>tempstring;
    int offset=0;
    int tempnumber=BDtoNumber(tempstring,offset);*/
    for(int i=1;i<=12;i++)
    {
        int temp=0;
        cout<<"This is the "<<i<<" hole!"<<endl;
        if(i==10)
        {
            ;
        }
        string thisStringB=IntToString(i)+"B";
        string thisStringBBrace="("+thisStringB+")";
        string thisStringD=IntToString(i)+"D";
        string thisStringDBrace="("+thisStringD+")";
        cout<<thisStringB<<'\t'<<IndexString(BDtoNumber(thisStringB,temp))<<endl;
        temp=0;
        cout<<thisStringBBrace<<'\t'<<IndexString(BDtoNumber(thisStringBBrace,temp))<<endl;
        temp=0;
        cout<<thisStringD<<'\t'<<IndexString(BDtoNumber(thisStringD,temp))<<endl;
        temp=0;
        cout<<thisStringDBrace<<'\t'<<IndexString(BDtoNumber(thisStringDBrace,temp))<<endl;
        temp=0;
    }
    cout<<endl;
}
bool IsNumber(char tempchar)
{
    if(tempchar<='9'&&tempchar>='0')
        return true;
    else
        return false;
}
int BDtoNumber(string tempstring,int & offset)//one line , and modify the offset;
{
    if(offset==tempstring.size())
        return -1;//finished one line;
    bool keydown=false;
    bool isBlow=true;
    int tempNumber=0;
    int counter=0;
    //number converter;
    char numberTank[3];
    for(int i=0; i<3; i++)
        numberTank[i]=0;
    if(tempstring[offset]=='(')
    {
        offset++;
        keydown=true;
    }
    for(counter=0; IsNumber(tempstring[counter+offset]); counter++)
    {
        numberTank[counter]=tempstring[counter+offset];
    }
    offset+=counter;
    for(int i=0; numberTank[i]!=0; i++)
    {
        tempNumber=tempNumber*10+numberTank[i]-'0';
    }
    if(tempstring[offset]=='B'||tempstring[offset]=='b')
    {
        isBlow=true;
    }
    else if(tempstring[offset]=='D'||tempstring[offset]=='d')
    {
        isBlow=false;
    }
    offset++;
    if(keydown==true)
        offset++;
    int returnValue=ToNumber(tempNumber,isBlow,keydown);
    cout<<returnValue<<endl;
    return returnValue;
}
int ToNumber(int hole,bool isBlow,bool isKeydown)//return the index of key
{
    int block=(hole-1)/4;
    int offset=block*12;
    int temphole=hole-4*block;
    int tempkey=(temphole-1)*4;
    if(isBlow==true)
        ;
    else
        tempkey+=2;
    if(isKeydown==false)
        ;
    else
        tempkey++;
    return tempkey+offset;
}
string IndexString(int number)
{
    int blocks=number/12;
    if(blocks==0)
        return '('+numberList[number%12]+')';
    else if(blocks==1)
        return numberList[number%12];
    else if(blocks==2)
        return '['+numberList[number%12]+']';
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

