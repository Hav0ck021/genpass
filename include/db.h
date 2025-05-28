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
        std::string hash_passwd;
        std::string host;
        std::string port;
    public:
        Database(const char *filename);
        ~Database();
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
        void update_credentials(const std::string &service_name,
                                const std::string &username,
                                const std::string &hash_passwd);
        void delete_user(const std::string &uuid);
        void delete_credentials(const std::string &service_name,
                                const std::string &username);
        std::string result_to_string(const pqxx::result &res);
        std::string get_user(const std::string &uuid);
        std::string get_hash_passwd(const std::string &username);
        static bool get_otp_status(const std::string &username);
        pqxx::result get_credentials(const std::string &service_name,
                                     const std::string &username);
        pqxx::result get_all_credentials(const std::string &username);
        
};
#endif //DB_H
