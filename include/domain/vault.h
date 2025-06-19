#ifndef VAULT_H
#define VAULT_H
#include "core/log.h"
#include <uuid/uuid.h>
#include <iostream>
#include <vector>

typedef struct Credentials
{
    uuid_t genpass_service_uuid;
    std::string service_name;
    std::string service_username;
    std::string service_pass;
} User_Credentials;

class Vault
{
    private:
        std::vector<User_Credentials> user_credential;
    public:
        Vault();
        ~Vault();
        bool create_credentials(const std::string service_name,
                                const std::string service_username,
                                const std::string service_pass);
        void edit_credentials(std::string service_name);
        void list_credentials(std::string service_name);
        void delete_credentials(std::string service_name);
        void list_all_credentials();
        void search_credentials(std::string service_name);
};
#endif // VAULT_H