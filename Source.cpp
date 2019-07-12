#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include <string>
#include <ctime>
#include "HeaderofStructs.h"
#include "HeaderofFile.h"
#include "HeaderofFunctions.h"
#include "HeaderofAnalysis.h"
using namespace std;
int prodnum, cargnum, stornum, ordnum, redsnum;
int main() {
	string str;
	loadFile();
	date today = todaydate();
	if (today.day == 30 && today != checkdate) sellAnalysis();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << "Enter What to Do?\n";
	cout << "(Add Store, Show and Edit Store, Add Cargo, Show and Edit Cargo,\n";
	cout << " Add Order, Delivered Order, Delivered ReducSell, Exit)\n";
	for (; ; ) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		getline(cin, str);
		if (str == "Exit") break;
		else if (str == "Add Store") addStore();
		else if (str == "Show and Edit Store") editStore();
		else if (str == "Add Order") addOrder();
		else if (str == "Add Cargo") addCargo();
		else if (str == "Show and Edit Cargo") editCargo();
		else if (str == "Delivered Order") deliveredOrder();
		else if (str == "Delivered ReducSell") deliveredReducSell();
		else if (str == "\n");
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
			cout << "Wrong Input!\n";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout << "Enter What to Do Next?\n";
	}
	saveFile();
	return 0;
}