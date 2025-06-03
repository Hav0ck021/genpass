#ifndef OTP_H_
#define OTP_H_
#include "../include/log.h"
#include <iostream>
#include <vector>
#include <string>
#define T0 0
#define OTP_DIGITS 6
#define OTP_INTERVAL 30
#define OTP_SECRET_LENGTH 20

enum class OTP_algorithm
{
    SHA1,
    SHA256,
    SHA512
};

class OTP
{
    private:
        static Logger otp_logger;
    public:
        OTP();
        ~OTP();
        static bool otp_is_activated(const std::string &username);
        static std::string generate_random_base32_secret(int length = OTP_SECRET_LENGTH);
        static std::string gererate_totp_from_time(const std::string& base32_secret,
            uint64_t unix_time,
            int time_step = OTP_INTERVAL,
            uint64_t t0 = T0,
            int digits = OTP_DIGITS,
            OTP_algorithm algorithm = OTP_algorithm::SHA1);
        static bool validate_totp(const std::string& base32_secret,
            const std::string& otp,
            uint64_t& counter,
            int window = 1,
            int digits = OTP_DIGITS,
            const std::string& secret = "");
        static uint64_t get_current_time();
        static std::string derive_key_from_totp(const std::string& totp,const std::string& shared_secret);
        static std::vector<unsigned char> generate_random_bytes(uint32_t num_bytes);
        static std::string bytes_to_base32(std::vector<unsigned char> bytes);
};
#endif // OTP_H_