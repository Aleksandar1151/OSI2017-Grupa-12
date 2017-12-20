#include "Functions.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	int p;
	string username, password;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	p = checkUser(username, password);
	cout << p;
	registration();
	
	system("pause");
	return 0;
}
/*Dule*/
