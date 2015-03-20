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
    for (int i = 0; tempstring[i]!= 0; i++)//�ַ���ת��Ϊ���֣���ȡ�������
    {
        dom_number=dom_number * 10 + tempstring[i] - '0';
    }
    
    domain* domainCollection = new domain[dom_number];//����������ļ���
    for (int i = 0; i < dom_number; i++)
    {
        target_file.getline(tempstring, 1024);//��ȡһ�У������������᲻������ڴ�й©��
        domainCollection[i].Initialization(tempstring);//Initialization
    }
    //��ȡ�����е������Ϣ
    
    
    target_file.getline(tempstring, 1024);
    int variable_number = 0;
	DeleteFollowingSpaces(tempstring);
    for (int i = 0; tempstring[i] != 0; i++)//�ַ���ת��Ϊ���֣���ȡvariable������
    {
        variable_number = variable_number * 10 + tempstring[i] - '0';
    }
    variable* variableCollection = new variable[variable_number];
    for (int i = 0; i < variable_number; i++)
    {
        target_file.getline(tempstring, 1024);
        variableCollection[i].Initialization(tempstring,domainCollection);
    }
    //��ȡ�����еı�����Ϣ
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
        edgeMatrix[i] = new maxandmin[variable_number];//��ʼ���߽����
        for (int j = 0; j < variable_number; j++)
            yueshuMatrix[i][j] = -1;
    }//��ʼ���洢����Լ���ľ���-1����û��Լ�����Ǹ�������Լ���ı��
    for (int i = 0; i < yueshu_number; i++)
    {
        target_file.getline(tempstring, 1024);//��ȡһ��
		DeleteFollowingSpaces(tempstring);
        vector<int>* tempvector = StringToIntArray(tempstring);
        int a = (*tempvector)[1];
        int b = (*tempvector)[2];
        int c = (*tempvector)[3];
        yueshuMatrix[a][b] = yueshuMatrix[b][a] = c;
    }//����ֵ���
    for (int i = 0; i < variable_number; i++)
    {
        for (int j = 0; j < variable_number; j++)
        {
            if (yueshuMatrix[i][j] > -1)
            {
                //�ڱ���֮�д洢��֮�й����ı����ı��
                (variableCollection[i].GetVectorPointer())->push_back(j);
                //����֮���й�ϵ�Ļ����ʹ����Ͻ���½磬�����ʼ��
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
    }//max˳�� ��һ����xi �ڶ�����xj ��������xi��ֵ�����
    LSSBC1(domainCollection,variableCollection,constraintCollection,variable_number,yueshuMatrix,min,max);
	bool CanPass = true;
	vector<int> cannotFitInIndex;
	for (int i = 0; i < variable_number; i++)
	{
		bool flag = false;
		for (int j = 0; j < variableCollection[i].GetdomainSize(); j++)
		{
			if (variableCollection[i].getQ(j) == true)//��PENDINGLIST��û�б�ɾ��
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
		cout << "��������������Լ��" << endl;
	else
	{
		cout << "������粻������Լ����һ�¼�������������ɾ�գ�" << endl;
		for (int m = 0; m < cannotFitInIndex.size(); m++)
		{
			cout << cannotFitInIndex[m] << '\t';
		}
	}
    return 0;
};
