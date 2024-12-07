#include"AuthSystem.h"
#include<iostream>

using namespace std;

const string correctBayId = "admin";
const string correctPassword = "lube123";

bool AuthSystem::authenticate(string bayID, string password)
{
	if (bayID == correctBayId && password == correctPassword) {
		return true; //Authentication sucessful
	}
	return false; //Authentication failed
}