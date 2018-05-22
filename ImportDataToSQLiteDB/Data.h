#pragma once
#include <string>
#include <iostream>

using namespace std;

class Data
{
public:
	Data();
	~Data();
	int ReadInt(istream& stream);
	string ReadStr(istream& stream);
	void CreateObject();
	void SetFirstName(string firstName);
	string GetFirstName();
	void SetSurname(string surName);
	string GetSurname();
	void SetAge(string age);
	string GetAge();
	void Show();
private:
	string firstName;
	string surname;
	string age;
};

