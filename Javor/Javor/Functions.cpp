#include "Functions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
#include <filesystem>
#include <ctype.h>
using namespace std;

void registration() // Funkcija za registraciju novih korisnika
{
	string username, password;
	int group;

	cout << "[Registracija]\n\n";
	do {		
		cout << "Korisnicko ime:\n>";
		cin >> username;
		if (!checkUser(username))
		{
			int flag = 1;
			while (flag) {
				flag = 0;
				cout << "PIN:\n>";
				cin >> password;
				if (password.length() != 4) flag = 1;
				else flag = 0;
				if (!isdigit(password[0])) flag = 1;
				else flag = 0;
				if (!isdigit(password[1])) flag = 1;
				else flag = 0;
				if (!isdigit(password[2])) flag = 1;
				else flag = 0;
				if (!isdigit(password[3])) flag = 1;
				if (flag) cout << "PIN mora imati 4 broja!\nUnesi novi ";
				else flag = 0;
			}
			
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
void login() // Funkcija za prijavu korisnika
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
			else if (option == 3)
			{
				deleteUser();
				system("pause");
				system("CLS");
			}
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
		//("..\\Debug\\Racuni\\");
		cout << "Racuni su obradjeni.\n";
		system("pause");
		system("CLS");

		do {
			cout << "Na sistem je prijavljen: [" << username << "]\n";
			cout << "Opcije analiticara:\n" << "	[ Pregled svih podataka za odredjenog kupca ]--------[ 1 ]" << 
				endl << "	[ Pregled svih podataka za odredjeni proizvod ]------[ 2 ]" << endl << "	[ Pregled ukupne prodaje za odredjeni mjesec ]-------[ 3 ] " << endl << "	[ Odjava ]-------------------------------------------[ 4 ]" << endl << "	[ Izlaz ]--------------------------------------------[ 5 ] \n >";
			cin >> option;
			system("CLS");
			if (option == 4)
			{
				cout << "Odjavljivanje korisnika " << username << "...\n";
				system("pause");
				system("CLS");
				goto label_1;
			}
			else if (option == 1 || option == 2 || option == 3) exportData(option);
			else if (option == 5) { cout << "Izlaz iz programa... \n"; }
			else cout << "Greska, izaberite opcije od 1 do 5!\n";
		} while (option != 5);

	}
	else cout << "\nNedefinisana greska!\n";
}
int checkUser(string username, string password) // Funkcija za provjeru korisnièkog imena i PIN-a
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
int checkUser(string username) // Funkcija za provjeru korisnièkog imena
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

void changeCurr() // Funkcija za promjenu valuta
{	
	string currency;
	string header;
	int headerFlag = 1;
	string line;
	

	ifstream fin;
	fin.open("Kuf.txt");
	ofstream temp;
	temp.open("temp.txt");
	cout << "Nova valuta\n> ";
	cin >> currency;

	ofstream fileCurrency;
	fileCurrency.open("Valuta.txt");
	if (fileCurrency.is_open())
		fileCurrency << currency << endl;


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
		remove("Kuf.txt");
		rename("temp.txt", "Kuf.txt");
	}
	else cout << "Greska prilikom otvaranja Kuf.txt\n";
	cout << "Valuta je promijenjena u " << currency<<endl<<endl;
	
}
void deleteUser() // Funkcija za brisanja korisnika
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

	cout << "Obrisano korisnik\n> " << deleteline << endl;

	temp.close();
	fin.close();
	remove("sifre.txt");
	rename("temp.txt", "sifre.txt");
}
void exportData(int option) // Funkcija za ispit podataka
{
	int noData = 0;
	string keyword;
	string line;
	string array;

	
	ifstream fkuf;
	fkuf.open("Kuf.txt");
	ofstream fout;

	if (option == 1)
	{
		cout << "Naziv kupca\n> "; cin >> keyword;
		fout.open("Pregled svih podataka za odredjenog kupca.txt");
		getline(fkuf, line);
		fout << line << endl << endl;
	
		while (getline(fkuf, line))
		{
			istringstream iss(line);
			string subs;
			iss >> subs;

			if (subs == keyword)
			{
				fout << line << endl;
				noData++;
			}
		}

		if (!noData) cout << "U KUF-u ne postoji kupac: " << keyword <<"." <<endl ;
		else cout << "Kreiran je ispis za kupca " << keyword << endl;
	}
	else if (option == 2)
	{
		cout << "Naziv proizvoda\n> ";
		//cin.ignore();
		getline(cin, keyword);
		
		fout.open("Pregled svih podataka za odredjen proizvod.txt");
		getline(fkuf, line);
		fout << line << endl << endl;

		while (getline(fkuf, line))
		{
			istringstream iss(line);
			string subs;
			string subs1;
			string subs2;
			iss >> subs1;
			iss >> subs1;
			iss >> subs2;

			subs.append(subs1);
			subs.append(" ");
			subs.append(subs2);



			if (subs == keyword)
			{
				fout << line << endl;
				noData++;
			}
		}

		if (!noData) cout << "U KUF-u ne postoji proizvod: " << keyword << "." << endl;
		else cout << "Kreiran je ispis za proizvod " << keyword << endl;
	}
	else if (option == 3)
	{
		cout << "Mjesec\n> "; cin >> keyword;
		fout.open("Pregled svih podataka za odredjeni mjesec.txt");
		getline(fkuf, line);
		fout << line << endl << endl;

		while (getline(fkuf, line))
		{
			istringstream iss(line);
			string subs;
			iss >> subs;
			iss >> subs;
			iss >> subs;
			iss >> subs;
			string temparray = subs;
			array = temparray.substr(3, 2);
			
			if (array == keyword)
			{
				fout << line << endl;
				noData++;
			}
			
		}

		if (!noData) cout << "U KUF-u ne postoji racun za proizvod u " << keyword << ". mjesecu." << endl;
		else cout << "Kreiran je ispis za " << keyword << " mjesec." << endl;
	}

	system("pause");
	system("CLS");
	
	fkuf.close();
	fout.close();
}



