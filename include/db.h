#ifndef DB_H
#define DB_H

#include <iostream>
#include <pqxx>

using namespace std;

class Database
{
    private:

    public:
        Database(const char *filename);
        ~Database();
        // Function to create table to users (SQL)
        // Function to create table to credentials (NoSQL)
        // Function to create table to settings (NoSQL)
        // Function to consult table to users (SQL)
        // Function to consult table to credentials (NoSQL)
        // Function to consult table to settings (NoSQL)
};
#endif //DB_H
