#include "Functions.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void registration()
{
	string name, lastname, password;
	int group;
	cout << "Registracija:\n";
	cout << "Ime:\n>";
	cin >> name;
	cout << "Prezime:\n>";
	cin >> lastname;
	cout << "Password:\n>";
	cin >> password;
	cout << "Korisnicka grupa:\n";
	cout << "Administrator	[1]\n";
	cout << "Analiticar	[2]\n>";
	cin >> group;
	cout << endl << endl;

	/*if (group == 1)
	createAdmin();
	else if (group == 2)
	createAnlys();
	else cout << "Greska";*/

	cout << name << lastname << password << group;
}

int checkUser(string username, string password)
{
	std::string line1;
	std::string line2;
	line1 = username + " " + password;
	cout << line1;
	std::ifstream myfile ("codes.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line2))
		{
			if (line2.compare(line1) == 0)
				return 1;
		}
		myfile.close();
	}
	return 0;
}

int checkUser(string username)
{
	int n;
	n = username.length();
	string line;
	ifstream myfile("codes.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (username.compare(0, n, line))
			{
				return 0;
				myfile.close();
			}
		}
		myfile.close();
	}
	return 1;
}