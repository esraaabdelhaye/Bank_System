#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include <iomanip>
#include "clsUser.h"
using namespace std;

class clsTransactionsScreen :protected clsScreen
{
private:
    enum enTransOptions { eDeposite = 1, eWithdraw, eTotBalance, eTransfer, eTransLog, eMainMenu };

    static void _ShowDepositeScreen() {
        clsDepositeScreen::ShowDepositeScreen();
    }

    static void _ShowWithdrawScreen() {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotBalanceScreen() {
        clsTotBalanceScreen::ShowTotBalanceScreen();
    }

    static void _ShowTransferScreen() {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen() {
        clsTransferLogScreen::ShowTransferLog();
    }

    static void _GoBackToTransMenu() {
        cout << "\n\n\t\t\t\t\tPress Any Key To Go Back To Transactions Menu...";
        system("pause>0");
        ShowTransactionsScreen();
    }

    static void _PerformTransOptions(enTransOptions Choice) {
        switch (Choice) {
        case enTransOptions::eDeposite:
            system("cls");
            _ShowDepositeScreen();
            _GoBackToTransMenu();
            break;
        case enTransOptions::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransMenu();
            break;
        case enTransOptions::eTotBalance:
            system("cls");
            _ShowTotBalanceScreen();
            _GoBackToTransMenu();
            break;
        case enTransOptions::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransMenu();
            break;
        case enTransOptions::eTransLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransMenu();
            break;
        case enTransOptions::eMainMenu:
            break;
        }
    }

public:
    static void ShowTransactionsScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }

        system("cls");
        _ShowScreenHeader("\t    Transactions Screen");

        cout << setw(37) << left << "" << "\t[1] Deposite.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balance.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Display Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << "\n\t\t\t\t\t===========================================\n";
        cout << "\t\t\t\t\tPlease Enter A Number Between 1 and 6: ";
        _PerformTransOptions((enTransOptions)clsInputValidate::ReadNumberBetween<int>(1, 6, "\t\t\t\t\tError: Out Of Range. Try Again: "));
    }
};

