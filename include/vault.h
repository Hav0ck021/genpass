#include <iostream>
#include <uuid/uuid.h>

class Vault
{
    private:
    public:
        Vault();
            uuid_t service_uuid;
            std::string service_name;
            std::string service_username;
            std::string service_pass;
        ~Vault();
        void list_all_credentials();
        void create_credentials(std::string service_name);
        void edit_credentials(std::string service_name);
        void delete_credentials(std::string service_name);
        void search_credentials(std::string service_name);
};