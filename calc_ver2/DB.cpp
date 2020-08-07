#include<mysql.h>
#include<iostream>
#include<string>
#include"DB.h"

#define DB_HOST	
#define DB_USER		
#define DB_PASSWD
#define DB_NAME		

using namespace std;


DB::DB(void) {  // 积己磊

    DB::connection = NULL;
    mysql_init( &(DB::conn));
    DB::connection = mysql_real_connect(&(DB::conn), DB_HOST, DB_USER, DB_PASSWD, DB_NAME, 3306, (char*)NULL, 0);

    if (connection == NULL)
    {
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&(DB::conn)));
    }
    else {
        string sql = "SELECT COUNT(company) FROM company_info";
        DB::inputsql(sql);
        DB::sql_result = mysql_store_result(DB::connection);
        DB::sql_row = mysql_fetch_row(DB::sql_result);
        DB::code_cnt = atoi(DB::sql_row[0]);
        //cout << "DB 立辟\n";
    }


};
void DB::inputsql(string str) {

    char insql[128];
    strcpy_s(insql, sizeof(insql), str.c_str());
    int query_stat = mysql_query(connection, insql);
    if (query_stat != 0)
    {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&(DB::conn)));
    }
    else {
        //cout << "DB 立辟\n";
    }
}
void DB::close() {
    mysql_close(DB::connection);
}
int DB::get_dataCount(string code, string startDate, string endDate) {
    string sql = "SELECT COUNT(close) FROM daily_price WHERE CODE='"+ code +"' AND DATE >= '"+ startDate +"' and DATE <= '"+ endDate +"'";
    int count = 0;
    DB::inputsql(sql);
    DB::sql_result = mysql_store_result(DB::connection);
    while ((DB::sql_row = mysql_fetch_row(DB::sql_result)) != NULL)
    {
        //printf("%s\n", sql_row[0]);
        count = atoi(DB::sql_row[0]);
    }
    return count;
}
void DB::req_data(string code, string startDate, string endDate) {
    string sql = "SELECT close FROM daily_price WHERE CODE='" + code + "' AND DATE >= '" + startDate + "' and DATE <= '" + endDate + "'";
    DB::inputsql(sql);
    DB::sql_result = mysql_store_result(DB::connection);
}
MYSQL_ROW DB::get_data(){
    DB::sql_row = mysql_fetch_row(DB::sql_result);
    return DB::sql_row;
}

