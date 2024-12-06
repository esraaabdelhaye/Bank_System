#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsFindUserScreen : protected clsScreen
{
private:
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
	static void ShowFindUserScreen() {
		_ShowScreenHeader("\t     Find User Screen");
		cout << "\nPlease Enter UserName: ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.isEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}

		_Print(User);
	}
};

