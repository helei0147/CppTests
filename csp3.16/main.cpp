#include <iostream>
#include "constraint.h"
#include "Model.h"
#include "pair.h"
#include "tools.h"
#include "value.h"
#include "variable.h"
#include "domain.h"
#include <fstream>
#include "maxmin.h"
#include "lssbc1.h"
using namespace std;

int main(void)
{
    ifstream target_file;
    target_file.open("little.txt");
    char* tempstring = new char[1024];
    target_file.getline(tempstring, 1024);
    int dom_number = 0;
	DeleteFollowingSpaces(tempstring);
    for (int i = 0; tempstring[i]!= 0; i++)//字符串转换为数字，读取域的数量
    {
        dom_number=dom_number * 10 + tempstring[i] - '0';
    }
    
    domain* domainCollection = new domain[dom_number];//创造所有域的集合
    for (int i = 0; i < dom_number; i++)
    {
        target_file.getline(tempstring, 1024);//读取一行，不过这样做会不会造成内存泄漏？
        domainCollection[i].Initialization(tempstring);//Initialization
    }
    //读取完所有的域的信息
    
    
    target_file.getline(tempstring, 1024);
    int variable_number = 0;
	DeleteFollowingSpaces(tempstring);
    for (int i = 0; tempstring[i] != 0; i++)//字符串转换为数字，读取variable的数量
    {
        variable_number = variable_number * 10 + tempstring[i] - '0';
    }
    variable* variableCollection = new variable[variable_number];
    for (int i = 0; i < variable_number; i++)
    {
        target_file.getline(tempstring, 1024);
        variableCollection[i].Initialization(tempstring,domainCollection);
    }
    //读取完所有的变量信息
    int yuanzuji_number = 0;
    target_file.getline(tempstring, 1024);
	DeleteFollowingSpaces(tempstring);
    for (int i = 0; tempstring[i] != 0; i++)
    {
        yuanzuji_number = yuanzuji_number * 10 + tempstring[i] - '0';
    }
    constraint* constraintCollection = new constraint[yuanzuji_number];
    for (int i = 0; i < yuanzuji_number; i++)
    {
        target_file.getline(tempstring, 1024);
        constraintCollection[i].Initialization(tempstring);
    }
    int yueshu_number = 0;
    target_file.getline(tempstring, 1024);
	DeleteFollowingSpaces(tempstring);
    for (int i = 0; tempstring[i] != 0; i++)
    {
        yueshu_number = yueshu_number * 10 + tempstring[i] - '0';
    }
    int** yueshuMatrix = new int*[variable_number];
    
    maxandmin** edgeMatrix = new maxandmin*[variable_number];
    for (int i = 0; i < variable_number; i++)
    {
        yueshuMatrix[i] = new int[variable_number];
        edgeMatrix[i] = new maxandmin[variable_number];//初始化边界矩阵
        for (int j = 0; j < variable_number; j++)
            yueshuMatrix[i][j] = -1;
    }//初始化存储所有约束的矩阵，-1代表没有约束，非负数代表约束的编号
    for (int i = 0; i < yueshu_number; i++)
    {
        target_file.getline(tempstring, 1024);//读取一行
		DeleteFollowingSpaces(tempstring);
        vector<int>* tempvector = StringToIntArray(tempstring);
        int a = (*tempvector)[1];
        int b = (*tempvector)[2];
        int c = (*tempvector)[3];
        yueshuMatrix[a][b] = yueshuMatrix[b][a] = c;
    }//矩阵赋值完成
    for (int i = 0; i < variable_number; i++)
    {
        for (int j = 0; j < variable_number; j++)
        {
            if (yueshuMatrix[i][j] > -1)
            {
                //在变量之中存储与之有关联的变量的编号
                (variableCollection[i].GetVectorPointer())->push_back(j);
                //变量之间有关系的话，就存在上界和下界，下面初始化
                int tempDomainIndex = variableCollection[j].GetDomainIndex();
                int tmax = domainCollection[tempDomainIndex].GetSize()-1;
                edgeMatrix[i][j].SetMax(tmax);
                edgeMatrix[i][j].SetMin(0);
            }
        }
    }
    int*** min = new int**[variable_number];
    for (int i = 0; i < variable_number; i++)
    {
        min[i] = new int*[variable_number];
    }
    for (int i = 0; i < variable_number; i++)
    {
        for (int j = 0; j < variable_number; j++)
        {
            int tempDomainIndex = variableCollection[i].GetDomainIndex();
            int tempsize=domainCollection[tempDomainIndex].GetSize();
            min[i][j] = new int[tempsize];
            for (int m = 0; m < tempsize; m++)
                min[i][j][m] = 0;
        }
    }
    
    int *** max = new int**[variable_number];
    for (int i = 0; i < variable_number; i++)
    {
        max[i] = new int*[variable_number];
    }
    for (int i = 0; i < variable_number; i++)
    {
        for (int j = 0; j < variable_number; j++)
        {
            int tempDomainIndex = variableCollection[i].GetDomainIndex();
            int tempsize = domainCollection[tempDomainIndex].GetSize();
            max[i][j] = new int[tempsize];
            for (int m = 0; m < tempsize; m++)
            {
                int k_size = domainCollection[variableCollection[j].GetDomainIndex()].GetSize();
                max[i][j][m] = k_size - 1;
            }
        }
    }//max顺序 第一个是xi 第二个是xj 第三个是xi中值的序号
    LSSBC1(domainCollection,variableCollection,constraintCollection,variable_number,yueshuMatrix,min,max);
	bool CanPass = true;
	vector<int> cannotFitInIndex;
	for (int i = 0; i < variable_number; i++)
	{
		bool flag = false;
		for (int j = 0; j < variableCollection[i].GetdomainSize(); j++)
		{
			if (variableCollection[i].getQ(j) == true)//在PENDINGLIST中没有被删除
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			cannotFitInIndex.push_back(i);
			CanPass = false;
		}
	}
	if (CanPass)
		cout << "这个网络可以满足约束" << endl;
	else
	{
		cout << "这个网络不能满足约束，一下几个变量的论域被删空：" << endl;
		for (int m = 0; m < cannotFitInIndex.size(); m++)
		{
			cout << cannotFitInIndex[m] << '\t';
		}
	}
    return 0;
};
