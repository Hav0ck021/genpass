#ifndef CONFIG_H
#define CONFIG_H
#include "../include/log.h"
#include <string>
#include <unordered_map>

class Config
{
    private:
        static Logger config_logger;
        static std::unordered_map<std::string, std::string> settings;
    public:
        Config();
        ~Config();
        static void load(const std::string& filename);
        static std::string get(const std::string& key);
        static void set(const std::string& key, const std::string& value);
};

#endif // CONFIG_H