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
	bool MarkForDelete = false;
};

enum enTasks {
	ChowClientList = 1,
	AddNewClient = 2,
	DeleteClient = 3,
	UpdateClientInfo = 4,
	FindClient = 5,
	Exit = 6
};

vector<string> SplitString(string S1, string delim);
stClientData ReadClientData();
void PrintClientData(stClientData CD);
void AppendClientRecordToFile(string FileName, string Record);
string CreateClientRecord(stClientData CD, string Diameter);
stClientData ParseRecordToClient(string Record,string Diameter);
void WriteClientsToFile(string FileName, vector <stClientData>& vClients);
void ReadClientsFromFile(string FileName, vector<stClientData>& vClients);
void PrintClientTableHeader(int Count);
void PrintClientRow(stClientData& Client);
void PrintClientTable(vector <stClientData>& vClients);
void InteractiveAddSingleClient(string FileName);
void DisplayAllClientsFromFile(string FileName);
void InteractiveAddMultipleClients(string FileName);
int FindClientIndexInVector(vector <stClientData>& vClients, string AccountNumber);
void RemoveDeletedClientsFromVector(vector <stClientData>& vClients);
void MarkClientForDeletionInVector(vector <stClientData>& vClients, string AccountNumber, bool& deleteSuccess);
void DeleteClientFromFileByAccountNumber(string FileName, string AccountNumber, bool& deleteSuccess);
void InteractiveDeleteMultipleClients(string FileName);
stClientData FindClientInFileByAccountNumber(string FileName, string AccountNumber);
void FindClientByAccountNumber(string FileName);
void UpdateClientInVector(vector <stClientData>& vClients, string AccountNumber);
void UpdateClientInformation(string FileName);
void WhatTheTask(string FileName,enTasks Task, bool& Is_End);
void PrintTheMainMenu(enTasks& Task);
void PrintEndCaption();
void StartTheProgram();







int main() {

	StartTheProgram();

}













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

void PrintClientData(stClientData CD) {

	cout << "\n\n";

	cout << "Account Number : " << CD.AccountNumber << endl;
	cout << "Pin Code       : " << CD.PinCode << endl;
	cout << "Name           : " << CD.Name << endl;
	cout << "Phone          : " << CD.Phone << endl;
	cout << "Account Balance: " << CD.AccountBalance << endl;

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

void WriteClientsToFile(string FileName, vector <stClientData>& vClients) {

	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (int i = 0; i < vClients.size(); i++) {
			if (!vClients[i].MarkForDelete)
				MyFile << CreateClientRecord(vClients[i], "/#/") << endl;
		}
	}

}


