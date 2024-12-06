#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;
class clsAddNewUserScreen : protected clsScreen
{
private:

	static int ReadUserPermissions() {
		int Permissions = 0;
		char Answer = 'n';


		cout << "Do You Wann Give User Full Permission? y/n : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			return -1;
		}
		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Clients List y/n? : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client y/n? : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client y/n? : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client y/n : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pUpdateClients;
		}

		cout << "\nFind Client y/n : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nPerform Transactions y/n : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pTranactions;
		}

		cout << "\nManage Users y/n : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		cout << "\nShow Login Register y/n : ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			Permissions += clsUser::enPermissions::pRegister;
		}
		return Permissions;
	}

	static void _ReadUserInfo(clsUser& User) {
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		User.Permissions = ReadUserPermissions();
	}

	static void _Print(clsUser User)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nAcc. Number : " << User.UserName;
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

public:
	static void ShowAddNewScreen() {
		_ShowScreenHeader("\t    Add New User Screen");


		string UserName = "";
		cout << "Enter The New User's UserName: ";
		UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName)) {
			cout << "UserName Already Taken, Try Another One: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser newUser = clsUser::GetAddNewUserObject(UserName);
		_ReadUserInfo(newUser);

		clsUser::enSaveResults saveResults = newUser.Save();
		if (saveResults == clsUser::enSaveResults::svSucceeded) {
			cout << "\n\nAccount Added Successfully" << endl;
			_Print(newUser);
		}
		else if (saveResults == clsUser::enSaveResults::svFailedEmptyObject) {
			cout << "Error, Account Wasn't Saved Because It's Empty!" << endl;
		}
	}
};

