#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <unordered_map>

class config
{
    private:
        static std::unordered_map<std::string, std::string> settings;
    public:
        config();
        ~config();
        static void load(const std::string& filename);
        static std::string get(const std::string& key);
        static void set(const std::string& key, const std::string& value);
};

#endif // CONFIG_H