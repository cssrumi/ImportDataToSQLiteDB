#include "stdafx.h"
#include "Data.h"
#include <string>
#include <iostream>

using namespace std;

Data::Data()
{
	CreateObject();
}


Data::~Data()
{
}

void Data::Show() {
	cout << "Imie : " + GetFirstName() << endl;
	cout << "Nazwisko : " + GetSurname() << endl;
	cout << "Wiek : ";
	cout << GetAge() << endl;
}

int Data::ReadInt(istream& stream) {
	int i;
	stream >> i;
	return i;
}

string Data::ReadStr(istream& stream) {
	string s;
	stream >> s;
	return s;
}

void Data::CreateObject() {
	string message = "Podaj (oddzielone spacja) :\nimie nazwisko wiek";
	cout << message << endl;
	SetFirstName(ReadStr(cin));
	SetSurname(ReadStr(cin));
	SetAge(ReadStr(cin));
}


//SETGET
void Data::SetFirstName(string firstName) {
	this->firstName = firstName;
}

string Data::GetFirstName() {
	return firstName;
}

void Data::SetSurname(string surName) {
	this->surname = surName;
}

string Data::GetSurname() {
	return surname;
}

void Data::SetAge(string age) {
	this->age = age;
}

string Data::GetAge() {
	return age;
}