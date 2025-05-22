#include <../include/auth.h>
#include <../include/app.h>
#include <../include/log.h>
#include <../include/user.h>
#include <sodium.h>
#include <iostream>
#include <string>

logger auth_logger("../logs/genpass.log");

auth::auth()
{
    auth_logger.log(log_level::INFO, "Auth constructor called.");
}

auth::~auth()
{
    auth_logger.log(log_level::INFO, "Auth destructor called.");
}

std::string auth::encrypt_password(const std::string& password)
{
    return encrypted_password;
}

std::string auth::decrypt_password(const std::string& password)
{
    return decrypted_password;
}

bool auth::create_password(const std::string& pass)
{
    return new_password;
}

std::string auth::reset_password(const std::string& pass)
{
    return new_password;
}