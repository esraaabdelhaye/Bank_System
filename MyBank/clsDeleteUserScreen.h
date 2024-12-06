#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsDeleteUserScreen :protected clsScreen
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
	static void ShowDeleteUserScreen() {
		_ShowScreenHeader("\t     Delete User Screen");
		string UserName = "";
		cout << "Enter The User's UserName: ";
		UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName)) {

			cout << "Account Not Found, Try Another One: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser UserToDelete = clsUser::Find(UserName);
		cout << "_________________________________________________" << endl;
		_Print(UserToDelete);

		cout << "\nAre You Sure You Wanna Delete This User? Y/N : ";
		char Ans;
		cin >> Ans;
		if (Ans == 'Y' || Ans == 'y') {
			if (UserToDelete.Delete()) {
				cout << "User Deleted Successfully" << endl;
				_Print(UserToDelete);
			}
			else {
				cout << "Error: User Wasn't Deleted" << endl;
			}
		}
	}
};
