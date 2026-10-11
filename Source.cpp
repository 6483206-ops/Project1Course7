
//The Programer Hasan Hlala
//This Program is a simple example of Banks Programs
//I write this code as a project in the end of the 7 course of Abo Hadhoud courses 

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Global file name for client data
string FileName = "ClientsData";
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
	Transactions = 6,
	Exit = 7
};

enum enTransactions {
	Deposit =1,
	Withdraw =2,
	TotalBalance =3,
	MainMenue =4
};

vector<string> SplitString(string S1, string delim);
stClientData ReadClientData();
void PrintClientData(stClientData CD);
void AppendClientRecordToFile(string Record);
string CreateClientRecord(stClientData CD, string Diameter);
stClientData ParseRecordToClient(string Record,string Diameter);
void WriteClientsToFile(vector <stClientData>& vClients);
void ReadClientsFromFile(vector<stClientData>& vClients);
void PrintClientTableHeader(int Count);
void PrintClientRow(stClientData& Client);
void PrintClientTable(vector <stClientData>& vClients);
void InteractiveAddSingleClient();
void DisplayAllClientsFromFile();
void InteractiveAddMultipleClients();
int FindClientIndexInVector(vector <stClientData>& vClients, string AccountNumber);
void RemoveDeletedClientsFromVector(vector <stClientData>& vClients);
void MarkClientForDeletionInVector(vector <stClientData>& vClients, string AccountNumber, bool& deleteSuccess);
void DeleteClientFromFileByAccountNumber(string AccountNumber, bool& deleteSuccess);
void InteractiveDeleteMultipleClients();
stClientData FindClientInFileByAccountNumber(string AccountNumber);
void FindClientByAccountNumber();
void UpdateClientInVector(vector <stClientData>& vClients, string AccountNumber);
void UpdateClientInformation();
void ReturnToTransactionsMainMenue();
string ReadAccountNumber();
void PrintDepositScreen();
void DepositInClient();
void PerformeTransaction(enTransactions Trans);
enTransactions ReadTheTransaction();
void PrintTransactionsMainMenue();
void PerformeTransactions();
enTasks WhatTheTask();
void PerformeTheTask(enTasks Task);
void PrintTheMainMenu();
void PrintEndCaption();
long long SumOfTotalBalance(vector <stClientData>& vClients);
void PrintClientBalanceTableHeader(int Count, int& LineLength);
void PrintClientBalanceTable(vector <stClientData>& vClients);
void PrintClientBalanceRow(stClientData& Client);
void DisplayTotalBalance();
void PrintWithdrawScreen();
void WithdrawFromClient();

void StartTheProgram();







int main() {

	StartTheProgram();

}











bool IfTheAccountNumperFound(string AccountNumber) {

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string line;
		stClientData CD = {};

		while (getline(MyFile, line)) {
			CD = ParseRecordToClient(line, "/#/");
			if (CD.AccountNumber == AccountNumber)
				return true;
		}
		MyFile.close();
	}

	return false;
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
	while (IfTheAccountNumperFound(CD.AccountNumber)) {
		cout << "\nThe Account Numper " << CD.AccountNumber << " found in the file...\n";
		cout << "Enter another one : ";
		getline(cin >> ws, CD.AccountNumber);
	}
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

void AppendClientRecordToFile(string Record) {

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

void WriteClientsToFile(vector <stClientData>& vClients) {

	fstream MyFile;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (int i = 0; i < vClients.size(); i++) {
			if (!vClients[i].MarkForDelete)
				MyFile << CreateClientRecord(vClients[i], "/#/") << endl;
		}
	}

}


void ReadClientsFromFile(vector<stClientData>& vClients) {

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

}

void InteractiveAddSingleClient() {
	stClientData CD;
	CD = ReadClientData();
	AppendClientRecordToFile(CreateClientRecord(CD, "/#/"));
}

void DisplayAllClientsFromFile() {

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);
	PrintClientTable(vClients);
}

void InteractiveAddMultipleClients() {
	char MoreClients = 'y';
	do {
		system("cls");
		cout << "Add new client : " << endl;
        InteractiveAddSingleClient();
		cout << "\nWant to add more client ? ";
		cin >> MoreClients;
	} while (toupper(MoreClients) == 'Y');
	cout << endl;
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


void DeleteClientFromFileByAccountNumber(string AccountNumber, bool& deleteSuccess) {

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);

	MarkClientForDeletionInVector(vClients, AccountNumber, deleteSuccess);

	if (deleteSuccess) {
		WriteClientsToFile(vClients);
	}
}

