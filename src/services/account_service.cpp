#include "core/log.h"
#include "services/account_service.h"


bool Account_Service::create_account(const std::string& email, const std::string& username, const std::string& password)
{
    Log::log(Log_level::INFO, "Starting user registration process for: " + username);

    if(!validate_email(email))
    {
        Log::log(Log_level::ERROR, "Invalid email format: " + email);
        return false;
    }
    if(!validate_username(username))
    {
        Log::log(Log_level::ERROR, "Invalid username format: " + username);
        return false;
    }
    if(!validate_password(password))
    {
        Log::log(Log_level::ERROR, "Invalid password format for user: " + username);
        return false;
    }
    if(is_email_taken(email))
    {
        Log::log(Log_level::ERROR, "Email already taken: " + email);
        return false;
    }
    if(is_username_taken(username))
    {
        Log::log(Log_level::ERROR, "Username already taken: " + username);
        return false;
    }
    if(!save_user_to_db(email, username, password))
    {
        Log::log(Log_level::ERROR, "Failed to save user to database for: " + username);
        return false;
    }

    Log::log(Log_level::INFO, "User registered successfully: " + username);
    return true;
}

bool Account_Service::recover_account(const std::string& username, const std::string &email)
{
    Log::log(Log_level::INFO, "Starting account recovery for user: " + username);

    // Verifica se o usuário existe
    if (!is_username_taken(username)) {
        Log::log(Log_level::ERROR, "Username not found: " + username);
        return false;
    }

    // Verifica se o email existe
    if (!is_email_taken(email)) {
        Log::log(Log_level::ERROR, "Email not found: " + email);
        return false;
    }

    // Verifica se o email está relacionado ao usuário
    // Supondo que i_app->db().get_user_by_username retorna um objeto User com campo email
    // auto user = i_app->db().get_user_by_username(username);
    // if (user.email != email) {
        // Log::log(Log_level::ERROR, "Email does not match username: " + username);
        // return false;
    // }

    // Altera a senha do usuário
    // Supondo que i_app->db().update_user_password atualiza a senha do usuário
    // if (!i_app->db().update_user_password(username, new_password)) {
    //     Log::log(Log_level::ERROR, "Failed to update password for user: " + username);
    //     return false;
    // }
    Log::log(Log_level::INFO, "Account recovery initiated for user: " + username);

    return true;
}

bool Account_Service::access_vault(const std::string& username, const std::string& password)
{
    
}

bool Account_Service::is_email_taken(const std::string& email)
{
    Log::log(Log_level::INFO, "Checking if email is taken: " + email);
    // if(!i_app->db().get_user_by_email(email).empty())
    // {
    //     return true;
    // }
    return false;
}

bool Account_Service::is_username_taken(const std::string& username)
{
    Log::log(Log_level::INFO, "Checking if username is taken: " + username);
    // if(!i_app->db().get_user_by_username(username).empty())
    // {
    //     return true;
    // }
    return false;
}

bool Account_Service::save_user_to_db(const std::string& email, const std::string& username, const std::string& password)
{
    Log::log(Log_level::INFO, "Saving user to database: " + username);
    // if(!i_app->db().save_user(email, username, password))
    // {
    //     Log::log(Log_level::ERROR, "Failed to save user to database.");
    //     return false;
    // }
    return true;
}


// void Account_Service::change_email(const std::string& username, const std::string& new_email) = 0;
// {
//    This function is a placeholder for future implementation.
//    Log::log(Log_level::INFO, "Changing email for user: " + username + " to " + new_email);
// }

// void Account_Service::change_username(const std::string& username, const std::string& new_username) = 0;
// {
//    This function is a placeholder for future implementation.
//    Log::log(Log_level::INFO, "Changing username for : " + username + " to " + new_username);
// }

void Account_Service::change_password(const std::string& username, const std::string& new_password)
{
    if(!validate_username(username))
    {
        Log::log(Log_level::ERROR, "Invalid username format: " + username);
        return;
    }
    if(!validate_password(new_password))
    {
        Log::log(Log_level::ERROR, "Invalid password format for user: " + username);
        return;
    }
    i_db->update_user_password(username, new_password);
    Log::log(Log_level::INFO, "Password changed successfully for user: " + username);
}

// void Account_Service::send_recovery_email(const std::string& username, const std::string& email)
// {
//     // This function is a placeholder for future implementation.
//     Log::log(Log_level::INFO, "Sending recovery email to: " + email + " for user: " + username);
//     // In a real application, you would implement the logic to send an email here.
// }