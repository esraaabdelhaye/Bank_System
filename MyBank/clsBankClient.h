#pragma once
#include<iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "Global.h"
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class clsBankClient :public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdatedMode = 1, AddNewMode };
	enMode _Mode;

	bool _MarkedForDelete = false;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#") {
		vector<string> vWords = clsString::Split(Line, Separator);
		clsBankClient Client(vWords[0], vWords[1], vWords[2], vWords[3], vWords[4], vWords[5], stof(vWords[6]), enMode::UpdatedMode);
		return Client;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#") {
		return Client.FirstName + Separator +
			Client.LastName + Separator +
			Client.Email + Separator +
			Client.Phone + Separator +
			Client.PinCode + Separator +
			Client.AccountNumber + Separator +
			to_string(Client.AccountBalance);
	}

	static clsBankClient _GetEmptyClientObject() {
		clsBankClient Client("", "", "", "", "", "", 0.0, enMode::EmptyMode);
		return Client;
	}

	static vector<clsBankClient> _LoadClientsDataFromFile() {
		vector<clsBankClient> vClients;
		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open()) {
			string line = "";
			while (getline(myFile, line)) {
				clsBankClient Client = _ConvertLineToClientObject(line);
				vClients.push_back(Client);
			}
			myFile.close();
		}
		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients) {
		fstream myFile;
		myFile.open("Clients.txt", ios::out);
		if (myFile.is_open()) {
			for (clsBankClient& C : vClients) {
				if (!C.MarkedForDelete) {
					string Line = _ConvertClientObjectToLine(C);
					myFile << Line << endl;
				}
			}
			myFile.close();
		}
	}

	void _AddDataLineToFile(string Line) {
		fstream myFile;
		myFile.open("Clients.txt", ios::app);
		if (myFile.is_open()) {
			myFile << Line << endl;
			myFile.close();
		}
	}

	void _Update() {
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		for (clsBankClient& C : vClients) {
			if (C.AccountNumber == this->AccountNumber) {
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
	}

	void _AddNew() {
		this->_Mode = enMode::UpdatedMode;
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	static vector<string> _getTransferLogLines() {
		vector<string> vLogs;
		fstream myFile;
		myFile.open("TransferLog.txt", ios::in);
		if (myFile.is_open()) {
			string Line = "";
			while (getline(myFile, Line)) {
				vLogs.push_back(Line);
			}
			myFile.close();
		}
		cout << vLogs.size() << endl;
		return vLogs;
	}

public:
	struct stTransferLog {
		string Time;
		string FirstAcc;
		string SecondAcc;
		double Amount;
		double FirstBalance;
		double SecondBalance;
		string UserName;
	};

	clsBankClient(string FirstName, string LastName, string Email, string Phone, string PinCode, string AccNo, float AccBal, enMode Mode)
		:clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_AccountBalance = AccBal;
		_PinCode = PinCode;
		_AccountNumber = AccNo;
	}

	//  Setters And Getters 
	string getAccountNumber()
	{
		return _AccountNumber;
	}
	__declspec(property(get = getAccountNumber)) string AccountNumber;

	void setPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string getPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	void setAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float getAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	void setMarkedForDelete(bool Mark)
	{
		_AccountBalance = Mark;
	}

	float getMarkedForDelete()
	{
		return _MarkedForDelete;
	}
	__declspec(property(get = getMarkedForDelete, put = setMarkedForDelete)) float MarkedForDelete;

	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << AccountNumber;
		cout << "\nPassword    : " << PinCode;
		cout << "\nBalance     : " << AccountBalance;
		cout << "\n___________________\n";

	}*/

	bool isEmpty() {
		return (this->_Mode == enMode::EmptyMode);
	}

	static clsBankClient GetAddNewCLientObject(string AccountNumber) {
		clsBankClient Client("", "", "", "", "", AccountNumber, 0, clsBankClient::enMode::AddNewMode);
		return Client;
	}

	static clsBankClient Find(string AccountNumber) {
		vector<clsBankClient> vClients;
		fstream myFile;
		myFile.open("Clients.txt", ios::in);
		if (myFile.is_open()) {
			string line = "";
			while (getline(myFile, line)) {
				clsBankClient Client = _ConvertLineToClientObject(line);
				if (Client.AccountNumber == AccountNumber) {
					return Client;
					myFile.close();
				}
				vClients.push_back(Client);
			}
			myFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {
		clsBankClient ClientFound = clsBankClient::Find(AccountNumber);
		if (ClientFound.PinCode == PinCode)
			return ClientFound;

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {
		clsBankClient ClientFound = clsBankClient::Find(AccountNumber);
		return (!ClientFound.isEmpty());
	}

	static void ReadClientInfo(clsBankClient& Client) {
		cout << "\nEnter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadNumber<float>();
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1 };
	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			return enSaveResults::svFailedEmptyObject;
			break;
		case enMode::UpdatedMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case enMode::AddNewMode:
			_AddNew();
			return enSaveResults::svSucceeded;
			break;
		}
	}

	static double GetTotalBalance() {
		vector<clsBankClient> vClients = _LoadClientsDataFromFile();
		double Balance = 0;
		for (clsBankClient& C : vClients) {
			Balance += C.AccountBalance;
		}
		return Balance;
	}

	bool Delete() {
		vector<clsBankClient> vClients = clsBankClient::GetClientsList();

		for (clsBankClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.MarkedForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static vector<clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	void Deposite(double DepositeVal) {
		AccountBalance += DepositeVal;
		Save();
	}

	bool Withdraw(double WithdrawVal) {
		if (AccountBalance >= WithdrawVal) {
			AccountBalance -= WithdrawVal;
			Save();
			return true;
		}
		return false;
	}

	bool TransferMoney(clsBankClient& Client_2, double Amount) {
		if (Amount > AccountBalance)
			return false;
		this->Withdraw(Amount);
		Client_2.Deposite(Amount);
		return true;
	}

	static string GetRegisterRecord(clsBankClient C1, clsBankClient C2, double Amount) {
		string Time = clsDate::getExactTime();
		return Time + "#//#" +
			C1.AccountNumber + "#//#" +
			C2.AccountNumber + "#//#" +
			to_string(Amount) + "#//#" +
			to_string(C1.AccountBalance) + "#//#" +
			to_string(C2.AccountBalance) + "#//#" +
			currentUser.UserName;
	}

	static void SaveToLog(clsBankClient C1, clsBankClient C2, double Amount) {
		string Record = GetRegisterRecord(C1, C2, Amount);
		fstream myFile;
		myFile.open("TransferLog.txt", ios::app);
		if (myFile.is_open()) {
			myFile << Record << endl;
			myFile.close();
		}
	}

	static vector<stTransferLog> GetTransLogStructs() {
		vector<string> vLogs = _getTransferLogLines();
		vector<stTransferLog> vStructLogs;
		for (string Log : vLogs) {
			vector<string> vWords = clsString::Split(Log, "#//#");
			vStructLogs.push_back({ vWords[0],vWords[1], vWords[2], stod(vWords[3]), stod(vWords[4]), stod(vWords[5]), vWords[6] });
		}
		return vStructLogs;
	}

};

