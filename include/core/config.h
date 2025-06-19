#ifndef CONFIG_H
#define CONFIG_H
#include "core/log.h"
#include <unordered_map>
#include <string>

typedef struct Config
{
    std::unordered_map<std::string, std::string> settings;
    std::string get(const std::string& key);
    void set(const std::string& key, const std::string& value);
    void load(const std::string& filename);
    void save(const std::string& filename, const std::string& key, const std::string& value);
} Config_Entry;

// int max_login_attempts = 3;
// int get_max_login_attempts();
// void set_max_login_attempts(int attempts);

#endif // CONFIG_H