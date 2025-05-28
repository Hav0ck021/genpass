#ifndef OTP_H_
#define OTP_H_

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
    public:
        OTP();
        ~OTP();
        static bool otp_is_activated(const std::string &username);
        static std::string generate_random_base32_secret(int length = OTP_SECRET_LENGTH);
        static std::string generate_hotp(const std::string& base32_secret, 
            uint64_t counter, 
            int digits = OTP_DIGITS,
            OTP_algorithm algorithm = OTP_algorithm::SHA1);
        static bool validate_hotp(const std::string& base32_secret,
            const std::string& otp,
            uint64_t& counter,
            int window = 1,
            int digits = OTP_DIGITS,
            const std::string& secret);
        static std::string generate_totp(const std::string& base32_secret,
            int time_step = OTP_INTERVAL,
            uint64_t t0 = T0,
            int digits = OTP_DIGITS,
            OTP_algorithm algorithm = OTP_algorithm::SHA1);
        static std::string gererate_totp_from_time(const std::string& base32_secret,
            uint64_t unix_time,
            int time_step = OTP_INTERVAL,
            uint64_t t0 = T0,
            int digits = OTP_DIGITS,
            OTP_algorithm algorithm = OTP_algorithm::SHA1);
        static long get_current_time();
};

#endif // OTP_H_