void CheckFormat1(const char *sPath) //PROVJERA RACUNA SA FORMATOM 1
{
	string line, p, k, c, u, d;
	double k1, c1, u1, q = 0;
	double s[20] = { 0 };
	int i = 0, n = 0, j, m, z;
	string::size_type sz;
	ifstream myfile;
	myfile.open(sPath, ios::in);
	if (myfile.is_open())
	{
		for (int lineno = 1; getline(myfile, line) && lineno < 6; lineno++)
			if (lineno == 6)
				cout << line << endl;
		while (getline(myfile, line))
		{
			if (line.compare(0, 39, "---------------------------------------") != 0)
			{
				n++;
				p = line;
				k = p.substr(11, 9);
				c = p.substr(21, 8);
				u = p.substr(30, 6);
				k1 = stod(k, &sz);
				c1 = stod(c, &sz);
				u1 = stod(u, &sz);
				s[i++] = u1;
				if (k1*c1 != u1)
				{
					PrintError(sPath);
					myfile.close();
				}
			}
			else
				myfile.close();
		}
		myfile.close();
	}
	for (int i = 0; i < 20; i++)
		q = q + s[i];
	j = All(q, n + 7, sPath);
	z = pdv(q, n + 8, sPath);
	m = Payment(q, q*0.17, n + 9, sPath);
	if ((j == 1) && (z == 1) && (m == 1))
	{
		Print1(n, sPath);
		AddProcessed(sPath);
	}
	else
	{
		PrintError(sPath);
	}
}
int All(double a, int n, const char* sPath) //ISCITAVANJE UKUPNOG IZNOSA SA RACUNA
{
	string line, s;
	double p;
	string::size_type sz;
	ifstream myfile;
	myfile.open(sPath, ios::in);
	if (myfile.is_open())
	{
		for (int lineno = 1; getline(myfile, line) && lineno < n; lineno++)
			if (lineno == n)
				cout << line << endl;
		if (getline(myfile, line))
		{
			s = line.substr(7, 4);
			p = stod(s, &sz);
			if (p == a)
				return 1;
			else
				return 0;
		}
		return 0;
		myfile.close();

	}
	return 0;
	myfile.close();
}
int pdv(double a, int n, const char * sPath) //ISCITAVANJE PDV-A SA RACUNA
{
	string line, s;
	double p, c;
	string::size_type sz;
	ifstream myfile;
	myfile.open(sPath, ios::in);
	if (myfile.is_open())
	{
		for (int lineno = 1; getline(myfile, line) && lineno < n; lineno++)
			if (lineno == n)
				cout << line << endl;
		if (getline(myfile, line))
		{
			s = line.substr(4, 6);
			p = stod(s, &sz);
			c = a * 0.17;
			if (c == p)
				return 1;
			else
				return 0;
		}
		return 0;
		myfile.close();
	}
	return 0;
	myfile.close();
}
int Payment(double a, double b, int n, const char * sPath) //ISCITAVANJE IZNOSA ZA PLACANJE
{
	string line, s;
	double p, i;
	string::size_type sz;
	ifstream myfile;
	myfile.open(sPath, ios::in);
	if (myfile.is_open())
	{
		for (int lineno = 1; getline(myfile, line) && lineno < n; lineno++)
			if (lineno == n)
				cout << line << endl;
		if (getline(myfile, line))
		{
			s = line.substr(19, 7);
			p = stod(s, &sz);
			i = a + b;
			if (p == i)
				return 1;
			else
				return 0;
		}
		return 0;
		myfile.close();
	}
	return 0;
	myfile.close();
}
void PrintError(const char * sPath) //ISPISIVANJE POGRESNOG RACUNA U ZASEBAN TXT FAJL
{
	string line;
	ifstream myfile;
	myfile.open(sPath, ios::in);
	ofstream file("Error.txt", ios::app);
	if (myfile.is_open())
	{
		if (file.is_open())
		{
			while (getline(myfile, line))
			{
				file << line << endl;
			}
		}
		file.close();
	}
	myfile.close();
}
void Print1(int m, const char * sPath)  //ISPIS PRVOG FORMATA U DATOTEKU KUF.TXT
{

	string line, kupac, datum, proizvod, kolicina, cijena, ukupno;
	string d, d1;
	double /*b, a, c,*/ pdv, u, k;
	int  n = 1;
	string::size_type sz;
	ifstream myfile;
	ifstream f("Valuta.txt");
	myfile.open(sPath, ios::app);
	ofstream file("Kuf.txt", ios::app);
	if (f.is_open())
	{
		if (getline(f, d))
			d1 = d.substr(0, 2);
	}
	f.close();
	if (myfile.is_open())
	{
		if (file.is_open())
		{
			while (getline(myfile, line))
			{
				n++;
				if (n == 2)
				{
					kupac = line.substr(7, 3);
				}
				if (n == 3)
				{
					datum = line.substr(7, 10);
				}
				if (n > 7 && n <= (7 + m))
				{
					if (line.compare(0, 39, "---------------------------------------") != 0)
					{
						proizvod = line.substr(0, 9);
						kolicina = line.substr(11, 9);
						cijena = line.substr(22, 7);
						ukupno = line.substr(31, 7);
						u = stod(ukupno, &sz);
						pdv = u * 0.17;
						k = pdv + u;
						file << kupac + "			" << proizvod << "	" << datum << "	" << kolicina << "		" << cijena << "		" << ukupno << "				" << pdv << "		" << k << "	" << d1 << endl;
					}
				}
			}
		}
	}
	file.close();
	myfile.close();
}
void CheckFormat4(const char* sPath) //PROVJERA RACUNA SA FORMATOM BROJ 4
{
	string line, p, k, c, u, d;
	double k1, c1, u1, q = 0;
	double s[20] = { 0 };
	int i = 0, n = 0, j, m, z;
	string::size_type sz;
	ifstream myfile;
	myfile.open(sPath, ios::in);
	if (myfile.is_open())
	{
		for (int lineno = 1; getline(myfile, line) && lineno < 7; lineno++)
			if (lineno == 7)
				cout << line << endl;
		while (getline(myfile, line))
		{
			if (line.compare(0, 39, "---------------------------------------") != 0)
			{
				n++;
				p = line;
				k = p.substr(11, 9);
				c = p.substr(21, 8);
				u = p.substr(30, 6);
				k1 = stod(k, &sz);
				c1 = stod(c, &sz);
				u1 = stod(u, &sz);
				s[i++] = u1;
				if (k1*c1 != u1)
				{
					PrintError(sPath);
					myfile.close();
				}
			}
			else
				myfile.close();
		}
		myfile.close();
	}
	for (int i = 0; i < 20; i++)
		q = q + s[i];
	j = All(q, n + 8, sPath);
	z = pdv(q, n + 9, sPath);
	m = Payment(q, q*0.17, n + 11, sPath);
	if ((j == 1) && (z == 1) && (m == 1))
	{
		Print2(n, sPath);
		AddProcessed(sPath);
	}
	else
	{
		PrintError(sPath);
	}

}
void Print2(int m, const char * sPath)  //ISPIS CETVRTOG FORMATA U DATOTEKU KUF.TXT
{
	string line, kupac, datum, proizvod, kolicina, cijena, ukupno;
	string d, d1;
	double /*b, a, c,*/ u, pdv, k;
	int  n = 1;
	string::size_type sz;
	ifstream f("Valuta.txt");
	ifstream myfile;
	myfile.open(sPath, ios::in);
	ofstream file("Kuf.txt", ios::app);
	if (f.is_open())
	{
		if (getline(f, d))
			d1 = d.substr(0, 2);
	}
	f.close();
	if (myfile.is_open())
	{
		if (file.is_open())
		{
			while (getline(myfile, line))
			{
				n++;
				if (n == 2)
				{
					kupac = line.substr(7, 3);
				}
				if (n == 3)
				{
					datum = line.substr(7, 10);
				}
				if (n > 8 && n <= (8 + m))
				{
					if (line.compare(0, 39, "---------------------------------------") != 0)
					{
						proizvod = line.substr(0, 9);
						kolicina = line.substr(11, 9);
						cijena = line.substr(22, 7);
						ukupno = line.substr(31, 7);
						u = stod(ukupno, &sz);
						pdv = u * 0.17;
						k = pdv + u;
						file << kupac + "			" << proizvod << "	" << datum << "	" << kolicina << "		" << cijena << "		" << ukupno << "				" << pdv << "		" << k << "	" << d1 << endl;
					}
				}
			}
		}
	}
	file.close();
	myfile.close();
}
void AddProcessed(const char * sPath)  //DODAVANJE OBRADJENO. U SVAKI RACUN KOJI JE ISPRAVAN
{
	ofstream myfile;
	myfile.open(sPath, ios::app);
	if (myfile.is_open())
	{
		myfile << endl;
		myfile << "OBRADJENO." << endl;
	}
	myfile.close();
}
int NumberOfLines(const char * sPath)  //PREBROJAVANJE LINIJA RACUNA
{
	int n = 1;
	string line;
	ifstream myfile;
	myfile.open(sPath, ios::in);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			n++;
		}
	}
	myfile.close();
	return n;
}
int BillProcessed(const char * sPath)  //PROVJERA DA LI JE RACUN VEC OBRADJEN
{
	string line;
	int a;
	int n = 1;
	a = NumberOfLines(sPath);
	string t;
	ifstream myfile;
	myfile.open(sPath, ios::in);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			n++;
			if (n == a)
			{
				if (line.compare(0, 10, "OBRADJENO.") == 0)
					return 0;
				else
					return 1;
			}
		}
	}
	return 0;
	myfile.close();
}
bool ListDirectoryContents(const char *sDir)  //CITANJE SVIH TXT. FAJLOVA IZ JEDNE DATOTEKE
{
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;

	int a;
	char sPath[2048];

	sprintf_s(sPath, "%s\\*.*", sDir);

	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		printf("Path not found: [%s]\n", sDir);
		return false;
	}

	do
	{
		if (strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0)
		{
			sprintf_s(sPath, "%s\\%s", sDir, fdFile.cFileName);

			if (fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
			{
				printf("Directory: %s\n", sPath);
				ListDirectoryContents(sPath);
			}
			else {

				a = BillProcessed(sPath);
				if (a != 0)
				{
					string line;
					string p;
					ifstream file;
					file.open(sPath, ios::in);
					if (file.is_open())
					{

						for (int lineno = 1; getline(file, line) && lineno < 5; lineno++)
							if (lineno == 4)
								p = line;
						file.close();
					}
					else cout << "Error.";
					if (p.compare(8, 5, "Racun") == 0)
						CheckFormat1(sPath);
					else if (p.compare(7, 10, "OSI Market") == 0)
					{
						CheckFormat4(sPath);
					}
					else
						cout << "Nepoznat format." << endl;

					while (getline(file, line))
					{


						cout << line << '\n';
					}
					file.close();
				}

			}
		}
	} while (FindNextFile(hFind, &fdFile));

	FindClose(hFind);

	return true;
}