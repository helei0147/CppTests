#include "domain.h"
#include "tools.h"
using namespace std;
domain::domain()
{}
void domain::SetSize(int tempsize)
{
	size = tempsize;
}//大小的设定竟然不是根据数组的大小，这里可能会产生不匹配的错误？
int domain::GetSize(void)
{
	return size;
}
int domain::GetIndex(void)
{
	return domain_index;
}
void domain::SetIndex(int tempindex)
{
	domain_index = tempindex;
}
void domain::Initialization(char* tstring)
{
	vector<int>* buffervector = StringToIntArray(tstring);//转换为数组
	domain_index = (*buffervector)[0];
	size = (*buffervector)[1];
	for (int i = 0; i < size; i++)
	{
		int temp = (*buffervector)[2 + i];
		domain_numbers.push_back(temp);
	}
}
bool domain::IfInTheDomain(int target)
{
	for (int i = 0; i < size; i++)
	{
		if (domain_numbers[i] == target)
			return true;
	}
	return false;
}//遍历查找该值是否在论域中

int domain::IndexToValue(int index)
{
	return domain_numbers[index];
}//根据论域中的下标来获得值

int domain::ValueToIndex(int Value)
{
	for (int i = 0; i < size; i++)
	{
		if (domain_numbers[i] == Value)
			return i;
	}
}//遍历获得值在论域中的下标
