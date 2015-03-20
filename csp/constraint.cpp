#include "constraint.h"//元组集的类
#include "tools.h"
#include <string>
int constraint::GetSize(void)
{
	return size;
}
int constraint::GetType(void)
{
	return type;
}//有两种类型的约束，存在约束，不允许存在的约束
constraint::constraint()
{
}//空的构造函数……
void constraint::Initialization(char* dataLine)//到底怎样从带空格的字符串值中读出数值啊啊啊啊啊
{
	std::vector<int>* buffervector = StringToIntArray(dataLine);
	serialNum = (*buffervector)[0];
	type = (*buffervector)[1];
	elements = (*buffervector)[2];
	firstDomain = (*buffervector)[3];
	secondDomain = (*buffervector)[4];
	size = (*buffervector)[5];
	pairCollection = new mypair[size];
	for (int i = 0; i < size; i++)
	{
		int tempfirst = (*buffervector)[5 + 2 * i];
		int tempsecond = (*buffervector)[5 + 2 * i + 1];
		pairCollection[i].SetFirst(tempfirst);
		pairCollection[i].SetSecond(tempsecond);
	}
}//转换函数并没有仔细检查
mypair* constraint::GetPairCollection(void)
{
	return pairCollection;
}
