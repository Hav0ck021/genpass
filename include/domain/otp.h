#ifndef OTP_H_
#define OTP_H_
#include "core/log.h"
#include "interface/idb.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#define OTP_DIGITS 6
#define OTP_INTERVAL 30
#define OTP_SECRET_LENGTH 20

class OTP
{
    private:
        std::shared_ptr<IDatabase> i_db;
    public:
        OTP(std::shared_ptr<IDatabase> db);
        ~OTP();
        bool totp_is_activated(const std::string &username);
        std::string generate_random_base32_secret(int length = OTP_SECRET_LENGTH);
        std::string gererate_totp_from_time(const std::string& base32_secret,
            uint64_t unix_time,
            int time_step = OTP_INTERVAL,
            int digits = OTP_DIGITS);
        bool validate_totp(const std::string& base32_secret,
            const std::string& otp,
            uint64_t& counter,
            int window = 1,
            int digits = OTP_DIGITS,
            const std::string& secret = "");
        uint64_t get_current_time();
        std::string derive_key_from_totp(const std::string& totp,const std::string& shared_secret);
        std::vector<unsigned char> generate_random_bytes(uint32_t num_bytes);
        std::string bytes_to_base32(std::vector<unsigned char> bytes);
        std::vector<unsigned char> base32_to_bytes(const std::string& base32);
};
#endif // OTP_H_