#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.isEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:

    static void ShowFindCurrencyScreen()
    {
        system("cls");
        _ShowScreenHeader("\t  Find Currency Screen");

        cout << "\n\t\t\t\t\tFind By: [1] Code or [2] Country ? ";
        short Answer = 1;

        Answer = clsInputValidate::ReadNumberBetween<int>(1, 2, "Error: Number Out Of Range. Try Again: ");

        if (Answer == 1)
        {
            string CurrencyCode;
            cout << "\n\t\t\t\t\tPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else
        {
            string Country;
            cout << "\n\t\t\t\t\tPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
        }

    }
};

