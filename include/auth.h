#ifndef AUTH_H
#define AUTH_H
#include "../include/log.h"
#include "../include/user.h"
#include "../include/app.h"
#include <iostream>
#include <string>

typedef struct Session
{
    std::string username;
    std::string token;
    std::time_t created_at;
    std::time_t last_activity;
    bool is_active;
} User_Session;

class Auth
{
    private:
        static Logger auth_logger;
        User_Session current_session;
        static bool is_valid_token_session(const std::string &token);
        static bool is_active_session(Session &user_session);
        static bool is_session_expired(Session &user_session);
        static void update_session_activity(Session &user_session);
    public:
        static constexpr std::time_t SESSION_TIMEOUT = 3600;
        Auth();
        ~Auth();
    
        static bool login(const std::string &username, const std::string &password);
        void logout();
        static bool compare_passwd_decrypted_passwd(const std::string &password, const std::string &hashed_password, const unsigned char *otp);
        
        static void create_session(const std::string &username);
        static void delete_session(const std::string &username);
        std::string generate_session_token(size_t length);
};
#endif // AUTH_H