void InteractiveDeleteMultipleClients() {
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
			DeleteClientFromFileByAccountNumber(accountNumber, deleteSuccess);
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
    
	cout << endl;
}

stClientData FindClientInFileByAccountNumber(string AccountNumber) {

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

		MyFile.close();
	}


}

void FindClientByAccountNumber() {
	system("cls");
	string AccountNumber;
	AccountNumber = ReadAccountNumber();

	stClientData CD = FindClientInFileByAccountNumber(AccountNumber);
	PrintClientData(CD);

	cout << "\n";
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

void UpdateClientInformation() {
	system("cls");
	string AccountNumber;
	cout << "Enter the Account Number of client you want to update it : ";
	cin >> AccountNumber;

	vector <stClientData> vClients;

	ReadClientsFromFile(vClients);

	UpdateClientInVector(vClients, AccountNumber);

	WriteClientsToFile(vClients);

	cout << "\n";

}

void ReturnToMainMenue() {
	cout << "\nPress any key to return to main menue...." << endl;
	system("pause>0");
}

void PrintDepositScreen() {
	string DepositScreen = "Deposit Screen";
	int LineLength = 10 + DepositScreen.length() + 10;

	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << DepositScreen << endl;
	cout << string(LineLength, '-') << endl;
}

string ReadAccountNumber() {
	string AccountNumber;
	
	cout << "Enter the Account Number : ";
	cin >> AccountNumber;

	while (!IfTheAccountNumperFound(AccountNumber)) {
		cout << "The Account Number not found!!!" << endl;
		cout << "Please enter a rigth one : ";
		cin >> AccountNumber;
	}
	return AccountNumber;
}

void ReturnToTransactionsMainMenue() {
	cout << "\nPress Any Key to return to Transactions Main Menue....\n";
	system("pause>0");
}

void DepositInClient() {
	PrintDepositScreen();
	cout << "\n";

	vector <stClientData> vClients;
	string AccountNumber = ReadAccountNumber();

	ReadClientsFromFile(vClients);
	int Index = FindClientIndexInVector(vClients, AccountNumber);

	cout << "The Following are the client data : ";
	PrintClientData(vClients[Index]);
	
	int DepositAmmount = 0;
	cout << "Please enter a deposit ammount : ";
	cin >> DepositAmmount;

	char SureDeposit;
	cout << "Are you sure you want to add " << DepositAmmount << "to this Account ? y/n: ";
	cin >> SureDeposit;
	if (toupper(SureDeposit) == 'Y') {
		vClients[Index].AccountBalance += DepositAmmount;
		WriteClientsToFile(vClients);
		cout << "The Account Balance after the addition is : " << vClients[Index].AccountBalance << endl;
	}
	else {
		return;
	}

}

void PrintWithdrawScreen() {

	string Withdraw = "Withdraw Screen";
	int LineLength = 10 + Withdraw.length() + 10;

	cout << "\n";

	cout << string(LineLength, '-') << endl;
	cout << string(10, ' ') << Withdraw << string(10, ' ') << endl;
	cout << string(LineLength, '-') << endl;

	cout << "\n\n";
}

void WithdrawFromClient() {

	PrintWithdrawScreen();

	string AccountNumber = ReadAccountNumber();

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);
	
	int Index = FindClientIndexInVector(vClients,AccountNumber);

	cout << "The following are the clients details : \n";
	PrintClientData(vClients[Index]);

	int WithdrawAmmount = 0;
	cout << "Please enter withdraw ammount? ";
	cin >> WithdrawAmmount;

	while (WithdrawAmmount > vClients[Index].AccountBalance) {

		cout << "Ammount Exceeds the balance, you can withdraw up to : " << vClients[Index].AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> WithdrawAmmount;
	}

	char SureWithdraw;
	cout << "Are you sure you want to withdraw " << WithdrawAmmount << " from this Account ? y/n: ";
	cin >> SureWithdraw;
	if (toupper(SureWithdraw) == 'Y') {
		vClients[Index].AccountBalance -= WithdrawAmmount;
		WriteClientsToFile(vClients);
		cout << "The Account Balance after the withdrawing is : " << vClients[Index].AccountBalance << endl;
	}
	else {
		return;
	}

}

long long SumOfTotalBalance(vector <stClientData>& vClients) {
	long long Sum = 0;

	for (stClientData& C : vClients) {
		Sum += C.AccountBalance;
	}

	return (long long)Sum;

}

