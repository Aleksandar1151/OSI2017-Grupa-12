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
	cout << "[Registration]\n";
	do {
		
		cout << "Username:\n>";
		cin >> username;
		if (!checkUser(username))
		{
			do {
				cout << "Password:\n>";
				cin >> password;
			} while (password.length() != 4 && cout << "Password must have 4 characters!\nEnter new ");
			
			do {
				cout << "  User Group:\n" << "	Administrator---[ 1 ]" << endl << "	Analyst---------[ 2 ]\n>";
				cin >> group;
				if (group != 1 && group != 2) cout << "You must choose one of the groups - 1 or 2!\n";
			} while (group != 1 && group != 2);
			
		}
		else
		{
			cout << "Username already exist.\nEnter new ";
		}
	} while (password.length() != 4);
	
	ofstream myfile;

	myfile.open("codes.txt", ios_base::app);
	if (myfile.is_open())
	{
		system("CLS");
		myfile << endl  << username << " " << password << " " << group;
		cout << "\nUser created:\n Username: " <<  username << "\n Password: " << password << "\n Group: " << (group == 1 ? " Admin\n" : " Analyst\n") << endl;
		system("pause");
		system("CLS");
		myfile.close();
	}	
}

void login()
{
	string username, password;
	int group=0,option;// = 0;
	int flag;
	do
	{
		cout << "[LOGIN]\n";
		cout << "Username:\n>";
		cin >> username;
		flag = checkUser(username);
		cout << "Test flag: " << flag << endl;
		if (!flag) { cout << "Error, wrong username!\n\n"; }
		else
		{
			cout << "Password:\n>";
			cin >> password;
			flag = checkUser(username, password);
			group = checkUser(username, password);
			if (!flag) { cout << "Error, wrong password!\n\n"; group = 0; }		
			else if(username != "admin" && password.length() != 4) { cout << "\nError, no user!\n"; group = 0; system("pause"); }
		}		
		
		flag = 0;
		if(group) cout << "\nLogged in as [ " << username << " ]" << endl << endl;
		system("pause");
		system("CLS");
	} while(!group);
	
	if (group == 1)
	{
		do
		{
			//cout << "\n--> Login as Admin.\n";
			cout << "  Admin options:\n" << "	[ Change currency ]--------[ 1 ]" << endl << "	[ Create Account ]---------[ 2 ]" << endl << "	[ Delete Account ]---------[ 3 ] " << endl << "	[ Logout ]-----------------[ 4 ]" << endl <<"	[ Exit ]-------------------[ 5 ] \n >";
			cin >> option;
			system("CLS");
			if (option == 1) changeCurr();
			else if (option == 2) registration();
			else if (option == 3) deleteUser();
			else if (option == 4) 
			{	
				cout << "Logging out...\n"; 
				system("pause");
				system("CLS"); 
				login(); 
			}
			else if (option == 5) { cout << " Exit... \n"; }
			else cout << "Error, choose options form 1 to 4!\n";
		} while (option != 5);
				
	}
	else if (group == 2)
	{
		cout << "\n--> Login as Analiticar.\n";
		exportData();
		system("CLS");
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

int checkUser(string username) // Nije ti dobro ovdje resize. To kod kuæe riješi. Kad ukucaš alek, on skrati i line na alek i bude dobro ime. Napravi da line uèitava do prvog razmaka pa makar i sa onom while string[i++]
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