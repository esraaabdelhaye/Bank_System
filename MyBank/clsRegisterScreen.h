#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;

class clsRegisterScreen : protected clsScreen
{
private:
	static void _PrintRegisterRecord(clsUser::stLoginRegisterRecord Record) {
		cout << "\t| " << setw(35) << left << Record.registTime;
		cout << "| " << setw(20) << left << Record.registName;
		cout << "| " << setw(20) << left << Record.registPass;
		cout << "| " << setw(15) << left << Record.registPermission;

	}
public:
	static void ShowRegisterScreen() {
		if (!CheckAccessRights(clsUser::enPermissions::pRegister))
		{
			return;// this will exit the function and it will not continue
		}

		vector<clsUser::stLoginRegisterRecord> vRecords = clsUser::GetRegisterStructs();

		string SubTitle = "\t\t(" + to_string(vRecords.size()) + ") Login(s).";
		_ShowScreenHeader("\t  Login Register List Screen", SubTitle);

		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(15) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		// Table Body
		for (clsUser::stLoginRegisterRecord Record : vRecords)
		{
			_PrintRegisterRecord(Record);
			cout << endl;
		}
		// Footer
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;
	}
};