void PrintClientBalanceTableHeader(int Count,int &LineLength) {
	const int totalWidth = 2 + 14 + 2 + 40 + 2 + 14 + 2; // compute rough width including separators
	cout << "\n\t\t\t\tBalance List (" << Count << ") Client(s)." << endl;
	cout << string(totalWidth, '_') << "\n\n";
	cout << "| " << setw(14) << left << "Account Number"
		<< "| " << setw(40) << left << "Client Name"
		<< "| " << setw(14) << left << "Balance"
		<< " |" << endl;
	cout << string(totalWidth, '_') << "\n";

	LineLength = totalWidth;
}

void PrintClientBalanceTable(vector <stClientData>& vClients) {
	
	int LineLength = 0;

	PrintClientBalanceTableHeader(vClients.size(),LineLength);
	if (vClients.size() != 0) {
		for (size_t i = 0; i < vClients.size(); i++) {
			PrintClientBalanceRow(vClients[i]);
			cout << "\n";
		}
	}
	
	string TotalBalanceString = "Total Balance = ";
	cout << "\n";
	cout << string((LineLength / 2) - (TotalBalanceString.length() / 2), ' ') << "Total Balance = " << SumOfTotalBalance(vClients);

}

void PrintClientBalanceRow(stClientData& Client) {
	cout << "| " << setw(14) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(14) << left << Client.AccountBalance << " |";
}


void DisplayTotalBalance() {

	vector <stClientData> vClients;
	ReadClientsFromFile(vClients);
	PrintClientBalanceTable(vClients);

}

void PerformeTransaction(enTransactions Trans,bool &PerformeMore) {

	system("cls");

	switch (Trans) {
	case enTransactions::Deposit:
		DepositInClient();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::Withdraw :
		WithdrawFromClient();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::TotalBalance :
		DisplayTotalBalance();
		ReturnToTransactionsMainMenue();
		break;
	case enTransactions::MainMenue :
		PerformeMore = false;
		break;
	}
}

enTransactions ReadTheTransaction() {
	int n;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> n;
	return (enTransactions)n;
}

void PrintTransactionsMainMenue() {
	string MainMenue = "Transactions Main Menue";
	int LineLength = 16 + MainMenue.length() + 16;
	cout << '\n';
	cout << string(16, ' ') << MainMenue << endl;
	cout << string(LineLength, '=') << endl;
	cout << string(8, ' ') << "[1] Deposit.\n";
	cout << string(8, ' ') << "[2] Withdraw.\n";
	cout << string(8, ' ') << "[3] Total Balances\n";
	cout << string(8, ' ') << "[4] Main Menue.\n";
	cout << string(LineLength, '=') << endl;
}

void PerformeTransactions() {
	bool PerformeMore = true;

	while (PerformeMore) {
		enTransactions Trans;
		system("cls");
		PrintTransactionsMainMenue();
		Trans = ReadTheTransaction();
		PerformeTransaction(Trans,PerformeMore);
	}
}

void PerformeTheTask(enTasks Task) {

	system("cls");

	switch (Task) {
	case enTasks::ChowClientList:
        DisplayAllClientsFromFile();
		ReturnToMainMenue();
		break;
	case enTasks::AddNewClient:
        InteractiveAddMultipleClients();
		ReturnToMainMenue();
		break;
	case enTasks::DeleteClient:
        InteractiveDeleteMultipleClients();
		ReturnToMainMenue();
		break;
	case enTasks::FindClient:
        FindClientByAccountNumber();
		ReturnToMainMenue();
		break;
	case enTasks::UpdateClientInfo:
        UpdateClientInformation();
		ReturnToMainMenue();
		break;
	case enTasks::Transactions :
		PerformeTransactions();
		ReturnToMainMenue();
	case enTasks::Exit :
		PrintEndCaption();
		break;
		
	}

}

enTasks WhatTheTask() {

	int n;
	cout << "\nEnter The number (1 to 7) ? ";
	cin >> n;
	return (enTasks)n;

}

void PrintTheMainMenu() {

	system("cls");

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
	cout << string(5, ' ') << "[6] Transactions.\n";
	cout << string(5, ' ') << "[7] Exit.\n";
	cout << string(LengthOfLine, '=') << endl;

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
		
		PrintTheMainMenu();

		enTasks Task;
		Task = WhatTheTask();
        PerformeTheTask(Task);
		
	}



}

