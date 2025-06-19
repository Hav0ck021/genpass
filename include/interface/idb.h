#ifndef IDB_H
#define IDB_H
#include <string>

class IDatabase
{
    public:
        virtual ~IDatabase() = default;

        virtual void connect(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname) = 0;
        virtual void disconnect() = 0;

        // virtual bool update_username(const std::string& old_username, const std::string& new_username) = 0;
        // virtual bool update_user_email(const std::string& username, const std::string& new_email) = 0;
        virtual void update_user_password(const std::string &username, const std::string &password) = 0;
        virtual std::string get_hash_passwd(const std::string &username) = 0;
        virtual std::string get_user(const std::string &username) = 0;
        virtual bool get_otp_status(const std::string &username) = 0;
};

#endif // IDB_H