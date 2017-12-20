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
	string line1, line2;
	line1 = username + " " + password;
	ifstream myfile ("codes.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line2))
		{
			if (line1.compare(line2) == 0)
				return 1;
		}
		myfile.close();
		return 1;
	}
	else cout << "Error.";
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
		return 1;
	}
	else cout << "Error.";
}