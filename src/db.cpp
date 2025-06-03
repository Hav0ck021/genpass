#include "../include/user.h"
// #include "../include/app.h"
#include "../include/log.h"
#include "../include/db.h"
#include <pqxx/pqxx>
#include <iostream>

Logger Database::db_logger;

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
        }
    }
    catch (const std::exception &e)
    {
        db_logger.log(Log_level::ERROR, std::string(e.what()));
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
        db_logger.log(Log_level::ERROR, "Database connection is not open.");
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
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                token VARCHAR(255) DEFAULT NULL)"
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

bool Database::get_otp_status(const std::string &username)
{
    return true;
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

int main() {
    // Ajuste o nome do banco de dados conforme necessário para seu ambiente
    const char* conninfo = "dbname=testdb user=postgres password=postgres host=localhost";
    Database db(conninfo);

    // Teste criação de tabelas
    db.create_table_user();
    db.create_table_credentials();

    // Teste inserção de usuário
    std::string uuid = "123e4567-e89b-12d3-a456-426614174000";
    std::string name = "Test User";
    std::string username = "testuser";
    std::string password = "hashedpassword";
    std::string email = "testuser@example.com";
    bool otp_enabled = true;
    db.insert_user(uuid, name, username, password, email, otp_enabled);

    // Teste inserção de credenciais
    std::string service_name = "github";
    std::string cred_username = "testuser";
    std::string cred_password = "servicepassword";
    db.insert_credentials(service_name, cred_username, cred_password);

    // Teste atualização de usuário
    std::string new_name = "Test User Updated";
    db.update_user(uuid, new_name, username, password, email, otp_enabled);

    // Teste atualização de credenciais
    std::string new_password = "newservicepassword";
    db.update_credentials(service_name, cred_username, new_password);

    // Teste obtenção de usuário
    std::string user_info = db.get_user(uuid);
    std::cout << "User info:\n" << user_info << std::endl;

    // Teste obtenção de hash da senha
    std::string hash = db.get_hash_passwd(username);
    std::cout << "Hash password:\n" << hash << std::endl;

    // Teste status OTP
    bool otp_status = db.get_otp_status(username);
    std::cout << "OTP status: " << (otp_status ? "enabled" : "disabled") << std::endl;

    // Teste obtenção de credenciais
    pqxx::result creds = db.get_credentials(service_name, cred_username);
    std::cout << "Credentials for service:\n" << db.result_to_string(creds) << std::endl;

    // Teste obtenção de todas as credenciais
    pqxx::result all_creds = db.get_all_credentials(cred_username);
    std::cout << "All credentials for user:\n" << db.result_to_string(all_creds) << std::endl;

    // Teste remoção de credenciais
    db.delete_credentials(service_name, cred_username);

    // Teste remoção de usuário
    db.delete_user(uuid);

    return 0;
}