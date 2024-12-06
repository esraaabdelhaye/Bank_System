#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "iomanip"
#include <vector>
using namespace std;

class clsUsersListScreen : protected clsScreen
{
private:

	static void PrintUserLineRecord(clsUser User) {
		cout << "\t| " << setw(15) << left << User.UserName;
		cout << "| " << setw(20) << left << User.FullName();
		cout << "| " << setw(12) << left << User.Phone;
		cout << "| " << setw(30) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(15) << left << User.Permissions;
	}
public:

	static void ShowClientsList() {
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;// this will exit the function and it will not continue
		}

		vector<clsUser> vUsers = clsUser::GetUsersData();

		//Header
		string Title = "\t  Users List Screen";
		string SubTitle = "\t  (" + to_string(vUsers.size()) + ") User(s).";
		_ShowScreenHeader(Title, SubTitle);

		// First Table Raw
		cout << setw(8) << left << "" << "| " << left << setw(15) << "User Name";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(30) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		// Table Body
		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Users Available In the System!";
		else
			for (clsUser User : vUsers)
			{
				PrintUserLineRecord(User);
				cout << endl;
			}
		// Footer
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

	}

};

