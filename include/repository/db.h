#ifndef DB_H
#define DB_H
#include "core/log.h"
#include "interface/idb.h"
#include <unordered_map>
#include <pqxx/pqxx>
#include <iostream>

class Database : public IDatabase
{
    private:
        std::unique_ptr<pqxx::connection> conn;
        std::string db_name;
        std::string user;
        std::string passwd;
        std::string host;
        std::string port;
    public:
        Database();
        ~Database();
        void connect(std::string host, std::string port, std::string db_name, std::string user, std::string passwd);
        std::unordered_map<std::string, std::string> load_env_file(const std::string& filename);
        void set_db_config(const std::unordered_map<std::string, std::string> &env_vars);
        void create_table_user();
        void create_table_credentials();
        void insert_user(const std::string &uuid,
                         const std::string &name,
                         const std::string &username,
                         const std::string &hash_passwd,
                         const std::string &email,
                         bool otp_is_enabled = false);
        void insert_credentials(const std::string &service_name,
                                const std::string &username,
                                const std::string &hash_passwd);
        void update_user(const std::string &uuid,
                         const std::string &name,
                         const std::string &username,
                         const std::string &hash_passwd,
                         const std::string &email,
                         bool otp_is_enabled);
        void update_user_password(const std::string &username, const std::string &password) override;
        void update_credentials(const std::string &service_name,
                                const std::string &username,
                                const std::string &hash_passwd);
        void delete_user(const std::string &uuid);
        void delete_credentials(const std::string &service_name, const std::string &username);
        std::string result_to_string(const pqxx::result &res);
        std::string get_user(const std::string &uuid) override;
        std::string get_hash_passwd(const std::string &username) override;
        bool get_otp_status(const std::string &username);
        std::string get_user_token_session(const std::string &username);
        pqxx::result get_credentials(const std::string &service_name, const std::string &username);
        pqxx::result get_all_credentials(const std::string &username);
};
#endif //DB_H
