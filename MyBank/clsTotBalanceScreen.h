#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <iomanip>
#include <vector>
using namespace std;

class clsTotBalanceScreen : protected clsScreen
{
private:
	static void _PrintClientBalanceLineRecord(clsBankClient Client) {
		cout << "\t|" << left << setw(20) << Client.AccountNumber;
		cout << "\t|" << left << setw(30) << Client.FullName();
		cout << "\t|" << left << setw(20) << Client.AccountBalance;
		cout << "\n\n";
	}

	static void _PrintClientsBalances(vector<clsBankClient> vClients) {
		if (vClients.size() == 0) {
			cout << "No Clients Available In The System..." << endl;
		}
		else {
			for (clsBankClient& C : vClients) {
				_PrintClientBalanceLineRecord(C);
			}
		}

	}
public:
	static void ShowTotBalanceScreen() {

		vector<clsBankClient> vClients = clsBankClient::GetClientsList();
		string subTile = "\t       [" + to_string(vClients.size()) + "] Client(s)";

		_ShowScreenHeader("\t    Total Balance Screen", subTile);

		cout << "\n_________________________________________________________________________________________\n\n";
		cout << "\t|" << left << setw(20) << "Account Number";
		cout << "\t|" << left << setw(30) << "Full Name";
		cout << "\t|" << left << setw(20) << "Account Balance";
		cout << "\n\n_________________________________________________________________________________________\n\n\n";

		_PrintClientsBalances(vClients);
		double Balance = clsBankClient::GetTotalBalance();
		cout << "\n_________________________________________________________________________________________\n\n";
		cout << clsUtil::Tabs(5) << "Total Balances = " << Balance << endl;
		cout << clsUtil::Tabs(5) << "( " << clsUtil::NumberToText(Balance) << ")\n\n" << endl;
	}
};

