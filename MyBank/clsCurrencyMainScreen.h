#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrencyListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRate.h"
#include "clsCurrencyCalculator.h"
using namespace std;

class clsCurrencyMainScreen: public clsScreen
{
private:

    static void _ShowListCurrencies() {
        clsCurrencyListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrency() {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRate() {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculator() {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _GoBackToCurrencyMainMenu() {
        cout << "\t\t\t\t\tPress any key to go back to main currency screen...\n";
        system("pause>0");
        ShowCurrencyMainScreen();
    }
    
    enum enCurrencyOptions {eList=1, eFind, eUpdateRate, enCalculator, eMainMenu};
    static void _PerformMainOptions(enCurrencyOptions Option) {
        switch (Option)
        {
        case clsCurrencyMainScreen::eList:
            _ShowListCurrencies();
            _GoBackToCurrencyMainMenu();
            break;
        case clsCurrencyMainScreen::eFind:
            _ShowFindCurrency();
            _GoBackToCurrencyMainMenu();
            break;
        case clsCurrencyMainScreen::eUpdateRate:
            _ShowUpdateRate();
            _GoBackToCurrencyMainMenu();
            break;
        case clsCurrencyMainScreen::enCalculator:
            _ShowCurrencyCalculator();
            _GoBackToCurrencyMainMenu();
            break;
        case clsCurrencyMainScreen::eMainMenu:
            break;
        default:
            break;
        }
    }
public:
    
	static void ShowCurrencyMainScreen() {
        system("cls");
        _ShowScreenHeader("\t  Currency Exchange Screen");

        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";

        cout << "\n\t\t\t\t\t===========================================\n";
        cout << "\t\t\t\t\tPlease Enter A Number Between 1 and 5: ";
        _PerformMainOptions((enCurrencyOptions)clsInputValidate::ReadNumberBetween<int>(1, 5, "\t\t\t\t\tError: Out Of Range. Try Again: "));
	}
};

