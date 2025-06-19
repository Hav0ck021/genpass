#include "core/log.h"
#include "domain/otp.h"
#include "interface/idb.h"
#include <openssl/hmac.h>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

const std::string BASE32_CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

const int unit_sep = 0x1F;

OTP::OTP(std::shared_ptr<IDatabase> db) : i_db(db) {}

OTP::~OTP()
{
    Log::log(Log_level::INFO, "OTP destructor called.");
}

bool OTP::totp_is_activated(const std::string &username)
{
    Log::log(Log_level::INFO, "OTP activation check called.");
    if(!i_db->get_otp_status(username))
    {
        Log::log(Log_level::WARNING, "OTP is not activated for the current user.");
        return false;
    }
    return true;
}

std::string OTP::generate_random_base32_secret(int length)
{
    Log::log(Log_level::INFO, "Generating random Base32 secret.");
    if(length <= 0)
    {
        Log::log(Log_level::ERROR, "Length must be greater than 0.");
        return "";
    }
    std::vector<unsigned char> random_bytes = OTP::generate_random_bytes(length);
    if(random_bytes.empty())
    {
        Log::log(Log_level::ERROR, "Failed to generate random bytes.");
        return "";
    }
    std::string base32_secret = OTP::bytes_to_base32(random_bytes);
    if(base32_secret.empty())
    {
        Log::log(Log_level::ERROR, "Failed to convert bytes to Base32.");
        return "";
    }
    Log::log(Log_level::INFO, "Random Base32 secret generated successfully.");
    return base32_secret;
}

std::string OTP::gererate_totp_from_time(const std::string& base32_secret,
    uint64_t unix_time,
    int time_step,
    int digits)
{
    if (unix_time == 0)
    {
        unix_time = get_current_time();
    }

    uint64_t counter = (unix_time) / time_step;
    auto key = base32_to_bytes(base32_secret);

    if (key.empty())
    {
        Log::log(Log_level::ERROR, "Base32 secret is empty or invalid.");
        return "";
    }
    
    unsigned char counter_bytes[8];
    for(int i = 7; i >= 0; --i)
    {
        counter_bytes[i] = counter & 0xFF;
        counter >>= 8;
    }

    unsigned char hmac_result[EVP_MAX_MD_SIZE];
    unsigned int result_len = 0;

    HMAC(EVP_sha512(),
         key.data(),
         key.size(),
         counter_bytes,
         8,
         hmac_result,
         &result_len);

    int offset = hmac_result[result_len - 1] & 0x0F;
    uint32_t binary_code = (hmac_result[offset] & 0x7F) << 24 |
                           (hmac_result[offset + 1] & 0xFF) << 16 |
                           (hmac_result[offset + 2] & 0xFF) << 8 |
                           (hmac_result[offset + 3] & 0xFF);

    uint32_t otp_int = binary_code % static_cast<uint32_t>(std::pow(10, digits));
    std::ostringstream otp_stream;
    otp_stream << std::setw(digits) << std::setfill('0') << otp_int;

    return otp_stream.str();
}

bool OTP::validate_totp(const std::string& base32_secret,
    const std::string& otp,
    uint64_t& counter,
    int window,
    int digits,
    const std::string& secret)
{
    if(otp.empty() || base32_secret.empty())
    {
        Log::log(Log_level::ERROR, "OTP or secret is empty.");
        return false;
    }

    uint64_t current_time = get_current_time();
    uint64_t time_step = 30;

    for(int i = -window; i <= window; ++i)
    {
        uint64_t test_time = current_time + (i * time_step);
        std::string generated_otp = gererate_totp_from_time(base32_secret, test_time, time_step, digits);
        if(generated_otp == otp)
        {
            counter = (test_time / time_step);
            return true;
        }
    }

    Log::log(Log_level::WARNING, "OTP validation failed.");
    return false;
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
        Log::log(Log_level::ERROR, "Length must be greater than 0.");
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
        Log::log(Log_level::ERROR, "Input bytes vector is empty.");
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
            int index = (buffer >> (bits_in_buffer - bits)) & unit_sep;
            base32_string += BASE32_CHARSET[index];
            bits_in_buffer -= bits;
        }
    }
    if(bits_in_buffer > 0)
    {
        int index = (buffer << (bits - bits_in_buffer)) & unit_sep;
        base32_string += BASE32_CHARSET[index];
    }
    while(base32_string.length() % 8 != 0)
    {
        base32_string += '=';
    }
    return base32_string;
}

std::vector<unsigned char> OTP::base32_to_bytes(const std::string& base32) {
    std::string b_32 = base32;
    b_32.erase(std::remove(b_32.begin(), b_32.end(), '='), b_32.end());

    std::vector<unsigned char> bytes;
    int buffer = 0, bits_left = 0;
    for(char c : b_32)
    {
        auto pos = BASE32_CHARSET.find(c);
        if(pos == std::string::npos)
        {
            break;
        }
        buffer = (buffer << 5) | pos;
        bits_left += 5;
        if(bits_left >= 8)
        {
            bytes.push_back((buffer >> (bits_left - 8)) & 0xFF);
            bits_left -= 8;
        }
    }
    return bytes;
}