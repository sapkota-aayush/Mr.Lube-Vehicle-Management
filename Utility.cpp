#include"Utility.h"
#include<iostream>

using namespace std;

bool isValidInput(const string& input)
{
	if (input.empty())
	{
		cout << "Input cannot be empty!" << endl;
		return false;
	}
	return true;
}

bool isValidLiscencePlate(const string& plate)
{
	if (plate.size() != 8)return false;
	for (int i = 0; i < 3; i++)
	{
		if (!isalpha(plate[i]) || !isupper(plate[i]))
		{
			return false;
		}
	}
	if (plate[3] != '-') return false;
	for (int i = 4; i < 8; ++i)
	{
		if (!isdigit(plate[i]))
		{
			return false;
		}
	}
	return true;
}


//Validate province
bool isValidProvince(const string& province)
{
	if (province == "ON" || province == "QB" || province == "AB" || province == "BC")
		return true;
	else
		return false;
}
