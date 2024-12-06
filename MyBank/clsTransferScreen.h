#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsDate.h"
#include "clsBankClient.h"
#include "fstream"
using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient Client) {
		cout << "\n\n\tClient Card\n";
		cout << "\t______________________________\n";
		cout << "\tFull Name      : " << Client.FullName() << "\n";
		cout << "\tAccount Number : " << Client.AccountNumber << "\n";
		cout << "\tAccount Balance: " << Client.AccountBalance << "\n";
		cout << "\t______________________________\n\n";
	}

	static clsBankClient ReadClient(string Message) {
		cout << Message;
		string Account_1 = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(Account_1)) {
			cout << "\tClient Not Found Try Again: ";
			Account_1 = clsInputValidate::ReadString();

		}
		return clsBankClient::Find(Account_1);
	}



public:
	static void ShowTransferScreen() {

		_ShowScreenHeader("\t\tTransfer Screen");


		clsBankClient Client_1 = ReadClient("\tEnter account number to transfer from: ");
		_PrintClientCard(Client_1);

		clsBankClient Client_2 = ReadClient("\tEnter account number to transfer to: ");
		_PrintClientCard(Client_2);

		cout << "\tEnter The Transfered Amount: ";
		string ErrorMes = "\tAmount exceeds the available balance. Enter another amount: ";
		double Amount = clsInputValidate::ReadNumberBetween<double>(0, Client_1.AccountBalance, ErrorMes);

		cout << "\tAre You Sure You Want To Perform This Operation? y/n: ";
		char Ans = 'n';
		cin >> Ans;
		if (Ans == 'y' || Ans == 'Y') {
			bool Successful = false;
			Successful = Client_1.TransferMoney(Client_2, Amount);
			if (Successful) {
				cout << "\n\tMoney Transferred successfully.\n\n";
				clsBankClient::SaveToLog(Client_1, Client_2, Amount);
				_PrintClientCard(Client_1);
				_PrintClientCard(Client_2);
			}
			else {
				cout << "\tError: Couldn't Transfer The Money Try Again Later.\n";
			}

		}

	}
};

