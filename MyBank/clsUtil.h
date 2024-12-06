#pragma once
#include <iostream>
#include<time.h>
#include"clsDate.h"
using namespace std;

class clsUtil
{
public:
	enum enCharType { Capital = 1, Small, Digit, SpecialChar, MixChar };

	static void Srand() {
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int from, int to) {
		return rand() % (to - from + 1) + from;
	}

	static char GetRandomCharacter(enCharType Type) {
		int from = 0, to = 0;
		switch (Type) {
		case enCharType::Capital:
			from = 65;
			to = 90;
			break;
		case enCharType::Small:
			from = 97;
			to = 122;
			break;
		case enCharType::SpecialChar:
			from = 33;
			to = 47;
			break;
		case enCharType::MixChar:
			from = 33;
			to = 122;
			break;
		case enCharType::Digit:
			from = 48;
			to = 57;
			break;
		}
	defualt:
		{
			from = 65;
			to = 90;
		}
		return char(RandomNumber(from, to));
	}

	static string GenerateWord(enCharType Type, int length) {
		string Word = "";
		for (int i = 0; i < length; i++) {
			Word += clsUtil::GetRandomCharacter(Type);
		}
		return Word;
	}

	static string GenerateKey(enCharType Type) {
		string Key = "";
		for (int i = 0; i < 4; i++) {
			Key += GenerateWord(Type, 4);
			Key += "-";
		}
		return Key.substr(0, Key.length() - 1);
	}

	static void GenerateKeys(int num, enCharType Type) {
		string word = "";
		for (int i = 0; i < num; i++) {
			cout << "Key [" << i << "] : ";
			GenerateKey(Type);
		}
	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = RandomNumber(From, To);
	}

	static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, Wordlength);

	}

	static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
	{
		for (int i = 0; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}

	static void Swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}

	static void Swap(double& a, double& b) {
		double temp = a;
		a = b;
		b = temp;
	}

	static void Swap(string& a, string& b) {
		string temp = a;
		a = b;
		b = temp;
	}

	static void Swap(bool& a, bool& b) {
		bool temp = a;
		a = b;
		b = temp;
	}

	static void Swap(char& a, char& b) {
		char temp = a;
		a = b;
		b = temp;
	}

	static  void Swap(clsDate& A, clsDate& B)
	{
		clsDate::SwapDates(A, B);
	}

	static  void ShuffleArray(int arr[100], int arrLength)
	{

		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}

	}

	static  void ShuffleArray(string arr[100], int arrLength)
	{

		for (int i = 0; i < arrLength; i++)
		{
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}

	}

	static string  Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i < NumberOfTabs; i++)
		{
			t = t + "\t";
		}
		return t;

	}

	static string  EncryptText(string Text, short EncryptionKey = 2)
	{
		//cout << "Original text: " << Text << endl;
		for (int i = 0; i <= Text.length(); i++)
		{

			Text[i] = char((int)Text[i] + EncryptionKey);

		}
		//cout << "Text After Encryption: " << endl;
		return Text;

	}

	static string  DecryptText(string Text, short EncryptionKey = 2)
	{
		//cout << "Encrypted Text: " << Text << endl;
		for (int i = 0; i <= Text.length(); i++)
		{

			Text[i] = char((int)Text[i] - EncryptionKey);

		}
		//cout << "Text After Decryption: " << Text << endl;
		return Text;

	}

	static string NumberToText(int Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}
	}
};

