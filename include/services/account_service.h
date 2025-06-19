#ifndef ACCOUNT_SERVICE_H
#define ACCOUNT_SERVICE_H

#include "interface/iapp.h"
#include "interface/idb.h"
#include <memory>

class Account_Service
{
    private:
        std::shared_ptr<IApp> i_app;
        std::shared_ptr<IDatabase> i_db;

        bool validate_email(const std::string& email);
        bool validate_username(const std::string& username);
        bool validate_password(const std::string& password);
        bool is_email_taken(const std::string& email);
        bool is_username_taken(const std::string& username);
        bool save_user_to_db(const std::string& email, const std::string& username, const std::string& password);
    public:
        Account_Service(std::shared_ptr<IApp> app, std::shared_ptr<IDatabase> db) : i_app(app), i_db(db) {}
        ~Account_Service() = default;

        bool create_account(const std::string& email, const std::string& username, const std::string& password);
        bool edit_account(const std::string &username, const std::string &new_password);
        bool recover_account(const std::string &username, const std::string &email);
        bool delete_account(const std::string &username);
        bool access_vault(const std::string& username, const std::string& password);
        bool generate_password(uint8_t size);
        // void change_email(const std::string& username, const std::string& new_email);
        // void change_username(const std::string& username, const std::string& new_username);
        void change_password(const std::string& username, const std::string& new_password);
        // void send_recovery_email(const std::string& username, const std::string& email);
};

#endif // ACCOUNT_SERVICE_H