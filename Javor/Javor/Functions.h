#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void registration();
void login();
int checkUser(string, string);
int checkUser(string);

void changeCurr();
void deleteUser();
void exportData(int);
bool ListDirectoryContents(const char* );


void CheckFormat1(const char *);
void CheckFormat4(const char *);
int All(double, int, const char *);
int pdv(double, int, const char *);
int Payment(double, double, int, const char *);
void Print1(int, const char *);
void PrintError(const char *);
void Print2(int, const char *);
void AddProcessed(const char *);
int BillProcessed(const char *);
int NumberOfLines(const char * sPath);
bool ListDirectoryContents(const char *);