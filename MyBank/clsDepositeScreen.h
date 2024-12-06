#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsDepositeScreen : protected clsScreen
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
		cout << "\nAcc. Number : " << Client.AccountNumber;
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}
public:
	static void ShowDepositeScreen() {
		_ShowScreenHeader("\t      Deposite Screen");

		string AccountNumber;
		cout << "Please, Enter A Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Account Number Is Not Found, Please Try Again: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		cout << "\n\nEnter You Deposite Value: ";
		double DepositeVal = clsInputValidate::ReadNumber<double>();

		cout << "\nAre you sure you want to perform this transaction? ";
		char Answer = 'n';
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			Client.Deposite(DepositeVal);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << Client.AccountBalance << endl;

		}
		else
		{
			cout << "\nOperation cancelled.\n";
		}

	}
};

