#include "Functions.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
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
	goto label;
label:;
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
			if (option == 1) changeCurr();
			else if (option == 2) registration();
			else if (option == 3) deleteUser();
			else if (option == 4) 
			{	
				cout << "Odjavljivanje korisnika " << username << "...\n"; 
				system("pause");
				system("CLS"); 
				goto label; 
			}
			else if (option == 5) { cout << "Izlaz iz programa... \n"; }
			else cout << "Greska, izaberite opcije od 1 do 5!\n";
		} while (option != 5);	
	}
	else if (group == 2)
	{
		exportData();
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
	cout << "\nPromijena valute...(funkcija nije zavrsena)\n\n";
}
void deleteUser()
{
	cout << "\nBrisanje naloga...(funkcija nije zavrsena)\n\n";
}
void exportData()
{
	cout << "\nIspis racuna...(funkcija nije zavrsena)\n\n";
}