#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUser.h"

using namespace std;
class clsManageUsersScreen : protected clsScreen
{
private:
    enum enUsersOptions { eListUsers = 1, eAddUser, eDeleteUser, eUpdateUser, eFindUser, eMainMenu };

    static void _ShowListUsersScreen() {
        clsUsersListScreen::ShowClientsList();
    }

    static void _ShowAddUserScreen() {
        clsAddNewUserScreen::ShowAddNewScreen();
    }

    static void _ShowDeleteUserScreen() {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen() {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen() {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _GoBackToUserMenu() {
        cout << "\n\n\t\t\t\t\tPress Any Key To Go Back To Manage Users Screen...";
        system("pause>0");
        ShowManageUsers();
    }

    static void _PerformUserOptions(enUsersOptions Choice) {
        switch (Choice) {
        case enUsersOptions::eListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToUserMenu();
            break;
        case enUsersOptions::eAddUser:
            system("cls");
            _ShowAddUserScreen();
            _GoBackToUserMenu();
            break;
        case enUsersOptions::eDeleteUser:
            system("cls");
            _ShowDeleteUserScreen();
            _GoBackToUserMenu();
            break;
        case enUsersOptions::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToUserMenu();
            break;
        case enUsersOptions::eFindUser:
            system("cls");
            _ShowFindUserScreen();
            _GoBackToUserMenu();
            break;
        case enUsersOptions::eMainMenu:
            break;
        }
    }
public:
    static void ShowManageUsers() {

        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");
        _ShowScreenHeader("\t    Manage Users Screen");

        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update Menu.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << "\n\t\t\t\t\t===========================================\n";
        cout << "\t\t\t\t\tPlease Enter A Number Between 1 and 6: ";
        _PerformUserOptions((enUsersOptions)clsInputValidate::ReadNumberBetween<int>(1, 6, "\t\t\t\t\tError: Out Of Range. Try Again: "));
    }
};

