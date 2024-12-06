#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
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
	static void ShowFindClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;// this will exit the function and it will not continue
		}

		_ShowScreenHeader("\t     Find Client Screen");
		cout << "\nPlease Enter Account Number: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		if (!Client1.isEmpty())
		{
			cout << "\nClient Found :-)\n";
		}
		else
		{
			cout << "\nClient Was not Found :-(\n";
		}

		_Print(Client1);
	}
};

