#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include "clsUtil.h"
#include <vector>
#include <string>
using namespace std;


class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 1, UpdatedMode = 2, AddNewMode };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;

	bool _MarkedForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#") {
		vector<string> vWords = clsString::Split(Line, Separator);
		clsUser Client(vWords[0], vWords[1], vWords[2], vWords[3], vWords[4], clsUtil::DecryptText(vWords[5]), stoi(vWords[6]), enMode::UpdatedMode);
		return Client;
	}

	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#") {
		return User.FirstName + Separator +
			User.LastName + Separator +
			User.Email + Separator +
			User.Phone + Separator +
			User.UserName + Separator +
			clsUtil::EncryptText(User.Password) + Separator +
			to_string(User.Permissions);
	}

	static vector<clsUser> _LoadUserssDataFromFile() {
		vector<clsUser> vUsers;
		fstream myFile;
		myFile.open("Users.txt", ios::in);
		if (myFile.is_open()) {
			string line = "";
			while (getline(myFile, line)) {
				clsUser User = _ConvertLineToUserObject(line);
				vUsers.push_back(User);
			}
			myFile.close();
		}
		return vUsers;
	}

	static void _SaveDataToFile(vector<clsUser> vUsers) {
		fstream myFile;
		myFile.open("Users.txt", ios::out);
		if (myFile.is_open()) {
			for (clsUser& U : vUsers) {
				if (!U.MarkedForDelete) {
					string Line = _ConvertUserObjectToLine(U);
					myFile << Line << endl;
				}
			}
			myFile.close();
		}
	}

	static clsUser _GetEmptyUserObject() {
		clsUser User("", "", "", "", "", "", 0, enMode::EmptyMode);
		return User;
	}

	void _AddDataLineToFile(string Line) {
		fstream myFile;
		myFile.open("Users.txt", ios::app);
		if (myFile.is_open()) {
			myFile << Line << endl;
			myFile.close();
		}
	}

	void _Update() {
		vector<clsUser> vUsers = _LoadUserssDataFromFile();
		for (clsUser& U : vUsers) {
			if (U.UserName == this->UserName) {
				U = *this;
				break;
			}
		}
		_SaveDataToFile(vUsers);
	}

	void _AddNew() {
		this->_Mode = enMode::UpdatedMode;
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	static vector <string> _GetRegisterRecords() {
		vector<string> vLoginLines;
		fstream myFile;
		myFile.open("LoginRegister.txt", ios::in);
		if (myFile.is_open()) {
			string Line = "";
			while (getline(myFile, Line)) {
				vLoginLines.push_back(Line);
			}
			myFile.close();
		}
		return vLoginLines;
	}

public:
	struct stLoginRegisterRecord {
		string registTime;
		string registName;
		string registPass;
		int registPermission;
	};

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pRegister = 128
	};

	bool hasPermission(enPermissions Permission) {
		if (Permission == enPermissions::eAll)
			return true;
		if ((Permission & this->Permissions) == Permission)
			return true;
		else return false;
	}

	clsUser(string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions, enMode Mode)
		:clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	void setMode(enMode Mode) {
		_Mode = Mode;
	}

	enMode getMode() {
		return _Mode;
	}

	_declspec(property(get = getMode, put = setMode)) enMode Mode;

	void setUserName(string Name) {
		_UserName = Name;
	}

	string getUserName() {
		return _UserName;
	}

	_declspec(property(get = getUserName, put = setUserName)) string UserName;

	void setPassword(string Pass) {
		_Password = Pass;
	}

	string getPassword() {
		return _Password;
	}

	_declspec(property(get = getPassword, put = setPassword)) string Password;

	void setPermissions(int Permissions) {
		_Permissions = Permissions;
	}

	int getPermissions() {
		return _Permissions;
	}

	_declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

	void setMarkedForDelete(bool Deleted) {
		_MarkedForDelete = Deleted;
	}

	bool getMarkedForDelete() {
		return _MarkedForDelete;
	}

	_declspec(property(get = getMarkedForDelete, put = setMarkedForDelete)) bool MarkedForDelete;

	static vector<clsUser> GetUsersData() {
		return _LoadUserssDataFromFile();
	}

	bool isEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	static clsUser GetAddNewUserObject(string UserName) {
		clsUser User("", "", "", "", "", UserName, 0, enMode::AddNewMode);
		return User;
	}

	static clsUser Find(string UserName) {

		vector<clsUser> vUsers;
		fstream myFile;
		myFile.open("Users.txt", ios::in);
		if (myFile.is_open()) {

			string line = "";
			while (getline(myFile, line)) {
				clsUser User = _ConvertLineToUserObject(line);
				if (User.UserName == UserName) {
					cout << User.Password << endl;
					
					return User;
					myFile.close();
				}
				vUsers.push_back(User);
			}
			myFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password) {
		clsUser UserFound = clsUser::Find(UserName);
		if (UserFound.Password == Password)
			return UserFound;

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName) {
		clsUser UserFound = clsUser::Find(UserName);
		return (!UserFound.isEmpty());
	}


	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1 };
	enSaveResults Save() {
		switch (_Mode) {
		case enMode::EmptyMode:
			return enSaveResults::svFailedEmptyObject;
			break;
		case enMode::UpdatedMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;
		case enMode::AddNewMode:
			_AddNew();
			return enSaveResults::svSucceeded;
			break;
		}
	}

	bool Delete() {
		vector<clsUser> vUsers = clsUser::GetUsersData();

		for (clsUser& U : vUsers) {
			if (U.UserName == UserName) {
				U.MarkedForDelete = true;
				break;
			}
		}
		_SaveDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	static vector<stLoginRegisterRecord> GetRegisterStructs() {
		vector<stLoginRegisterRecord> vLogins;
		vector<string> vRegisterLines = _GetRegisterRecords();
		for (string line : vRegisterLines) {
			vector<string> stringStruct = clsString::Split(line, "#//#");
			stLoginRegisterRecord Record = { stringStruct[0], stringStruct[1], stringStruct[2], stoi(stringStruct[3]) };
			vLogins.push_back(Record);
		}
		return vLogins;
	}
};
