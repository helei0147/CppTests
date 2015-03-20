#include <iostream>
#include <string>
using namespace std;
const int KEYDOWN=1;
const int KEYUP=0;
int main()
{
    string testString;
    cout<<"Please enter the BD string"<<endl;
    cin>>testString;
    string newString;
    int pointer=0;
    for(int i=0;i<=testString.size();i++)
    {
        if(testString[i]='(')
        {
            int numPart=0;//数字部分的位数
            char numString[3];//数字部分的字符串，0结尾
            for(numPart=0;;numPart++)
            {
                if(testString[i+numPart]>='9'||testString[i+numPart]<='0')
                {
                    break;
                }
                numString[numPart]=testString[i+numPart];
            }
            numString[numPart]=0;
            int num=0;//数字部分的真实数字
            for(int counter=0;numString[counter]!=0;counter++)
            {
                num=num*10+numString[counter]-'0';
            }
            if(numString[i+numPart]=='B'||numString[i+numPart]=='b')
            {

            }
            else if(numString[i+numPart]=='D'||numString[i+numPart]=='d')
        }
    }
    return 0;
}
int KeyConverter(int holeIndex,char B_D,int keyState)
{
    int blockIndex=0;

    blockIndex=holeIndex/4;
    int offset=blockIndex*12;
    int index=holeIndex%4;
    if(holeIndex==0)
    {
        if(B_D=='B')
        {
            if(keyState==0)
                return
        }
    }
}
