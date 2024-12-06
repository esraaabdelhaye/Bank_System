#pragma once
#include <iostream>
#include <fstream>
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;
class clsLoginScreen :protected clsScreen
{
private:

	static void _AddToLoginRegister() {
		string Line = clsDate::getExactTime() + "#//#" + currentUser.UserName + "#//#" + clsUtil::EncryptText(currentUser.Password) + "#//#" + to_string(currentUser.Permissions);

		fstream myFile;
		myFile.open("LoginRegister.txt", ios::app);
		if (myFile.is_open()) {
			myFile << Line << endl;
			myFile.close();
		}
	}

	static bool _Login() {
		string UserName = "", Password = "";
		bool NotFound = false;
		int Trails = 3;
		do {

			if (NotFound) {
				Trails--;
				cout << "\n\t\t\t\t\tError: Incorrect Username / Password\n";

				if (Trails == 0) {
					cout << "\n\n\n\t\t\t\t\tYou Are Locked After 3 Failed Trails.\n";
					cout << "\t\t\t\t\t\t      GOOD BYE!\n\n";
					return false;
				}
				cout << "\t\t\t\t\tYou Have [" << Trails << "] Trail(s) Left\n\n\n";
			}

			cout << "\t\t\t\t\tEnter UserName: ";
			UserName = clsInputValidate::ReadString();
			cout << "\t\t\t\t\tEnter Password: ";
			Password = clsInputValidate::ReadString();

			currentUser = clsUser::Find(UserName, Password);
		} while (NotFound = currentUser.isEmpty());

		_AddToLoginRegister();

		clsMainScreen::ShowMainMenu();
		return true;
	}
public:
	static bool ShowLoginScreen() {

		_ShowScreenHeader("\t\tLogin Screen");
		return _Login();
	}
};

