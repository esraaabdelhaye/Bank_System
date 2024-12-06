#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:
    static void _ShowScreenHeader(string Title, string subTitle = "") {
        ShowUserNameAndDate();

        cout << "\n\n\t\t\t\t\t===========================================";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (subTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << subTitle;
        }
        cout << "\n\n\t\t\t\t\t===========================================\n\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission) {
        if (currentUser.hasPermission(Permission)) {
            return true;
        }
        else {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            return false;
        }
    }

    static void ShowUserNameAndDate() {
        clsDate Today = clsDate::GetSystemDate();
        string UserName = currentUser.UserName;

        cout << "\t\t\t\t\t===========================================\n\n";
        cout << "\t\t\t\t\tDate: " << clsDate::DateToString(Today);
        cout << "\n\t\t\t\t\tUserName: " << UserName;

    }
};

