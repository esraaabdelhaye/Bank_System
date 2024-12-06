#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsUser.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
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
	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;// this will exit the function and it will not continue
		}

		_ShowScreenHeader("\t    Update Client Screen");

		string AccountNumber;
		cout << "Please, Enter A Client Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "Account Number Is Not Found, Please Try Again: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_Print(Client);

		cout << "Update Client Info:" << endl;
		cout << "_______________________" << endl;

		clsBankClient::ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResult;
		SaveResult = Client.Save();
		switch (SaveResult)
		{
		case  clsBankClient::enSaveResults::svSucceeded:
			cout << "\nAccount Updated Successfully :-)\n";
			_Print(Client);
			break;
		case clsBankClient::enSaveResults::svFailedEmptyObject:
			cout << "\nError account was not saved because it's Empty";
			break;
		}

	}
};

