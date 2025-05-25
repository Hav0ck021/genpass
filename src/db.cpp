#include "../include/user.h"
#include "../include/app.h"
#include "../include/log.h"
#include "../include/db.h"

Logger db_logger("../logs/genpass.log");

Database::Database(const char *filename)
{
    db_logger.log(Log_level::INFO, "Database constructor called.");
    try
    {
        conn = new pqxx::connection(filename);
        if (conn->is_open())
        {
            db_logger.log(Log_level::INFO, "Opened database successfully: " + Database::db_name);
        }
        else
        {
            db_logger.log(Log_level::ERROR, "Can't open database");
            exit(1);
        }
    }
    catch (const std::exception &e)
    {
        db_logger.log(Log_level::ERROR, e.what());
        exit(1);
    }
}

Database::~Database()
{
    db_logger.log(Log_level::INFO, "Database destructor called.");
    conn->disconnect();
    delete conn;
}

void Database::create_table_user()
{
    // Development
}

void Database::create_table_credentials()
{
    // Development
}

void Database::create_table_settings()
{
    // Development
}

void Database::consult_table_credentials()
{
    // Development
}

void Database::consult_table_settings()
{
    // Development
}