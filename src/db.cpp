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
        db_logger.log(Log_level::ERROR, std::string(e.what()));
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
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec(
            R"(CREATE TABLE IF NOT EXISTS users (
                id SERIAL PRIMARY KEY,
                uuid VARCHAR(37) REFERENCES users(id),
                name VARCHAR(100) NOT NULL,
                username VARCHAR(50) UNIQUE NOT NULL,
                password VARCHAR(255) NOT NULL,
                email VARCHAR(100) UNIQUE NOT NULL,
                otp_is_enabled BOOLEAN DEFAULT FALSE,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP)"
        );
        w.commit();
        db_logger.log(Log_level::INFO, "Users table created successfully.");
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error creating users table: " + std::string(e.what()));
    }
    
}

void Database::create_table_credentials()
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec(
            R"(CREATE TABLE IF NOT EXISTS credentials (
                id SERIAL PRIMARY KEY,
                CONSTRAINT fk_uuid_user FOREIGN KEY (uuid) REFERENCES users(uuid),
                service_name VARCHAR(100) NOT NULL,
                username VARCHAR(50) NOT NULL,
                password VARCHAR(255) NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP)"
        );
        w.commit();
        db_logger.log(Log_level::INFO, "Credentials table created successfully.");
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error creating credentials table: " + std::string(e.what()));
    }
}

void Database::insert_user(const std::string &uuid,
                           const std::string &name,
                           const std::string &username,
                           const std::string &password,
                           const std::string &email,
                           bool otp_is_enabled)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("insert_user", uuid, name, username, password, email, otp_is_enabled);
        w.commit();
        db_logger.log(Log_level::INFO, "User inserted successfully: " + username);
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error inserting user: " + std::string(e.what()));
    }
}

void Database::insert_credentials(const std::string &service_name,
                                  const std::string &username,
                                  const std::string &password)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("insert_credentials", service_name, username, password);
        w.commit();
        db_logger.log(Log_level::INFO, "Credentials inserted successfully for service: " + service_name);
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error inserting credentials: " + std::string(e.what()));
    }
}

void Database::update_user(const std::string &uuid,
                         const std::string &name,
                         const std::string &username,
                         const std::string &password,
                         const std::string &email,
                         bool otp_is_enabled)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("update_user", uuid, name, username, password, email, otp_is_enabled);
        w.commit();
        db_logger.log(Log_level::INFO, "User updated successfully: " + username);
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error updating user: " + std::string(e.what()));
    }
}

void Database::update_credentials(const std::string &service_name,
                                  const std::string &username,
                                  const std::string &password)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("update_credentials", service_name, username, password);
        w.commit();
        db_logger.log(Log_level::INFO, "Credentials updated successfully for service: " + service_name);
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error updating credentials: " + std::string(e.what()));
    }
}

void Database::delete_user(const std::string &uuid)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("delete_user", uuid);
        w.commit();
        db_logger.log(Log_level::INFO, "User deleted successfully: " + uuid);
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error deleting user: " + std::string(e.what()));
    }
}

void Database::delete_credentials(const std::string &service_name,
                                  const std::string &username)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("delete_credentials", service_name, username);
        w.commit();
        db_logger.log(Log_level::INFO, "Credentials deleted successfully for service: " + service_name);
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error deleting credentials: " + std::string(e.what()));
    }
}

std::string Database::result_to_string(const pqxx::result &res)
{
    if(res.empty())
    {
        db_logger.log(Log_level::WARNING, "Result is empty.");
        return "";
    }
    std::stringstream result_str;
    for(const auto &row : res)
    {
        for(const auto &field : row)
        {
            result_str << field.as<std::string>() << " ";
        }
        result_str << "\n";
    }
    db_logger.log(Log_level::INFO, "Result converted to string successfully.");
    return result_str.str();
}

std::string Database::get_user(const std::string &uuid)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return "";
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_user", uuid);
        std::string user_result = result_to_string(res);
        db_logger.log(Log_level::INFO, "User retrieved successfully: " + uuid);
        return user_result;
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error retrieving user: " + std::string(e.what()));
        return "";
    }
}

std::string Database::get_hash_passwd(const std::string &username)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return "";
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_hash_passwd", username);
        std::string hash_passwd_result = result_to_string(res);
        db_logger.log(Log_level::INFO, "Password hash retrieved successfully for user: " + username);
        return hash_passwd_result;
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error retrieving password hash: " + std::string(e.what()));
        return "";
    }
}

pqxx::result Database::get_credentials(const std::string &service_name,
                                        const std::string &username)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return pqxx::result();
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_credentials", service_name, username);
        db_logger.log(Log_level::INFO, "Credentials retrieved successfully for service: " + service_name);
        return res;
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error retrieving credentials: " + std::string(e.what()));
        return pqxx::result();
    }
}

pqxx::result Database::get_all_credentials(const std::string &username)
{
    if(!conn->is_open())
    {
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
        return pqxx::result();
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_all_credentials", username);
        db_logger.log(Log_level::INFO, "All credentials retrieved successfully for user: " + username);
        return res;
    }
    catch(const std::exception& e)
    {
        db_logger.log(Log_level::ERROR, "Error retrieving credentials: " + std::string(e.what()));
        return pqxx::result();
    }
}