#ifndef  AUTHSYSTEM_H
#define AUTHSYSTEM_H

#include<string>
using namespace std;

class AuthSystem
{
public:
	bool authenticate(string bayID, string password);
};

#endif // ! AUTHSYSTEM_H
