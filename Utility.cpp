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