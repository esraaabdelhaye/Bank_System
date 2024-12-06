#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsBankClient.h"
using namespace std;

class clsClientListScreen : protected clsScreen
{
private:

	static void PrintClientLineRecord(clsBankClient Client) {
		cout << "\t| " << setw(15) << left << Client.getAccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(30) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(15) << left << Client.AccountBalance;
	}
public:

	static void ShowClientsList() {

		if (!CheckAccessRights(clsUser::enPermissions::pListClients))
		{
			return;// this will exit the function and it will not continue
		}

		vector<clsBankClient> vClients = clsBankClient::GetClientsList();

		//Header
		string Title = "\t  Client List Screen";
		string SubTitle = "\t  (" + to_string(vClients.size()) + ") Client(s).";
		_ShowScreenHeader(Title, SubTitle);

		// First Table Raw
		cout << setw(8) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(30) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		// Table Body
		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else
			for (clsBankClient Client : vClients)
			{
				PrintClientLineRecord(Client);
				cout << endl;
			}
		// Footer
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

	}

};

