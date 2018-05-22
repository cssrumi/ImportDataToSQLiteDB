#include "stdafx.h"
#include "SQLiteDB.h"
#include "sqlite3.h"
#include <cstdlib>
#include <string>
#include "Data.h"
#include <cstdio>
#include <fstream>


using namespace std;

SQLiteDB::SQLiteDB(string stringIN)
{
	const char* cstr = stringIN.c_str();
	rc = sqlite3_open(cstr, &db);
	CreateTable();
}


SQLiteDB::~SQLiteDB()
{
	Disconnect();
}


int SQLiteDB::CallBack(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


void SQLiteDB::ExportToFile(char *sql) {
	//Clear data in file
	ofstream outData;
	outData.open("output.csv", ofstream::out | ofstream::trunc);
	outData.close();
	//Set Column name
	outData.open("output.csv", ios::app);
	outData << "id;imie;nazwisko;wiek" << endl;
	outData.close();
	//Export new data to file
	const char* response = "Eksportuje...";
	rc = sqlite3_exec(db, sql, ToFile, (void*)response, &zErrMsg);
	Response();
}

int SQLiteDB::ToFile(void *NotUsed, int argc, char **argv, char **azColName) {
	string line = "";
	ofstream outData;
	outData.open("output.csv", ios::app);
	//Format data from select
	for (int i = 0; i<argc; i++) {
		line += argv[i];
		if (i + 1<argc)
			line += ";";
	}
	//Insert data into file
	if (outData.is_open()) {
		outData << line << endl;
	}
	else
		cout << "Brak dostêpu do pliku." << endl;
	outData.close();
	return 0;
}

void SQLiteDB::Delete(string id) {
	string del = "DELETE from DANEKLIENTOW where ID=" + id;
	sql = &del[0u];
	Exec(sql);
}

void SQLiteDB::CreateTable() {
	sql = (char*)"CREATE TABLE DANEKLIENTOW(" \
		"ID INTEGER PRIMARY KEY AUTOINCREMENT," \
		"IMIE			TEXT    NOT NULL," \
		"NAZWISKO		TEXT	NOT NULL," \
		"WIEK			INT		NOT NULL );";
	ExecWithOutResponse(sql);
}

void SQLiteDB::Exec(char *sql) {
	rc = sqlite3_exec(db, sql, CallBack, 0, &zErrMsg);
	Response();
}
void SQLiteDB::ExecWithOutResponse(char *sql) {
	rc = sqlite3_exec(db, sql, CallBack, 0, &zErrMsg);
}

void SQLiteDB::Insert(Data data) {
	string str = "insert into DANEKLIENTOW (" \
		"IMIE, " \
		"NAZWISKO, " \
		"WIEK" \
		") values ('" \
		+ data.GetFirstName() + "', '" \
		+ data.GetSurname() + "','" \
		+ data.GetAge() + "')";
	sql = &str[0u];
	Exec(sql);

}

void SQLiteDB::Select(char* sql) {
	const char* response = "Wynik wyboru :";
	rc = sqlite3_exec(db, sql, CallBack, (void*)response, &zErrMsg);
	Response();
}

void SQLiteDB::Response() {
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operacja zakonczona sukcesem\n");
	}
}

void SQLiteDB::Disconnect() {
	sqlite3_close(db);
}