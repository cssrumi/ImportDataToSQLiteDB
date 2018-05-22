#pragma once
#include <string>
#include "sqlite3.h"
#include "Data.h"
#include <fstream>

class SQLiteDB
{
public:
	SQLiteDB(string stringIN);
	~SQLiteDB();
	static int CallBack(void * NotUsed, int argc, char ** argv, char ** azColName);
	static int ToFile(void * NotUsed, int argc, char ** argv, char ** azColName);
	void Delete(string id);
	void CreateTable();
	void Exec(char * sql);
	void ExecWithOutResponse(char * sql);
	void Insert(Data data);
	void ExportToFile(char * sql);
	void Select(char * sql);
	void Response();
	void Disconnect();
private:
	char *sql;
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
};

