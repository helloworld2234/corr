#pragma once
#include<mysql.h>
using namespace std;

class DB {
public:
	DB();
	void inputsql(string sql );
	int get_dataCount(string code, string startDate, string endDate);
	void req_data(string code, string startDate, string endDate);
	void close();
	MYSQL_ROW get_data();
	MYSQL* connection;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int code_cnt;
};