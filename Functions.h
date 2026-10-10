#ifndef FUNCTIONS_H
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

struct stClientData {
    std::string AccountNumber;
    std::string PinCode;
    std::string Name;
    std::string Phone;
    int AccountBalance = 0;
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

extern std::string FileName;

// Function prototypes
std::vector<std::string> SplitString(std::string S1, std::string delim);
stClientData ReadClientData();
void PrintClientData(stClientData CD);
void AppendClientRecordToFile(std::string Record);
std::string CreateClientRecord(stClientData CD, std::string Diameter);
stClientData ParseRecordToClient(std::string Record, std::string Diameter = "/#/");
void WriteClientsToFile(std::vector<stClientData>& vClients);
void ReadClientsFromFile(std::vector<stClientData>& vClients);
void PrintClientTableHeader(int Count);
void PrintClientRow(stClientData& Client);
void PrintClientTable(std::vector<stClientData>& vClients);
void InteractiveAddSingleClient();
void DisplayAllClientsFromFile();
void InteractiveAddMultipleClients();
int FindClientIndexInVector(std::vector<stClientData>& vClients, std::string AccountNumber);
void RemoveDeletedClientsFromVector(std::vector<stClientData>& vClients);
void MarkClientForDeletionInVector(std::vector<stClientData>& vClients, std::string AccountNumber, bool& deleteSuccess);
void DeleteClientFromFileByAccountNumber(std::string AccountNumber, bool& deleteSuccess);
void InteractiveDeleteMultipleClients();
stClientData FindClientInFileByAccountNumber(std::string AccountNumber);
void FindClientByAccountNumber();
void UpdateClientInVector(std::vector<stClientData>& vClients, std::string AccountNumber);
void UpdateClientInformation();
bool IfTheAccountNumperFound(std::string AccountNumber);
void ReturnToMainMenue();
enTasks WhatTheTask();
void PerformeTheTask(enTasks Task);
void PrintTheMainMenu();
void PrintEndCaption();
void StartTheProgram();

#endif // FUNCTIONS_H
