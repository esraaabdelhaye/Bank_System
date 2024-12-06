#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:


	static void _ReadClientInfo(clsBankClient& Client) {
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
	static void ShowAddNewScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;// this will exit the function and it will not continue
		}

		_ShowScreenHeader("\t    Add New Client Screen");

		string AccountNumber = "";
		cout << "Enter The New Client's Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Account Number Already Taken, Try Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient newClient = clsBankClient::GetAddNewCLientObject(AccountNumber);
		_ReadClientInfo(newClient);

		clsBankClient::enSaveResults saveResults = newClient.Save();
		if (saveResults == clsBankClient::enSaveResults::svSucceeded) {
			cout << "Account Added Successfully" << endl;
			_Print(newClient);
		}
		else if (saveResults == clsBankClient::enSaveResults::svFailedEmptyObject) {
			cout << "Error, Account Wasn't Saved Because It's Empty!" << endl;
		}
	}
};

