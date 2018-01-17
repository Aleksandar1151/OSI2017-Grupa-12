#include "Functions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
#include <filesystem>
using namespace std;

void registration()
{
	string username, password;
	int group;

	cout << "[Registracija]\n\n";
	do {		
		cout << "Korisnicko ime:\n>";
		cin >> username;
		if (!checkUser(username))
		{
			do {
				cout << "PIN:\n>";
				cin >> password;
			} while (password.length() != 4 && cout << "PIN mora imati 4 broja!\nUnesi novi ");
			
			do {
				cout << "  Korisnicka grupa:\n" << "	Administrator---[ 1 ]" << endl << "	Analiticar------[ 2 ]\n>";
				cin >> group;
				if (group != 1 && group != 2) cout << "Morate izabrati jednu od grupa - 1 or 2!\n";
			} while (group != 1 && group != 2);
		}
		else{cout << "Korisnicko ime vec postoji.\nUnesite novo ";}
	} while (password.length() != 4);

	ofstream myfile;
	myfile.open("sifre.txt", ios_base::app);
	if (myfile.is_open())
	{
		system("CLS");
		myfile << endl  << username << " " << password << " " << group;
		cout << "\nRegistrovan korisnik:\n Korisnicko ime: " <<  username << "\n Sifra: " << password << "\n Korisnicka grupa: " << (group == 1 ? " Administrator\n" : " Analiticar\n") << endl;
		system("pause"); 
		system("CLS");
		myfile.close();
	}	
}
void login()
{
	goto label_1;

label_1:;
	string username, password;
	int group=0,option;
	int flag;


	do {
		cout << "[Prijava]\n\n";
		cout << "Korisnicko ime:\n>";
		cin >> username;
		flag = checkUser(username);
		if (!flag) { cout << "Greska, pogresno korisnicko ime!\n\n"; }
		else
		{
			cout << "Sifra:\n>";
			cin >> password;
			flag = checkUser(username, password);
			group = checkUser(username, password);
			if (!flag) { cout << "Greska, pogresna sifra!\n\n"; group = 0; }		
			else if(username != "admin" && username != "analiticar" && password.length() != 4) { cout << "\nGreska, nema korisnika!\n"; group = 0;}
		}		
		flag = 0;
		if(group) cout << "\nNa sistem je prijavljen [ " << username << " ]" << endl << endl;
		system("pause");
		system("CLS");
	} while(!group);

	if (group == 1)
	{
		do {
			cout << "Na sistem je prijavljen: [" << username << "]\n";
			cout << "Opcije administratora:\n" << "	[ Promijenite valutu ]--------[ 1 ]" << endl << "	[ Napravite novi nalog ]------[ 2 ]" << endl << "	[ Obrisite nalog ]------------[ 3 ] " << endl << "	[ Odjava ]--------------------[ 4 ]" << endl <<"	[ Izlaz ]---------------------[ 5 ] \n >";
			cin >> option;
			system("CLS");
			if (option == 1)
			{
				changeCurr();
				system("pause");
				system("CLS");
			}
			else if (option == 2) registration();
			else if (option == 3) deleteUser();
			else if (option == 4) 
			{	
				cout << "Odjavljivanje korisnika " << username << "...\n"; 
				system("pause");
				system("CLS"); 
				goto label_1;
			}
			else if (option == 5) { cout << "Izlaz iz programa... \n"; }
			else cout << "Greska, izaberite opcije od 1 do 5!\n";
		} while (option != 5);	
	}
	else if (group == 2)
	{
		ListDirectoryContents("..\\Racuni\\");
		system("pause");
		system("CLS");
		login();
	}
	else cout << "\nNedefinisana greska!\n";
}
int checkUser(string username, string password)
{
	string line1;
	string line2;
	int n ,group,q;
	line1 = username + " " + password;
	n = (int)line1.size();	

	ifstream myfile;
	myfile.open("sifre.txt");
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
	else cout << "Greska prilikom otvaranja sifre.txt\n";
	return 0;
}
int checkUser(string username) 
{
	string name, line, str;
	int n = (int)username.size();
	int q,group;
	
	ifstream myfile;
	myfile.open("sifre.txt");
	if (myfile.is_open()) 
	{
		while (getline(myfile, line))
		{
			q = (int)line.length();
			q = q - 1;
			group = line[q] - 48;			
			int i = 0;
			while (line[i] != ' ') i++;
			line.resize(i);
			if (username.compare(line) == 0)			
			{
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
	string currency;
	string header;
	int headerFlag = 1;
	string line;
	

	ifstream fin;
	fin.open("kuf.txt");
	ofstream temp;
	temp.open("temp.txt");
	cout << "Nova valuta\n> ";
	cin >> currency;


	if (fin.is_open())
	{
		getline(fin, header);
		while (getline(fin, line))
		{
			if (headerFlag) {	temp << header << endl; headerFlag = 0;	}
			int column = 10;
			size_t length = line.length();
			istringstream iss(line);
			string subs;
			while(column--) {iss >> subs;  }
			size_t lsubs = subs.length();
			line.replace(length - lsubs, lsubs, currency);
			temp << line << endl;
		}
		temp.close();
		fin.close();
		remove("kuf.txt");
		rename("temp.txt", "kuf.txt");
	}
	else cout << "Greska prilikom otvaranja kuf.txt\n";
	cout << "Valuta je promijenjena u " << currency<<endl<<endl;
	
}
void deleteUser()
{
	string deleteline;
	string line;
	string array;


	ifstream fin;
	fin.open("sifre.txt");
	ofstream temp;
	temp.open("temp.txt");
	cout << "Ime\n> ";
	cin >> deleteline;


	while (getline(fin, line))
	{
		istringstream iss(line);
		string subs;
		iss >> subs;

		if (subs != deleteline)
		{
			temp << line << endl;
		}
	}

	temp.close();
	fin.close();
	remove("sifre.txt");
	rename("temp.txt", "sifre.txt");
}
void exportData()
{
	/*

    string s = "Somewhere down the road";
    istringstream iss(s);

    do
    {
        string subs;
        iss >> subs;
        cout << "Substring: " << subs << endl;
    } while (iss);

	
	cout << "\nIspis racuna...(funkcija nije zavrsena)\n\n";*/
}

bool ListDirectoryContents(const char *sDir)
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	char sPath[2048];

	//Specify a file mask. *.* = We want everything!
	sprintf_s(sPath, "%s\\*.*", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		printf("Path not found: [%s]\n", sDir);
		return false;
	}

	do
	{
		//Find first file will always return "."
		//    and ".." as the first two directories.
		if (strcmp(fdFile.cFileName, ".") != 0
			&& strcmp(fdFile.cFileName, "..") != 0)
		{
			//Build up our file path using the passed in
			//  [sDir] and the file/foldername we just found:
			sprintf_s(sPath, "%s\\%s", sDir, fdFile.cFileName);

			//Is the entity a File or Folder?
			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				printf("Directory: %s\n", sPath);
				ListDirectoryContents(sPath); //Recursion, I love it!
			}
			else {
				//->printf("File: %s\n", sPath);
				string line;
				ifstream file;
				file.open(sPath, ios::in);

				while (getline(file, line))
				{
					cout << line << '\n';
				}
				file.close();

			}
		}
	} while (FindNextFile(hFind, &fdFile)); //Find the next file.

	FindClose(hFind); //Always, Always, clean things up!

	return true;
}