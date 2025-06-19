#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/log.h"
#include "domain/otp.h"
#include "interface/idb.h"
#include <memory>
#include <string>

/*
    Mocks to Database 
    Scope: idb.h
           otp.h/.cpp
*/
class MockDatabase : public IDatabase
{
    public:
        MOCK_METHOD(void, connect, (const std::string&, const std::string&, const std::string&, const std::string&), (override));
        MOCK_METHOD(void, disconnect, (), (override));
        MOCK_METHOD(void, update_user_password, (const std::string&, const std::string&), (override));
        MOCK_METHOD(bool, get_otp_status, (const std::string&), (override));
};

class OTPTest : public ::testing::Test 
{
    protected:
        std::shared_ptr<MockDatabase> mock_db;
        std::unique_ptr<OTP> otp;

        void SetUp() override
        {
            mock_db = std::make_shared<MockDatabase>();
            otp = std::make_unique<OTP>(mock_db);
        }
};

/*
    Mock testing for: OTP::generate_random_base32_secret()
    Result: returns valid length
 */
TEST_F(OTPTest, GenerateRandomBase32Secret_ReturnsValidLength)
{
    std::string secret = otp->generate_random_base32_secret(20);
    ASSERT_FALSE(secret.empty());
    ASSERT_GE(secret.length(), 20);
}

/*
    Mock testing for: OTP::totp_is_activated()
    Result: return true
 */
TEST_F(OTPTest, TotpIsActivated_ReturnsTrueIfActive)
{
    EXPECT_CALL(*mock_db, get_otp_status("testuser"))
        .WillOnce(::testing::Return(true));
    ASSERT_TRUE(otp->totp_is_activated("testuser"));
}

/*
    Mock testing for: OTP::totp_is_activated
    Result: return false
 */
TEST_F(OTPTest, TotpIsActivated_ReturnsFalseIfNotActive)
{
    EXPECT_CALL(*mock_db, get_otp_status("testuser"))
        .WillOnce(::testing::Return(false));
    ASSERT_FALSE(otp->totp_is_activated("testuser"));
}

/*
    Mock testing for: OTP::gererate_totp_from_time + OTP::validate_totp
    Result: returns valid OTP
 */
TEST_F(OTPTest, GenerateAndValidateTotp)
{
    std::string secret = otp->generate_random_base32_secret(20);
    uint64_t now = otp->get_current_time();
    std::string generated = otp->gererate_totp_from_time(secret, now, 30, 6);
    ASSERT_EQ(generated.length(), 6);

    uint64_t counter = 0;
    ASSERT_TRUE(otp->validate_totp(secret, generated, counter, 1, 6, secret));
}

/*
    Mock testing for: OTP::generate_random_base32_secret with invalid length
    Result: returns empty string
 */
TEST_F(OTPTest, GenerateRandomBase32Secret_InvalidLength_ReturnsEmpty)
{
    std::string secret = otp->generate_random_base32_secret(0);
    ASSERT_TRUE(secret.empty());
}

/*
    Mock testing for: OTP::generate_random_bytes with length equal to zero
    Result: returns empty vector
*/
TEST_F(OTPTest, GenerateRandomBytes_ZeroLength_ReturnsEmpty)
{
    std::vector<unsigned char> bytes = otp->generate_random_bytes(0);
    ASSERT_TRUE(bytes.empty());
}

/*
    Mock testing for: OTP::generate_random_bytes return vector not null
    Result: returns vector with correct size
*/
TEST_F(OTPTest, GenerateRandomBytes_ValidLength_ReturnsCorrectSize)
{
    std::vector<unsigned char> bytes = otp->generate_random_bytes(16);
    ASSERT_FALSE(bytes.empty());
    ASSERT_EQ(bytes.size(), 16);
}

/*
    Mock testing for: OTP::bytes_to_base32 with vector null
    Result: returns empty string
*/
TEST_F(OTPTest, BytesToBase32_EmptyInput_ReturnsEmpty)
{
    std::vector<unsigned char> input;
    std::string output = otp->bytes_to_base32(input);
    ASSERT_TRUE(output.empty());
}

/*
    Mock testing for: OTP::base32_to_bytes with invalid input
    Result: returns empty vector
*/
TEST_F(OTPTest, Base32ToBytes_InvalidCharacter_ReturnsEmpty)
{
    std::string invalid_base32 = "InvalidBase32!";
    std::vector<unsigned char> output = otp->base32_to_bytes(invalid_base32);
    ASSERT_TRUE(output.empty());
}

/*
    Mock testing for: OTP::base32_to_bytes with valid input
    Result: returns vector with correct size
*/
TEST_F(OTPTest, Base32ToBytes_ValidBase32_ReturnsCorrectBytes)
{
    std::string valid_base32 = "JBSWY3DP";
    std::vector<unsigned char> output = otp->base32_to_bytes(valid_base32);
    ASSERT_FALSE(output.empty());
    ASSERT_EQ(output.size(), 5);  // JBSWY3DP decodes to 5 bytes
}

/*
    Mock testing for: OTP::gererate_totp_from_time with invalid base32
    Result: returns empty string
*/
TEST_F(OTPTest, GenerateTotpFromTime_InvalidBase32_ReturnsEmpty)
{
    std::string invalid_base32 = "InvalidBase32!";
    uint64_t now = otp->get_current_time();
    std::string totp = otp->gererate_totp_from_time(invalid_base32, now, 30, 6);
    ASSERT_TRUE(totp.empty());
}

/*
    Mock testing for: OTP::validate_totp with invalid OTP
    Result: returns false
*/
TEST_F(OTPTest, ValidateTotp_InvalidOtp_ReturnsFalse)
{
    std::string secret = otp->generate_random_base32_secret(20);
    uint64_t now = otp->get_current_time();
    std::string generated = otp->gererate_totp_from_time(secret, now, 30, 6);
    
    uint64_t counter = 0;
    ASSERT_FALSE(otp->validate_totp(secret, "123456", counter, 1, 6, secret));
}

/*
    Mock testing for: OTP::validate_totp with empty secret
    Result: returns false
*/
TEST_F(OTPTest, ValidateTotp_EmptySecret_ReturnsFalse)
{
    std::string empty_secret = "";
    std::string otp_code = "123456";
    uint64_t counter = 0;
    ASSERT_FALSE(otp->validate_totp(empty_secret, otp_code, counter, 1, 6, empty_secret));
}

/*
    Mock testing for: OTP::derive_key_from_totp not implemented
    Result: returns empty string
*/
TEST_F(OTPTest, DeriveKeyFromTotp_NotImplemented_ReturnsEmpty)
{
    std::string totp = "123456";
    std::string shared_secret = "shared_secret";
    std::string derived_key = otp->derive_key_from_totp(totp, shared_secret);
    ASSERT_TRUE(derived_key.empty());
}

/*
    Mock testing for: OTP::get_current_time returns reasonable UNIX time
    Result: returns a value greater than 0 and less than 4102444800 (Year 2100)
*/
TEST_F(OTPTest, GetCurrentTime_ReturnsReasonableUnixTime)
{
    uint64_t current_time = otp->get_current_time();
    ASSERT_GT(current_time, 0);
    ASSERT_LT(current_time, 4102444800);  // Year 2100
}

int main(int argc, char **argv)
{
    Log::create_log_file(); 
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
