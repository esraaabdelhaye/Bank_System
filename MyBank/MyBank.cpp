#pragma once
#include <iostream>
#include "clsUtil.h"
#include "clsDate.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsLoginScreen.h"

int main()

{
    bool stillHasTrails = true;
    while (stillHasTrails) {
        stillHasTrails = clsLoginScreen::ShowLoginScreen();
    }
    system("pause>0");

    return 0;
}