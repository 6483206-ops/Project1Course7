#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

struct stClientData {
	string AccountNumper;
	string PINCode;
	string Name;
	string Phone;
	int AccountBalance;
	bool MarkOfDelete = false;
};

enum enTasks {
	ChowClientList = 1,
	AddNewClient = 2,
	DeleteClient = 3,
	UpdateClientInfo = 4,
	FindClient = 5,
	Exit = 6
};



void WhatTheTask(enTasks Task, bool& Is_End) {}

void PrintTheMainMenu(enTasks& Task) {

	string MainMenu = "Main Menue Screen";
	int LengthOfLine = 10 + MainMenu.length() + 10;
	cout << string(LengthOfLine, '=') << endl;
	cout << string(10, ' ') << MainMenu << string(10, ' ') << endl;
	cout << string(LengthOfLine, '=') << endl;
	cout << string(5, ' ') << "[1] Show Client List.\n";
	cout << string(5, ' ') << "[2] Add New Client.\n";
	cout << string(5, ' ') << "[3] Delete Client.\n";
	cout << string(5, ' ') << "[4] Update Client\n";
	cout << string(5, ' ') << "[5] Find Client.\n";
	cout << string(5, ' ') << "[6] Exit.\n";
	cout << string(LengthOfLine, '=') << endl;

	cout << "Chose what do you want to do? [1 to 6]? ";
}

void PrintEndCaption() {

	system("cls");

	string s = "\nThe Programe end ...........\n";
	int LengthOfLine = s.length() + 5 + 5;

	cout << string(LengthOfLine, '=') << endl;
	cout << string(5, ' ') << "\nThe Programe end ...........\n" << string(5, ' ') << endl;
	cout << string(LengthOfLine, '=') << endl;
}

void StartTheProgram() {

	while (true) {
		system("cls");
		enTasks Task;

		PrintTheMainMenu(Task);

		bool Is_End = false;
		WhatTheTask(Task, Is_End);

		if (Is_End) {

			PrintEndCaption();
			return;

		}

	}



}






int main() {

	string n = "l";
	PrintTheMainMenu();

}