void ReadClientsFromFile(string FileName, vector<stClientData>& vClients) {

	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string line = "";
		stClientData client;

		while (getline(MyFile, line)) {
			client = ParseRecordToClient(line,"/#/");
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

void DisplayAllClientsFromFile(string FileName) {

	vector <stClientData> vClients;
	ReadClientsFromFile(FileName, vClients);
	system("cls");
	PrintClientTable(vClients);
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

int FindClientIndexInVector(vector <stClientData>& vClients, string AccountNumber) {

	for (int i = 0; i < vClients.size(); i++) {
		if (vClients[i].AccountNumber == AccountNumber) return i;
	}

	return -1;
}

void RemoveDeletedClientsFromVector(vector <stClientData>& vClients) {
	vector <stClientData> vClients2;
	int count = 0;

	for (int i = 0; i < vClients.size(); i++) {
		if (vClients[i].MarkForDelete)
			continue;
		vClients2.push_back(vClients[i]);
		count++;
	}

	vClients = vClients2;

}

void MarkClientForDeletionInVector(vector <stClientData>& vClients, string AccountNumber, bool& deleteSuccess) {

	int clientIndex = FindClientIndexInVector(vClients, AccountNumber);

	if (clientIndex != -1) {
		vClients[clientIndex].MarkForDelete = true;
		deleteSuccess = true;
	}
	else {
		deleteSuccess = false;
		return;
	}
	RemoveDeletedClientsFromVector(vClients);

}


void DeleteClientFromFileByAccountNumber(string FileName, string AccountNumber, bool& deleteSuccess) {

	vector <stClientData> vClients;
	ReadClientsFromFile(FileName, vClients);

	MarkClientForDeletionInVector(vClients, AccountNumber, deleteSuccess);

	if (deleteSuccess) {
		WriteClientsToFile(FileName, vClients);
	}
}

void InteractiveDeleteMultipleClients(string FileName) {
	char deleteMore = 'n';
	char wantToDelete = 'n';
	bool deleteSuccess = false;

	string accountNumber;

	do {
		system("cls");

		cout << "\n\n";
		if (toupper(deleteMore) == 'N')
			cout << "Enter the client account number you want to delete from " << FileName << ": ";
		else
			cout << "Enter the next client account number: ";
		cin >> accountNumber;

		cout << "\nDo you really want to delete the client " << accountNumber << "? (Y/N): ";
		cin >> wantToDelete;

		deleteSuccess = false;
		if (toupper(wantToDelete) == 'Y') {
			DeleteClientFromFileByAccountNumber(FileName, accountNumber, deleteSuccess);
		}

		if (deleteSuccess) {
			cout << "\n\nThe client with account number " << accountNumber << " was deleted successfully.\n";
		}
		else {
			cout << "The client with account number " << accountNumber << " was not found.\n";
		}

		cout << "\n\nDo you want to delete more clients? (Y/N): ";
		cin >> deleteMore;

	} while (toupper(deleteMore) == 'Y');

	cout << "The file content after the delete operations:" << endl;
	cout << "\n";
	DisplayAllClientsFromFile(FileName);
}

stClientData FindClientInFileByAccountNumber(string FileName, string AccountNumber) {

	string Record = "";

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string line;
		stClientData CD = {};

		while (getline(MyFile, line)) {
			CD = ParseRecordToClient(line,"/#/");
			if (CD.AccountNumber == AccountNumber)
				return CD;
		}
	}


}

void FindClientByAccountNumber(string FileName) {
	system("cls");
	string AccountNumber;
	cout << "Enter the Account number of the client you need : ";
	cin >> AccountNumber;

	stClientData CD = FindClientInFileByAccountNumber(FileName, AccountNumber);
	PrintClientData(CD);

	cout << "\nPress Enter to return to the Main Menu...";
	string _pause;
	// Consume any leftover newline and then wait for the user to press Enter
	getline(cin, _pause);
	getline(cin, _pause);
}

void UpdateClientInVector(vector <stClientData>& vClients, string AccountNumber) {

	int IndexOfClients = FindClientIndexInVector(vClients, AccountNumber);

	cout << "\n\nEnter Client Data Info : \n";
	cout << string(25, '=') << endl;

	cout << "Enter PinCode? ";
	getline(cin >> ws, vClients[IndexOfClients].PinCode);
	cout << "Enter Name? ";
	getline(cin, vClients[IndexOfClients].Name);
	cout << "Enter Phone? ";
	getline(cin, vClients[IndexOfClients].Phone);
	cout << "Enter Account Balance? ";
	cin >> vClients[IndexOfClients].AccountBalance;
	cout << string(25, '=') << endl;


}

void UpdateClientInformation(string FileName) {
	system("cls");
	string AccountNumber;
	cout << "Enter the Account Number of client you want to update it : ";
	cin >> AccountNumber;

	vector <stClientData> vClients;

	ReadClientsFromFile(FileName, vClients);

	UpdateClientInVector(vClients, AccountNumber);

	WriteClientsToFile(FileName, vClients);

	cout << "\nPress Enter to return to the Main Menu...";
	string _pause;
	// Consume any leftover newline and then wait for the user to press Enter
	getline(cin, _pause);
	getline(cin, _pause);

}

void WhatTheTask(string FileName, enTasks Task, bool& Is_End) {

	switch (Task) {
	case enTasks::ChowClientList:
		DisplayAllClientsFromFile(FileName);
		break;
	case enTasks::AddNewClient:
		InteractiveAddMultipleClients(FileName);
		break;
	case enTasks::DeleteClient:
		InteractiveDeleteMultipleClients(FileName);
		break;
	case enTasks::FindClient:
		FindClientByAccountNumber(FileName);
		break;
	case enTasks::UpdateClientInfo:
		UpdateClientInformation(FileName);
		break;
	case enTasks::Exit:
		Is_End = true;
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
		WhatTheTask(FileName, Task, Is_End);

		if (Is_End) {

			PrintEndCaption();
			return;

		}

	}



}

