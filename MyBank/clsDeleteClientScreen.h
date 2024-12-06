#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUser.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:

	static void _Print(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.getAccountNumber();
		cout << "\nPassword    : " << Client.getPinCode();
		cout << "\nBalance     : " << Client.getAccountBalance();
		cout << "\n___________________\n";

	}

public:
	static void ShowDeleteClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;// this will exit the function and it will not continue
		}

		_ShowScreenHeader("\t\tDelete Client");
		string AccountNumber = "";
		cout << "Enter The Client's Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "Account Not Found, Try Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient ClientToDelete = clsBankClient::Find(AccountNumber);
		cout << "_________________________________________________" << endl;
		_Print(ClientToDelete);

		cout << "\nAre You Sure You Wanna Delete This Client? Y/N : ";
		char Ans;
		cin >> Ans;
		if (Ans == 'Y' || Ans == 'y') {
			if (ClientToDelete.Delete()) {
				cout << "Client Deleted Successfully" << endl;
				_Print(ClientToDelete);
			}
			else {
				cout << "Error: Client Wasn't Deleted" << endl;
			}
		}
	}
};

