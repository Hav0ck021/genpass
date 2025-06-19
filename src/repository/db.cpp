#include "core/log.h"
#include "repository/db.h"
#include <functional>
#include <pqxx/pqxx>
#include <iostream>

Database::Database(){}

Database::~Database()
{
    Log::log(Log_level::INFO, "Database destructor called.");
    conn->disconnect();
}

void Database::connect(std::string host, std::string port, std::string db_name, std::string user, std::string passwd)
{
    
    std::string conn_str = "host=" + host
                         + " port=" + port
                         + " dbname=" + db_name
                         + " user=" + user
                         + " password=" + passwd;
    conn = std::make_unique<pqxx::connection>(conn_str);
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Failed to connect to the database.");
        return;
    }
    Log::log(Log_level::INFO, "Connected to the database successfully.");
    
    /*
        Prepare statements from query strings.
        These statements are used to interact with the GenPass database.
        They are prepared once and can be reused multiple times.
    */

    // Insert User
    conn->prepare("insert_user", "INSERT INTO users (uuid, name, username, password, email, otp_is_enabled, token) VALUES ($1, $2, $3, $4, $5, $6, $7);");
    
    // Insert Credentials
    conn->prepare("insert_credentials","INSERT INTO credentials (uuid, service_name, username, password) VALUES ($1, $2, $3, $4);");

    // Update User
    conn->prepare("update_user", "UPDATE users SET name = $2, username = $3, password = $4, email = $5, otp_is_enabled = $6 WHERE uuid = $1;");

    // Update User Password
    conn->prepare("update_user_password", "UPDATE users SET password = $2 WHERE username = $1;");

    // Update Credentials
    conn->prepare("update_credentials", "UPDATE credentials SET password = $3 WHERE service_name = $1 AND username = $2;");

    // Delete User
    conn->prepare("delete_user", "DELETE FROM users WHERE uuid = $1;");

    // Delete Credentials
    conn->prepare("delete_credentials", "DELETE FROM credentials WHERE service_name = $1 AND username = $2;");

    // Get User
    conn->prepare("get_user", "SELECT * FROM users WHERE uuid = $1;");

    // Get Password
    conn->prepare("get_hash_passwd", "SELECT password FROM users WHERE username = $1;");

    // Get OTP Status
    conn->prepare("get_otp_status", "SELECT otp_is_enabled FROM users WHERE username = $1;");

    // Get Token Session
    conn->prepare("get_user_token_session", "SELECT token FROM users WHERE username = $1;");
    
    // Get User UUID by Username
    conn->prepare("get_user_uuid_by_username", "SELECT uuid FROM users WHERE username = $1;");
    
    // Get Credentials from user
    conn->prepare("get_credentials", "SELECT * FROM credentials WHERE service_name = $1 AND username = $2;");

    // Get all Credentials from user
    conn->prepare("get_all_credentials", "SELECT * FROM credentials WHERE username = $1;");
}

std::unordered_map<std::string, std::string> Database::load_env_file(const std::string& filename)
{
    std::unordered_map<std::string, std::string> env_vars;
    std::ifstream file(filename);
    if(!file.is_open())
    {
        Log::log(Log_level::ERROR, "Could not open environment file: " + filename);
        return env_vars;
    }
    std::string line;
    while(std::getline(file, line))
    {
        if(line.empty() || line[0] == '#') // Skip empty lines and comments
            continue;
        
        size_t pos = line.find('=');
        if(pos != std::string::npos)
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            env_vars[key] = value;
        }
    }
    
    file.close();
    return env_vars;
}

void Database::set_db_config(const std::unordered_map<std::string, std::string> &env_vars)
{
    std::unordered_map<std::string_view, std::function<void(std::string_view)>> dispatcher = {
        {"DB_NAME",     [&](std::string_view val) { db_name = std::string(val); }},
        {"DB_USERNAME", [&](std::string_view val) { user = std::string(val); }},
        {"DB_PASSWORD", [&](std::string_view val) { passwd = std::string(val); }},
        {"DB_HOSTNAME", [&](std::string_view val) { host = std::string(val); }},
        {"DB_PORT",     [&](std::string_view val) { 
            try {
                port = std::stoi(std::string(val));
            } catch (...) {
                std::cerr << "DB_PORT inválido: " << val << "\n";
            }
        }},
    };

    for (const auto& [key, value] : env_vars) {
        auto it = dispatcher.find(key);
        if (it != dispatcher.end()) {
            it->second(value);
        }
    }
}

void Database::create_table_user()
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec(
            R"(CREATE TABLE IF NOT EXISTS users (
                id SERIAL PRIMARY KEY,
                uuid VARCHAR(37) UNIQUE NOT NULL,
                name VARCHAR(100) NOT NULL,
                username VARCHAR(50) UNIQUE NOT NULL,
                password VARCHAR(255) NOT NULL,
                email VARCHAR(100) UNIQUE NOT NULL,
                otp_is_enabled BOOLEAN DEFAULT FALSE,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                token VARCHAR(255) DEFAULT '');)"
        );
        w.commit();
        Log::log(Log_level::INFO, "Users table created successfully.");
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error creating users table: " + std::string(e.what()));
    }
}

