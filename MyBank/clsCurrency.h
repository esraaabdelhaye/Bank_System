#pragma once
#include <iostream>
#include <vector>
#include "clsString.h"
#include "string"
#include "fstream"
using namespace std;

class clsCurrency
{
private:
	enum enMode {eEmptyMode = 1, eUpdatedMode };

	enMode _Mode;
	string _Country;
	string _CurrencyName;
	string _CurrencyCode;
	float _Rate;


	static clsCurrency _ConvertLineToCurrencyObject(string Line) {
		vector<string> vWords = clsString::Split(Line,"#//#");
		return clsCurrency(vWords[0], vWords[1], vWords[2], stof(vWords[3]), enMode::eUpdatedMode);
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency) {
		return Currency.Country() + "#//#" +
			Currency.CurrencyCode() + "#//#" +
			Currency.CurrencyName() + "#//#" +
			to_string(Currency.Rate());
	}

	static vector<clsCurrency> _LoadObjectsFromFile() {
		vector<clsCurrency> vCurrencies;
		fstream myFile;
		myFile.open("Currencies.txt", ios::in);
		if (myFile.is_open()) {
			string Line = "";
			while (getline(myFile, Line)) {
				vCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
			}
			myFile.close();
		}

		return vCurrencies;
	}

	static void _SaveCurrenciesToFile(vector<clsCurrency> vCurrencies) {
		fstream myFile;
		myFile.open("Currencies.txt", ios::out);
		if (myFile.is_open()) {
			for (clsCurrency& C : vCurrencies) {
				myFile << _ConvertCurrencyObjectToLine(C) << endl;
			}
			myFile.close();
		}
	}

	void _Update() {
		vector<clsCurrency> vCurrencies = _LoadObjectsFromFile();

		for (clsCurrency& C : vCurrencies) {
			if (C.CurrencyCode() == CurrencyCode()) {
				C = *this;
				break;
			}
		}

		_SaveCurrenciesToFile(vCurrencies);
	}

	static clsCurrency _GetEmptyCurrency() {
		return { "","","",0,enMode::eEmptyMode };
	}

public:

	clsCurrency(string Country,string Appriviation,  string Name, float Value, enMode Mode) {
		_Country = Country;
		_CurrencyName = Country;
		_CurrencyCode = Appriviation;
		_Rate = Value;
		_Mode = Mode;
	}

	bool isEmpty() {
		return (_Mode == enMode::eEmptyMode);
	}

	string Country() {
		return _Country;
	}

	string CurrencyCode() {
		return _CurrencyCode;
	}

	string CurrencyName() {
		return _CurrencyName;
	}

	float Rate() {
		return _Rate;
	}

	void UpdateRate(float NewRate) {
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCode(string Code) {
		string CurrencyCode = clsString::UpperAllString(Code);
		vector<clsCurrency> vCurrencies = GetCurrenciesList();

		for (clsCurrency& C : vCurrencies) {
			if (C.CurrencyCode() == CurrencyCode) {
				return C;
			}
		}

		return _GetEmptyCurrency();
	}

	static clsCurrency FindByCountry(string Country) {
		string CurrencyCountry = clsString::UpperAllString(Country);
		vector<clsCurrency> vCurrencies = GetCurrenciesList();

		for (clsCurrency& C : vCurrencies) {
			if (clsString::UpperAllString(C.Country()) == CurrencyCountry) {
				return C;
			}
		}

		return _GetEmptyCurrency();
	}

	static bool isCurrencyExist(string CurrencyCode) {
		clsCurrency FoundCurrency = FindByCode(CurrencyCode);
		return(!(FoundCurrency.isEmpty()));
	}

	static vector<clsCurrency> GetCurrenciesList() {
		return _LoadObjectsFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.Rate());

	}
};

