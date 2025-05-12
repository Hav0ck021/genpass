#ifndef GENPASS_DB_H
#define GENPASS_DB_H

#include <iostream>
#include <sqlite3.h>

using namespace std;

int createDB(){
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("genPass.db", &DB);

    if(exit){
        cerr << "Error opening DB! " << sqlite3_errmsg(DB) << " : " << sqlite3_errcode(DB) << endl;
        return (-1);
    } else {
        cout << "DataBase opened successfully!" << endl;
    }
    sqlite3_close(DB);
    return 0;
}

int createTable(sqlite3* DB){
    string sql = "CREATE TABLE PERSON("
                 "ID INT PRIMARY KEY     NOT NULL, "
                 "NAME           TEXT    NOT NULL, "
                 "NICK           TEXT     NOT NULL, "
                 "PASS            INT     NOT NULL;";

}

#endif //GENPASS_DB_H
