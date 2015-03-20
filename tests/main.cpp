#include <iostream>
#include <vector>
using namespace std;
void Display(vector<int>* tempVector);
int main()
{
    vector<int> tempVector;
    tempVector.push_back(3);
    tempVector.push_back(4);
    Display(&tempVector);
    tempVector.clear();
    cout<<"vector after clear:"<<endl;
    Display(&tempVector);
    return 0;
}
void Display(vector<int>* tempVector)
{
    for(int i=0;i<tempVector->size();i++)
    {
        cout<<(*tempVector)[i]<<endl;
    }
}
