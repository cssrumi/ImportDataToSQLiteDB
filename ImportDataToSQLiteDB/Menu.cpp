#include "stdafx.h"
#include "Menu.h"
#include <Windows.h>
#include <iostream>
#include "SQLiteDB.h"
#include <string>
#include "conio.h"
#include "Data.h"

using namespace std;

Menu::Menu()
{
	ChangeDB();
	StartMenu();
}


Menu::~Menu()
{
}


void Menu::StartMenu() {
	bool exit = false;
	char key;
	while (!exit) {
		PrintMenu();
		key = _getch();
		if (key == 'D' || key == 'd')
		{
			Add();
		}
		if (key == 'U' || key == 'u')
		{
			Delete();
		}
		if (key == 'W' || key == 'w')
		{
			ShowAll();
		}
		if (key == 'Z' || key == 'z')
		{
			ChangeDB();
		}
		if (key == 'P' || key == 'p')
		{
			Export();
		}
		if (key == 'E' || key == 'e')
		{
			exit = true;
		}
	}
}

void Menu::PrintMenu() {
	system("cls");
	cout << "Obecnie wybrana baza to : " << GetDataBaseName() << endl;
	cout << endl;
	cout << "Zmien nazwe bazy \t - Z" << endl;
	cout << "Dodaj osobe\t\t - D" << endl;
	cout << "Usun osobe\t\t - U" << endl;
	cout << "Wyswietl zawartosc bazy  - W" << endl;
	cout << "Wyeksportuj baze do pliku- P" << endl;
	cout << "Zamknij program \t - E" << endl;
}

void Menu::Add() {
	system("cls");
	Data *data = new Data();
	SQLiteDB *db = new SQLiteDB(GetDataBaseName());
	db->Insert(*data);
	delete db;
	system("pause");
}

void Menu::ChangeDB() {
	system("cls");
	string stringIN;
	cout << "Podaj nazwe bazy : ";
	cin >> stringIN;
	SetDataBaseName(stringIN);
	system("pause");
}

void Menu::SetDataBaseName(string stringIN) {
	this->dbName = stringIN;
}

string Menu::GetDataBaseName() {
	return dbName;
}

void Menu::Delete() {
	system("cls");
	string id;
	cout << "Podaj id osoby ktora chcesz usunac : ";
	cin >> id;
	SQLiteDB *db = new SQLiteDB(GetDataBaseName());
	db->Delete(id);
	delete db;
	system("pause");
}

void Menu::Export() {
	system("cls");
	SQLiteDB *db = new SQLiteDB(GetDataBaseName());
	char* select = (char*)"Select * from DANEKLIENTOW";
	db->ExportToFile(select);
	delete db;
	system("pause");
}

void Menu::ShowAll() {
	system("cls");
	char* select = (char*)"Select * from DANEKLIENTOW";
	SQLiteDB *db = new SQLiteDB(GetDataBaseName());
	db->Select(select);
	delete db;
	system("pause");
}