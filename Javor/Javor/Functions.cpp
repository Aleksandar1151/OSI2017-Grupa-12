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

	do {
		cout << "[Registration]\n";
		cout << "Username:\n>";
		cin >> username;
		cout << "Password:\n>"; 
		cin >> password;
		cout << "  User Group:\n" << "	Administrator---[ 1 ]" << endl << "	Analyst---------[ 2 ]\n>";
		cin >> group;
		if (password.length() != 4) cout << "Password must have 4 characters!\n";
	} while (password.length() != 4);
	
	ofstream myfile;

	myfile.open("codes.txt", ios_base::app);
	if (myfile.is_open())
	{
		myfile << endl  << username << " " << password << " " << group;
		cout << "\nU datoteku je upisano: " << username << " " << password << " " << group << endl;
		myfile.close();
	}	
	

}

void login()
{
	string username, password;
	int group,option;// = 0;
	do
	{
		cout << "[LOGIN]\n";
		cout << "Username:\n>";
		cin >> username;
		cout << "Password:\n>";
		cin >> password;
		group = checkUser(username, password);
		
		if ( username != "admin" && password.length() != 4) cout << "\nError, no user!\n";
	} while(!group);
	
	if (group == 1)
	{
		cout << "\n--> Login as Admin.\n";
		cout << "  Admin options:\n" << "	Change currency--------[ 1 ]" << endl << "	Create Account---------[ 2 ]" << endl << "	Delete Account---------[ 3 ] \n>";
		cin >> option;
		if (option == 1) changeCurr();
		else if (option == 2) registration();
		else if (option == 3) deleteUser();
		else cout << "Error, choose options form 1 to 3!\n";		
	}
	else if (group == 2)
	{
		cout << "\n--> Login as Analiticar.\n";
		exportData();
	}
	else cout << "\n--> Unidentified Error!\n";
}

int checkUser(string username, string password)
{
	string line1;
	string line2;
	int n ,group,q;

	line1 = username + " " + password;
	n = (int)line1.size();
	
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
	
	//cout << "Duzina je: "<< n << "\n\n";
	ifstream myfile;
	myfile.open("codes.txt");

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			q = (int)line.length();
			//cout << line << " Njegova duzina je " << q << endl;
			q = q - 1;
			group = line[q] - 48;			
			//cout << "Grupa: " << group << endl;
			line.resize(n);
			if (username.compare(line) == 0)			
			{
				//cout << line << " i " << username << "\n";
				myfile.close();				
				return group;
			}			
		}
		myfile.close();
	}
	return 0;
}

void changeCurr()
{
	cout << "Changing currency...(unfinished function)\n";
}
void deleteUser()
{
	cout << "Deleting user...(unfinished function)\n";
}

void exportData()
{
	cout << "Export data...(unfinished function)\n";
}