#include "core/app.h"
#include "core/log.h"
#include "domain/user.h"
#include "domain/vault.h"
#include "repository/db.h"
#include <uuid/uuid.h>
#include <iostream>

Vault::Vault(){}

Vault::~Vault()
{
    Log::log(Log_level::INFO, "Vault credentials has been removed.");
}

bool Vault::create_credentials(const std::string service_name,
                               const std::string service_username,
                               const std::string service_pass)
{
    if(service_name.empty())
    {
        Log::log(Log_level::ERROR, "The service name can't be empty.");
        return false;
    }
  
    Credentials new_credential;
    uuid_generate(new_credential.genpass_service_uuid);
    new_credential.service_name = service_name;

    std::cout << "Enter service username: ";
    std::cin >> new_credential.service_username;
    new_credential.service_pass = app.get_password_input();

    user_credential.push_back(new_credential);
    Log::log(Log_level::INFO, "Credentials for service " + service_name + " have been created.");
    return true;
}

void Vault::edit_credentials(std::string service_name)
{
    if(service_name.empty())
    {
        Log::log(Log_level::ERROR, "The service name can't be empty.");
    }
    // if(db.get_credentials(service_name, user.get_username()))
    // {
    //     Log::log(Log_level::ERROR, "No credentials found for the service: " + service_name);
    //     return;
    // }
}

void Vault::list_credentials(std::string service_name)
{
    
}

void Vault::delete_credentials(std::string service_name)
{
    
}

void Vault::list_all_credentials()
{
    
}

void Vault::search_credentials(std::string service_name)
{
    
}