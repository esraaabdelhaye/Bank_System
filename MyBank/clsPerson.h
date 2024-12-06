#pragma once
#include <iostream>
using namespace std;

class clsPerson
{
private:
	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:
	clsPerson(string firstname, string lastname, string email, string phone) {
		_FirstName = firstname;
		_LastName = lastname;
		_Email = email;
		_Phone = phone;
	}

	void setFirstName(string firstName) {
		_FirstName = firstName;
	}

	string getFirstName() {
		return _FirstName;
	}

	_declspec(property(put = setFirstName, get = getFirstName)) string FirstName;

	void setLastName(string lastName) {
		_LastName = lastName;
	}

	string getLastName() {
		return _LastName;
	}

	_declspec(property(put = setLastName, get = getLastName)) string LastName;

	void setEmail(string Email) {
		_Email = Email;
	}

	string getEmail() {
		return _Email;
	}

	_declspec(property(put = setEmail, get = getEmail)) string Email;

	void setPhone(string phone) {
		_Phone = phone;
	}

	string getPhone() {
		return _Phone;
	}

	_declspec(property(put = setPhone, get = getPhone)) string Phone;

	string FullName()
	{
		return FirstName + " " + LastName;
	}
};

