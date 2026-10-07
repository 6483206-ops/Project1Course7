#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

struct stClientData {
	string AccountNumber;
	string PinCode;
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

vector<string> SplitString(string S1, string delim) {

	vector <string> vString;

	short pos = 0;
	string sWord;

	while ((pos = S1.find(delim)) != std::string::npos) {

		sWord = S1.substr(0, pos);
		if (sWord != "") {
			vString.push_back(sWord);
		}

		S1.erase(0, pos + delim.length());

	}

	if (S1 != " ") {
		vString.push_back(S1);
	}

	return vString;

}

stClientData ReadClientData() {
	stClientData CD;
	cout << "Enter Account Number? ";
	getline(cin >> ws, CD.AccountNumber);
	cout << "Enter PinCode? ";
	getline(cin, CD.PinCode);
	cout << "Enter Name? ";
	getline(cin, CD.Name);
	cout << "Enter Phone? ";
	getline(cin, CD.Phone);
	cout << "Enter Account Balance? ";
	cin >> CD.AccountBalance;

	return CD;
}

void AppendClientRecordToFile(string FileName, string Record) {

	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << Record << endl;
		MyFile.close();
	}


}

string CreateClientRecord(stClientData CD, string Diameter) {

	string Record = "";

	Record += (CD.AccountNumber + Diameter);
	Record += (CD.PinCode + Diameter);
	Record += (CD.Name + Diameter);
	Record += (CD.Phone + Diameter);
	Record += (to_string(CD.AccountBalance));

	return Record;

}

stClientData ParseRecordToClient(string Record, string Diameter = "/#/") {

	vector<string> vRecordData = { "" };
	vRecordData = SplitString(Record, Diameter);

	stClientData ClientData;

	if (vRecordData.size() == 0) {
		return ClientData;
	}

	ClientData.AccountNumber = vRecordData[0];

	if (vRecordData.size() >= 2) {
		ClientData.PinCode = vRecordData[1];
	}
	if (vRecordData.size() >= 3) {
		ClientData.Name = vRecordData[2];
	}
	if (vRecordData.size() >= 4) {
		ClientData.Phone = vRecordData[3];
	}
	if (vRecordData.size() >= 5) {
		ClientData.AccountBalance = stod(vRecordData[4]);
	}

	return ClientData;
}

void ReadClientsFromFile(string FileName, vector<stClientData>& vClients) {

	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string line = "";
		stClientData client;

		while (getline(MyFile, line)) {
			client = ParseRecordToClient(line);
			vClients.push_back(client);

		}

		MyFile.close();
	}

}

void PrintClientTableHeader(int Count) {
	const int totalWidth = 2 + 14 + 2 + 12 + 2 + 40 + 2 + 14 + 2 + 14 + 2; // compute rough width including separators
	cout << "\n\t\t\t\tClient List (" << Count << ") Client(s)." << endl;
	cout << string(totalWidth, '_') << "\n\n";
	cout << "| " << setw(14) << left << "Account Number"
		<< "| " << setw(12) << left << "Pin Code"
		<< "| " << setw(40) << left << "Client Name"
		<< "| " << setw(14) << left << "Phone"
		<< "| " << setw(14) << left << "Balance"
		<< " |" << endl;
	cout << string(totalWidth, '_') << "\n";
}

void PrintClientRow(stClientData& Client) {
	cout << "| " << setw(14) << left << Client.AccountNumber;
	cout << "| " << setw(12) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(14) << left << Client.Phone;
	cout << "| " << setw(14) << left << Client.AccountBalance << " |";
}

void PrintClientTable(vector <stClientData>& vClients) {
	PrintClientTableHeader(vClients.size());
	if (vClients.size() != 0) {
		for (size_t i = 0; i < vClients.size(); i++) {
			PrintClientRow(vClients[i]);
			cout << "\n";
		}
	}

	cout << "\nPress Enter to return to the Main Menu...";
	string _pause;
	// Consume any leftover newline and then wait for the user to press Enter
	getline(cin, _pause);
	getline(cin, _pause);
}

void InteractiveAddSingleClient(string FileName) {
	stClientData CD;
	CD = ReadClientData();
	AppendClientRecordToFile(FileName, CreateClientRecord(CD, "/#/"));
}

void InteractiveAddMultipleClients(string FileName) {
	char MoreClients = 'y';
	do {
		system("cls");
		cout << "Add new client : " << endl;
		InteractiveAddSingleClient(FileName);
		cout << "\nWant to add more client ? ";
		cin >> MoreClients;
	} while (toupper(MoreClients) == 'Y');

	cout << "\n\n The file content after added the client(s) : " << endl;
	DisplayAllClientsFromFile(FileName);
}

void DisplayAllClientsFromFile(string FileName) {

	vector <stClientData> vClients;
	ReadClientsFromFile(FileName, vClients);
	system("cls");
	PrintClientTable(vClients);
}

void WhatTheTask(string FileName,enTasks Task, bool& Is_End) {

	switch (Task) {
	case enTasks::ChowClientList :
		DisplayAllClientsFromFile(FileName);
		break;
	case enTasks::AddNewClient :
		InteractiveAddMultipleClients(FileName);
		break;


	}
	

}

void PrintTheMainMenu(enTasks& Task) {

	int n;

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
	cin >> n;
	Task = enTasks(n);
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

	string FileName = "ClientsData";

	while (true) {
		system("cls");
		enTasks Task;

		PrintTheMainMenu(Task);

		bool Is_End = false;
		WhatTheTask(FileName,Task, Is_End);

		if (Is_End) {

			PrintEndCaption();
			return;

		}

	}



}






int main() {

	StartTheProgram();

}