#pragma once
#include<iostream>
#include"clsDate.h"
using namespace std;

class clsInputValidate
{
public:
	template<typename T> static bool IsNumberBetween(T num, T first, T last) {
		return (num >= first && num <= last);
	}

	template<typename T> static T ReadNumber(string ErrorMessage = "\n\t\t\t\t\tInvalid Number, Enter again: ") {
		T number;
		while (!(cin >> number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return number;
	}
	
	template<typename T> static int ReadNumberBetween(T from, T to, string Message) {

		T Number = ReadNumber<T>();
		while (!clsInputValidate::IsNumberBetween(Number, from, to)) {
			cout << Message;
			Number = ReadNumber<T>();
		}
		return Number;
	}

	static string ReadString() {
		string Input;
		// Using std::ws will extract all white spaces 
		getline(cin >> ws, Input);
		return Input;
	}

	static bool isDateBetween (clsDate Date, clsDate First, clsDate Last) {
		bool first = clsDate::CompareDates(Date, First) == clsDate::enDateCompare::After;
		bool second = clsDate::CompareDates(Date, Last) == clsDate::enDateCompare::Before;
		return (first && second);
	}

	static bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}
};

