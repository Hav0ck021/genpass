#include "../include/otp.h"
#include "../include/log.h"

Logger otp_logger("../logs/genpass.log");

OTP::OTP()
{
    otp_logger.log(Log_level::INFO, "OTP constructor called.");
}

OTP::~OTP()
{
    otp_logger.log(Log_level::INFO, "OTP destructor called.");
}

std::string generate_random_base32_secret(int length = OTP_SECRET_LENGTH)
{
    // Development of this function is in progress.
}

std::string OTP::generate_hotp(const std::string& base32_secret, 
    uint64_t counter, 
    int digits,
    OTP_algorithm algorithm)
{
    // Development of this function is in progress.
}

bool OTP::validate_hotp(const std::string& base32_secret,
    const std::string& otp,
    uint64_t& counter,
    int window,
    int digits,
    const std::string& secret)
{
    // Development of this function is in progress.
}

std::string OTP::generate_totp(const std::string& base32_secret,
    int time_step,
    uint64_t t0,
    int digits,
    OTP_algorithm algorithm)
{
    // Development of this function is in progress.
}

std::string OTP::gererate_totp_from_time(const std::string& base32_secret,
    uint64_t unix_time,
    int time_step,
    uint64_t t0,
    int digits,
    OTP_algorithm algorithm)
{
    // Development of this function is in progress.
}

long OTP::get_current_time()
{
    // Development of this function is in progress.
}