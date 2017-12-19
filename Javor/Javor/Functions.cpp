#include "Functions.h"
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
