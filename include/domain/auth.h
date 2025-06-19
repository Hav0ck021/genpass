#ifndef AUTH_H
#define AUTH_H
#include "core/log.h"
#include "domain/crypto.h"
#include "interface/iauth.h"
#include "interface/idb.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

typedef struct Session
{
    std::string username;
    std::string token;
    std::time_t created_at;
    std::time_t last_activity;
    bool is_active;
} User_Session;

class Auth : public IAuth
{
    private:
        std::shared_ptr<IDatabase> i_db;
        std::unordered_map<std::string, User_Session> sessions;
        bool is_valid_token_session(const std::string &token);
        bool is_active_session(User_Session &user_session);
        bool is_session_expired(User_Session &user_session);
    public:
        Auth(std::shared_ptr<IDatabase> i_db);
        ~Auth();
        static constexpr std::time_t SESSION_TIMEOUT = 3600;
        static void update_session_activity(User_Session &user_session);
        bool login(const std::string &username, const std::string &password) override;
        bool is_logged_in(const std::string &token) override;
        void logout(const std::string &token) override;
        bool compare_passwd_decrypted_passwd(const std::string &password, const std::string &hashed_password, const unsigned char *otp); 
        void create_session(const std::string &username);
        void delete_session(const std::string &username);
        std::string generate_session_token(size_t length);
        User_Session* get_session(const std::string &token);
        bool verify_session(User_Session &user_session);
};
#endif // AUTH_H