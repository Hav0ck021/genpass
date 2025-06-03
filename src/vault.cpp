#include "../include/vault.h"
#include "../include/log.h"
#include "../include/app.h"
#include <iostream>

Logger Vault::vault_logger;

Vault::Vault()
{
    vault_logger.log(Log_level::INFO, "Vault credentials has been created.");
}

Vault::~Vault()
{
    vault_logger.log(Log_level::INFO, "Vault credentials has been removed.");
}

bool Vault::create_credentials(const std::string service_name,
                               const std::string service_username,
                               const std::string service_pass)
{
    if(service_name.empty())
    {
        vault_logger.log(Log_level::ERROR, "The service name can't be empty.");
        return false;
    }
  
    Credentials new_credential;
    uuid_generate(new_credential.genpass_service_uuid);
    new_credential.service_name = service_name;

    std::cout << "Enter service username: ";
    std::cin >> new_credential.service_username;
    new_credential.service_pass = App::get_password_input("Enter service password: ");

    user_credential.push_back(new_credential);
    vault_logger.log(Log_level::INFO, "Credentials for service " + service_name + " have been created.");
    return true;
}

void Vault::edit_credentials(std::string service_name)
{

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