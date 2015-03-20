#include "constraint.h"//Ԫ�鼯����
#include "tools.h"
#include <string>
int constraint::GetSize(void)
{
	return size;
}
int constraint::GetType(void)
{
	return type;
}
constraint::constraint()
{
}
void constraint::Initialization(char* dataLine)//���������Ӵ��ո���ַ���ֵ�ж�����ֵ����������
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
}
mypair* constraint::GetPairCollection(void)
{
	return pairCollection;
}