void Database::create_table_credentials()
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec(
            R"(CREATE TABLE IF NOT EXISTS credentials (
                id SERIAL PRIMARY KEY,
                uuid VARCHAR(37) NOT NULL REFERENCES users(uuid),
                service_name VARCHAR(100) NOT NULL,
                username VARCHAR(50) NOT NULL,
                password VARCHAR(255) NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );)"
        );
        w.commit();
        Log::log(Log_level::INFO, "Credentials table created successfully.");
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error creating credentials table: " + std::string(e.what()));
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
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("insert_user", uuid, name, username, password, email, otp_is_enabled, "");
        pqxx::result r = w.exec("SELECT * FROM users WHERE username = " + w.quote(username));

        w.commit();
        Log::log(Log_level::INFO, "User inserted successfully: " + username);
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error inserting user: " + std::string(e.what()));
    }
}

void Database::insert_credentials(const std::string &service_name,
                                  const std::string &username,
                                  const std::string &password)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result r = w.exec_prepared("get_user_uuid_by_username", username);
        if(r.empty())
        {
            Log::log(Log_level::ERROR, "User not found: " + username);
            return;
        }
        std::string uuid = r[0][0].as<std::string>();
        w.exec_prepared("insert_credentials", uuid, service_name, username, password);
        w.commit();
        Log::log(Log_level::INFO, "Credentials inserted successfully for service: " + service_name);
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, " inserting credentials: " + std::string(e.what()));
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
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("update_user", uuid, name, username, password, email, otp_is_enabled);
        w.commit();
        Log::log(Log_level::INFO, "User updated successfully: " + username);
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error updating user: " + std::string(e.what()));
    }
}

void Database::update_user_password(const std::string &username, const std::string &password)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("update_user_password", username, password);
        w.commit();
        Log::log(Log_level::INFO, "Password updated successfully for user: " + username);
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error updating password: " + std::string(e.what()));
    }
}

void Database::update_credentials(const std::string &service_name,
                                  const std::string &username,
                                  const std::string &password)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("update_credentials", service_name, username, password);
        w.commit();
        Log::log(Log_level::INFO, "Credentials updated successfully for service: " + service_name);
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error updating credentials: " + std::string(e.what()));
    }
}

void Database::delete_user(const std::string &uuid)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("delete_user", uuid);
        w.commit();
        Log::log(Log_level::INFO, "User deleted successfully: " + uuid);
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error deleting user: " + std::string(e.what()));
    }
}

void Database::delete_credentials(const std::string &service_name,
                                  const std::string &username)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return;
    }
    pqxx::work w(*conn);
    try
    {
        w.exec_prepared("delete_credentials", service_name, username);
        w.commit();
        Log::log(Log_level::INFO, "Credentials deleted successfully for service: " + service_name);
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error deleting credentials: " + std::string(e.what()));
    }
}

std::string Database::result_to_string(const pqxx::result &res)
{
    if(res.empty())
    {
        Log::log(Log_level::WARNING, "Result is empty.");
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
    Log::log(Log_level::INFO, "Result converted to string successfully.");
    return result_str.str();
}

std::string Database::get_user(const std::string &uuid)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return "";
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_user", uuid);
        std::string user_result = result_to_string(res);
        Log::log(Log_level::INFO, "User retrieved successfully: " + uuid);
        return user_result;
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error retrieving user: " + std::string(e.what()));
        return "";
    }
}

std::string Database::get_hash_passwd(const std::string &username)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return "";
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_hash_passwd", username);
        std::string hash_passwd_result = result_to_string(res);
        Log::log(Log_level::INFO, "Password hash retrieved successfully for user: " + username);
        return hash_passwd_result;
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error retrieving password hash: " + std::string(e.what()));
        return "";
    }
}

bool Database::get_otp_status(const std::string &username)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return false;
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_otp_status", username);
        bool otp_status = res[0]["otp_is_enabled"].as<bool>();
        Log::log(Log_level::INFO, "OTP status retrieved successfully for user: " + username);
        return otp_status;
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error retrieving OTP status: " + std::string(e.what()));
        return false;
    }
    return true;
}

std::string Database::get_user_token_session(const std::string &username)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return "";
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_user_token_session", username);
        if(res.empty())
        {
            Log::log(Log_level::WARNING, "No session token found for user: " + username);
            return "";
        }
        std::string token = res[0][0].as<std::string>();
        Log::log(Log_level::INFO, "Session token retrieved successfully for user: " + username);
        return token;
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error retrieving session token: " + std::string(e.what()));
        return "";
    }
}


pqxx::result Database::get_credentials(const std::string &service_name,
                                        const std::string &username)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return pqxx::result();
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_credentials", service_name, username);
        Log::log(Log_level::INFO, "Credentials retrieved successfully for service: " + service_name);
        return res;
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error retrieving credentials: " + std::string(e.what()));
        return pqxx::result();
    }
}

pqxx::result Database::get_all_credentials(const std::string &username)
{
    if(!conn->is_open())
    {
        Log::log(Log_level::ERROR, "Database connection is not open.");
        return pqxx::result();
    }
    pqxx::work w(*conn);
    try
    {
        pqxx::result res = w.exec_prepared("get_all_credentials", username);
        Log::log(Log_level::INFO, "All credentials retrieved successfully for user: " + username);
        return res;
    }
    catch(const std::exception& e)
    {
        Log::log(Log_level::ERROR, "Error retrieving credentials: " + std::string(e.what()));
        return pqxx::result();
    }
}