#include "Functions.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void registration()
{
	string username, password;
	int group;
	cout << "Registracija:\n";
	/*cout << "Username:\n>";
	cin >> username; 
	cout << "Prezime:\n>";
	cin >> lastname;
	cout << "Password:\n>";*/
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

	//cout << name << lastname << password << group;
}

void login()
{}

int checkUser(string username, string password)
{
	string line1;
	string line2;
	int n ,group,q;

	line1 = username + " " + password;
	n = (int)line1.size();
	cout << "Unio si:" << line1;

	ifstream myfile;
	myfile.open("codes.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line2))
		{
			q = (int)line2.length(); q = q - 1;
			group = line2[q] - 48;
			line2.resize(n);
				if (line1.compare(line2) == 0)
				{
					myfile.close();
					return group;					
				}
		}
		myfile.close();
	}

	return 0;
}

int checkUser(string username)
{
	string name, password, line;
	int n = (int)username.size();
	int q,group;
	
	cout << "Duzina je: "<< n << "\n\n";
	ifstream myfile;
	myfile.open("codes.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			q = (int)line.length();
			cout << line << " Njegova duzina je " << q << endl;
			q = q - 1;
			group = line[q] - 48;			
			cout << "Grupa: " << group << endl;
			line.resize(n);
			if (username.compare(line) == 0)			
			{
				cout << line << " i " << username << "\n";
				myfile.close();				
				return group;
			}			
		}
		myfile.close();
	}
	return 0;
}

