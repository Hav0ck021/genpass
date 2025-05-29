#include "../include/vault.h"
#include "../include/log.h"
#include <iostream>

Logger vault_logger;

Vault::Vault()
{
    vault_logger.log(Log_level::INFO, "Vault credentials has been created.");
}

Vault::~Vault()
{
    vault_logger.log(Log_level::INFO, "Vault credentials has been removed.");
}

void Vault::create_credentials(std::string sn)
{
    if(sn.empty())
    {
        vault_logger.log(Log_level::ERROR, "The service name can't be empty.");
    }
    // Continue development.
}