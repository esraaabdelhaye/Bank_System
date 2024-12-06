#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;
class clsTransferLogScreen : protected clsScreen
{
private:
	static void _PrintLogRecord(clsBankClient::stTransferLog Log) {
		cout << "\t| " << setw(25) << left << Log.Time;
		cout << "| " << setw(10) << left << Log.FirstAcc;
		cout << "| " << setw(10) << left << Log.SecondAcc;
		cout << "| " << setw(10) << left << Log.Amount;
		cout << "| " << setw(10) << left << Log.FirstBalance;
		cout << "| " << setw(10) << left << Log.SecondBalance;
		cout << "| " << setw(15) << left << Log.UserName;

	}
public:
	static void ShowTransferLog() {
		vector<clsBankClient::stTransferLog> vLogs = clsBankClient::GetTransLogStructs();

		string SubTitle = "\t  (" + to_string(vLogs.size()) + ") Transfer Log(s).";

		_ShowScreenHeader("\t    Transfer Log Screen", SubTitle);

		cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
		cout << "| " << left << setw(10) << "s.Acct";
		cout << "| " << left << setw(10) << "d.Acct";
		cout << "| " << left << setw(10) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(15) << "Username";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		// Table Body
		for (clsBankClient::stTransferLog Log : vLogs)
		{
			_PrintLogRecord(Log);
			cout << endl;
		}
		// Footer
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;
	}
};

