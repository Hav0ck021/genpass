#ifndef DB_H
#define DB_H

#include <iostream>
#include <pqxx/pqxx>

class Database
{
    private:
        pqxx::connection *conn;
        std::string db_name;
        std::string user;
        std::string password;
        std::string host;
        std::string port;
    public:
        Database(const char *filename);
        ~Database();
        void create_table_user();
        void create_table_credentials();
        void create_table_settings();
        void consult_table_user();
        void consult_table_credentials();
        void consult_table_settings();
};
#endif //DB_H
