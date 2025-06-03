#include "../include/otp.h"
#include "../include/log.h"
#include "../include/db.h"
#include <openssl/hmac.h>
#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <string>
#include <ctime>

const std::string BASE32_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
const int k = 0x1F;

Logger OTP::otp_logger;

OTP::OTP()
{
    otp_logger.log(Log_level::INFO, "OTP constructor called.");
}

OTP::~OTP()
{
    otp_logger.log(Log_level::INFO, "OTP destructor called.");
}

bool OTP::otp_is_activated(const std::string &username)
{
    otp_logger.log(Log_level::INFO, "OTP activation check called.");
    if(!Database::get_otp_status(username))
    {
        otp_logger.log(Log_level::WARNING, "OTP is not activated for the current user.");
        return false;
    }
    return true;
}

std::string OTP::generate_random_base32_secret(int length)
{
    otp_logger.log(Log_level::INFO, "Generating random Base32 secret.");
    if(length <= 0)
    {
        otp_logger.log(Log_level::ERROR, "Length must be greater than 0.");
        return "";
    }
    std::vector<unsigned char> random_bytes = OTP::generate_random_bytes(length);
    if(random_bytes.empty())
    {
        otp_logger.log(Log_level::ERROR, "Failed to generate random bytes.");
        return "";
    }
    std::string base32_secret = OTP::bytes_to_base32(random_bytes);
    if(base32_secret.empty())
    {
        otp_logger.log(Log_level::ERROR, "Failed to convert bytes to Base32.");
        return "";
    }
    otp_logger.log(Log_level::INFO, "Random Base32 secret generated successfully.");
    return base32_secret;
}

std::string OTP::gererate_totp_from_time(const std::string& base32_secret,
    uint64_t unix_time,
    int time_step,
    uint64_t t0,
    int digits,
    OTP_algorithm algorithm)
{
    return "";
}

bool OTP::validate_totp(const std::string& base32_secret,
    const std::string& otp,
    uint64_t& counter,
    int window,
    int digits,
    const std::string& secret)
{
    return true;
}

uint64_t OTP::get_current_time()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

std::string OTP::derive_key_from_totp(const std::string& totp, const std::string& shared_secret)
{
    return "";
}

std::vector<unsigned char> OTP::generate_random_bytes(uint32_t num_bytes)
{
    std::vector<unsigned char> random_bytes;
    if(num_bytes == 0)
    {
        otp_logger.log(Log_level::ERROR, "Length must be greater than 0.");
        return random_bytes;
    }
    random_bytes.resize(num_bytes);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<unsigned char> distribution(0, 255);
    
    for(uint32_t i = 0; i < num_bytes; ++i)
    {
        random_bytes[num_bytes - 1] = distribution(generator);
    }

    return random_bytes;
}

std::string OTP::bytes_to_base32(std::vector<unsigned char> bytes)
{
    if(bytes.empty())
    {
        otp_logger.log(Log_level::ERROR, "Input bytes vector is empty.");
        return "";
    }
    
    std::string base32_string;
    unsigned long long value = 0;
    int bits = 5;
    int buffer = 0;
    int bits_in_buffer = 0;
    
    for(unsigned char byte : bytes)
    {
        buffer = (buffer << 8) | byte;
        bits_in_buffer += 8;

        while(bits_in_buffer >= bits)
        {
            int index = (buffer >> (bits_in_buffer - bits)) & k;
            base32_string += BASE32_CHARSET[index];
            bits_in_buffer -= bits;
        }
    }
    if(bits_in_buffer > 0)
    {
        int index = (buffer << (bits - bits_in_buffer)) & k;
        base32_string += BASE32_CHARSET[index];
    }
    while(base32_string.length() % 8 != 0)
    {
        base32_string += '=';
    }
    return base32_string;
}


// int main() {
//     OTP otp;

//     // Test generate_random_bytes
//     auto random_bytes = otp.generate_random_bytes(10);
//     std::cout << "Random bytes (10): ";
//     for (auto b : random_bytes) std::cout << std::hex << (int)b << " ";
//     std::cout << std::dec << std::endl;
//     assert(random_bytes.size() == 10);

//     // Test bytes_to_base32
//     std::string base32 = otp.bytes_to_base32(random_bytes);
//     std::cout << "Base32: " << base32 << std::endl;
//     assert(!base32.empty());

//     // Test generate_random_base32_secret
//     std::string secret = otp.generate_random_base32_secret();
//     std::cout << "Random Base32 Secret: " << secret << std::endl;
//     assert(!secret.empty());

//     // Test get_current_time
//     uint64_t now = otp.get_current_time();
//     std::cout << "Current time: " << now << std::endl;
//     assert(now > 0);

//     // Test otp_is_activated (assuming Database::get_otp_status returns false for "testuser")
//     bool activated = otp.otp_is_activated("testuser");
//     std::cout << "OTP activated for 'testuser': " << activated << std::endl;

//     // The following functions are not implemented, so just call them to check compilation
//     std::string totp = otp.gererate_totp_from_time(secret, now, 30, 0, 6, OTP_algorithm::SHA1);
//     std::cout << "Generated TOTP: " << totp << std::endl;

//     uint64_t counter = 0;
//     bool valid = otp.validate_totp(secret, "123456", counter, 1, 6, secret);
//     std::cout << "Validate TOTP: " << valid << std::endl;

//     std::string derived = otp.derive_key_from_totp("123456", secret);
//     std::cout << "Derived key: " << derived << std::endl;

//     std::cout << "All tests ran (some functions are stubs)." << std::endl;
//     return 0;
// }


// int main() {
//     uint64_t timestamp = OTP::get_current_time();
//     std::cout << "Unix Timestamp: " << timestamp << std::endl;
//     return 0;
// }