#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "core/log.h"
#include <string>
#include <fstream>

class LogTest : public ::testing::Test
{
    protected:
        void SetUp() override
        {
            std::remove(Log::LOG_FILE_PATH.c_str());
            Log::create_log_file();
            ASSERT_TRUE(Log::log_file.is_open());
        }

        void TearDown() override
        {
            Log::log_file.close();
        }
};

TEST_F(LogTest, CreateLogFile_CreatesLogDirectoryAndFile)
{
    ASSERT_TRUE(Log::log_file.is_open());
    ASSERT_EQ(Log::log_file.is_open(), true);
}

TEST_F(LogTest, LogMessage_WritesToLogFile)
{
    Log::log(Log_level::INFO, "This is a test log message.");
    ASSERT_TRUE(Log::log_file.is_open());

    std::string log_file_path = "logs/genpass.log";
    Log::log_file.close();
    std::ifstream infile(log_file_path);
    ASSERT_TRUE(infile.is_open());

    std::string line;
    std::getline(infile, line);
    ASSERT_FALSE(line.empty());
    ASSERT_NE(line.find("This is a test log message."), std::string::npos);

    infile.close();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    Log::create_log_file();
    return RUN_ALL_TESTS();
}