#pragma once
#include "stdafx.h"
#include "Menu.h"
#include <Windows.h>
#include <iostream>
#include "SQLiteDB.h"
#include <string>
#include "Data.h"

#pragma execution_character_set( "utf-8" )

using namespace std;

class Menu
{
public:
	Menu();
	~Menu();
	void StartMenu();
	void PrintMenu();
	void Add();
	void ChangeDB();
	void SetDataBaseName(string stringIN);
	string GetDataBaseName();
	void Delete();
	void Export();
	void ShowAll();
private:
	string dbName;
};

