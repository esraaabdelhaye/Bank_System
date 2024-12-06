#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsRegisterScreen.h"
#include "clsCurrencyMainScreen.h"
#include <iomanip>
#include "Global.h"
#include "clsUser.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
    static void _ShowAllClientsScreen() {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen() {
        clsAddNewClientScreen::ShowAddNewScreen();
    }

    static void _ShowDeleteClientScreen() {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen() {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen() {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsScreen() {
        clsTransactionsScreen::ShowTransactionsScreen();
    }

    static void _ShowManageUsersScreen() {
        clsManageUsersScreen::ShowManageUsers();
    }

    static void _ShowRegisterScreen() {
        clsRegisterScreen::ShowRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen() {
        clsCurrencyMainScreen::ShowCurrencyMainScreen();
    }

    static void _GoBackToMainMenu() {
        cout << "\n\n\t\t\t\t\tPress Any Key To Go Back To Main Menu..." << endl;
        system("pause>0");
        ShowMainMenu();
    }

    enum enMainOptions { eListClients = 1, eAddNewClient, eDeleteClient, eUpdateClient, eFindClient, eShowTransactions, eManageUsers, eRegister, eExchange, eLogout };
    static void _PerformMainOptions(enMainOptions choice) {
        switch (choice) {
        case enMainOptions::eListClients:
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
            break;
        case enMainOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientScreen();
            _GoBackToMainMenu();
            break;
        case enMainOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;
        case enMainOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;
        case enMainOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;
        case enMainOptions::eShowTransactions:
            system("cls");
            _ShowTransactionsScreen();
            _GoBackToMainMenu();
            break;
        case enMainOptions::eManageUsers:
            system("cls");
            _ShowManageUsersScreen();
            _GoBackToMainMenu();
            break;
        case enMainOptions::eRegister:
            system("cls");
            _ShowRegisterScreen();
            _GoBackToMainMenu();
            break;
        case enMainOptions::eExchange:
            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenu();
            break;
        default:
            //cout << "\n\n\n\t\t\t\t\t\t\tGOOD BYE\n\n\n";
            system("cls");
            currentUser = clsUser::Find("", "");
        }
    }

public:
    static void ShowMainMenu() {
        system("cls");
        _ShowScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Register Login.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << "\n\t\t\t\t\t===========================================\n";
        cout << "\t\t\t\t\tPlease Enter A Number Between 1 and 10: ";
        _PerformMainOptions((enMainOptions)clsInputValidate::ReadNumberBetween<int>(1, 10, "\t\t\t\t\tError: Out Of Range. Try Again: "));
    }
};

