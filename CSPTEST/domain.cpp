#include "domain.h"
#include "tools.h"
using namespace std;
domain::domain()
{}
void domain::SetSize(int tempsize)
{
	size = tempsize;
}
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
	vector<int>* buffervector = StringToIntArray(tstring);
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
}

int domain::IndexToValue(int index)
{
	return domain_numbers[index];
}

int domain::ValueToIndex(int Value)
{
	for (int i = 0; i < size; i++)
	{
		if (domain_numbers[i] == Value)
			return i;
	}
}