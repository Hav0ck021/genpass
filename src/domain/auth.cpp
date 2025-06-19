#include "core/log.h"
#include "domain/auth.h"
#include "domain/crypto.h"
#include "domain/otp.h"
#include "interface/idb.h"
#include <sodium.h>
#include <iostream>
#include <memory>
#include <random>
#include <string>

const std::string BASE64_URL_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

Auth::Auth(std::shared_ptr<IDatabase> i_db) : i_db(i_db) {}

Auth::~Auth()
{
    Log::log(Log_level::INFO, "Auth destructor called.");
}

bool Auth::is_valid_token_session(const std::string &token)
{
    Log::log(Log_level::INFO, "Validating token session: " + token);
    return false;
}

bool Auth::is_active_session(Session &user_session)
{
    Log::log(Log_level::INFO, "Checking if session is active for user: " + user_session.username);
    return user_session.is_active && !is_session_expired(user_session);
}

bool Auth::is_session_expired(Session &user_session)
{
    Log::log(Log_level::INFO, "Checking if session is expired for user: " + user_session.username);
    std::time_t current_time = std::time(nullptr);
    return (current_time - user_session.last_activity) > SESSION_TIMEOUT;
}

void Auth::update_session_activity(Session &user_session)
{
    Log::log(Log_level::INFO, "Updating session activity for user: " + user_session.username);
    user_session.last_activity = std::time(nullptr);
}

bool Auth::login(const std::string &username, const std::string &password)
{
    Log::log(Log_level::INFO, "Login attempt for user: " + username);    
    if (username.empty() || password.empty())
    {
        Log::log(Log_level::ERROR, "Username or password cannot be empty.");
        return false;
    }
    if (i_db->get_user(username).empty())
    {
        Log::log(Log_level::ERROR, "User not found: " + username);
        return false;
    }
    std::string hashed_password = i_db->get_hash_passwd(username);
    if(!i_db->get_otp_status(username))
    {
        Log::log(Log_level::INFO, "OTP is not activated for user: " + username);
        return compare_passwd_decrypted_passwd(password, hashed_password, nullptr);
    }
    
    std::string otp;
    std::cout << "Enter OTP: ";
    std::cin >> otp;

    if(otp.empty())
    {
        Log::log(Log_level::ERROR, "OTP cannot be empty.");
        return false;
    }
    if(compare_passwd_decrypted_passwd(password,
                                       hashed_password,
                                       reinterpret_cast<const unsigned char*>(otp.c_str())) != true)
    {
        Log::log(Log_level::ERROR, "Password or OTP is incorrect for user: " + username);
        return false;
    }
    Log::log(Log_level::INFO, "User " + username + " logged in successfully.");
    create_session(username);
    return true;
}

bool Auth::is_logged_in(const std::string &token)
{
    Log::log(Log_level::INFO, "Checking if user is logged in with token: " + token);
    auto it = sessions.find(token);
    return it != sessions.end() && it->second.is_active;
}

void Auth::logout(const std::string &token)
{
    auto it = sessions.find(token);
    if(it == sessions.end())
    {
        Log::log(Log_level::ERROR, "Session not found for token: " + token);
        return;
    }
    delete_session(token);
    Log::log(Log_level::INFO, "User logged out successfully.");
}
    
bool Auth::compare_passwd_decrypted_passwd(const std::string &password,
                                            const std::string &hashed_password,
                                            const unsigned char *otp)
{
    return password != Crypto::decrypt_password(const_cast<char*>(password.c_str()),
                                                const_cast<char*>(hashed_password.c_str()), otp);
}

void Auth::create_session(const std::string &username)
{
    if(username.empty())
    {
        Log::log(Log_level::ERROR, "Username cannot be empty.");
        return;
    }
    if(i_db->get_user(username).empty())
    {
        Log::log(Log_level::ERROR, "User not found: " + username);
        return;
    }
    auto it = sessions.find(username);
    if(it != sessions.end() && it->second.is_active)
    {
        Log::log(Log_level::WARNING, "Session already exists for user: " + username);
        return;
    }

    std::cout << "Creating session for user: " << username << '\n';
    std::string uuid_token = generate_session_token(32);

    User_Session session;
    session.username = username;
    session.token = uuid_token;
    session.created_at = std::time(nullptr);
    session.last_activity = session.created_at;
    session.is_active = true;
    sessions[uuid_token] = session;
    
    Log::log(Log_level::INFO, "Session created for user: " + username + " with token: " + session.token);
}

void Auth::delete_session(const std::string &token)
{
    auto it = sessions.find(token);
    if(it == sessions.end())
    {
        Log::log(Log_level::WARNING, "Session not found.");
        return;
    }
    std::cout << "Deleting session for user: " << sessions.at(token).username << '\n';
    sessions.erase(it);
}

std::string Auth::generate_session_token(size_t lenght)
{
    if(lenght == 0)
    {
        Log::log(Log_level::ERROR, "Token length must be greater than 0.");
        return "";
    }
    
    std::string new_token;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, BASE64_URL_ALPHABET.size() - 1);

    while(lenght > 0)
    {
        new_token += BASE64_URL_ALPHABET[dis(gen)];
        lenght--;
    }
    return new_token;
}

User_Session* Auth::get_session(const std::string &token)
{
    auto it = sessions.find(token);
    if(it != sessions.end())
    {
        return &it->second;
    }
    Log::log(Log_level::WARNING, "Session not found for token: " + token);
    return nullptr;
}

bool Auth::verify_session(User_Session &user_session)
{
    if(!is_valid_token_session(user_session.token))
    {
        Log::log(Log_level::ERROR, "Invalid session token for user: " + user_session.username);
        return false;
    }
    if(!is_active_session(user_session))
    {
        Log::log(Log_level::ERROR, "Session is not active or has expired for user: " + user_session.username);
        return false;
    }
    return true;
}