#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "core/log.h"
#include "domain/auth.h"

/*
    Mocks to Auth
    Scope: iauth.h
           auth.h/.cpp
*/
class MockAuth : public IAuth
{
    public:
        MOCK_METHOD(bool, login, (const std::string&, const std::string&), (override));
        MOCK_METHOD(void, logout, (const std::string&), (override));
        MOCK_METHOD(bool, is_logged_in, (const std::string&), (override));
};

class AuthTest : public ::testing::Test 
{
    protected:
        std::shared_ptr<MockAuth> mock_auth;

        void SetUp() override
        {
            mock_auth = std::make_shared<MockAuth>();
        }
};

/*
    Test sessions: Auth::login()
*/

/*
    Mock testing for: Auth::login
    Result: returns false if username is empty
*/
TEST_F(AuthTest, Login_FailsIfUsernameIsEmpty)
{
    EXPECT_CALL(*mock_auth, login("", "password"))
        .WillOnce(::testing::Return(false));
}

/*
    Mock testing for: Auth::login
    Result: returns false if password is empty
*/
TEST_F(AuthTest, Login_FailsIfPasswordIsEmpty)
{

}

/*
    Mock testing for: Auth::login
    Result: returns false if user is not found
*/
TEST_F(AuthTest, Login_FailsIfUserNotFound)
{

}

/*
    Mock testing for: Auth::login
    Result: returns true if password is correct and OTP is disabled
*/
TEST_F(AuthTest, Login_SucceedsWithoutOtpIfPasswordIsCorrect)
{

}

/*
    Mock testing for: Auth::login
    Result: returns false if OTP is enabled but input is empty
*/
TEST_F(AuthTest, Login_FailsIfOtpEnabledButInputEmpty)
{

}

/*
    Mock testing for: Auth::login
    Result: returns false if OTP or password is incorrect
*/
TEST_F(AuthTest, Login_FailsIfOtpOrPasswordIncorrect)
{

}

/*
    Mock testing for: Auth::login
    Result: returns true if password and OTP are correct
*/
TEST_F(AuthTest, Login_SucceedsWithCorrectOtpAndPassword)
{

}



/*
    Test sessions: Auth::logout()
*/

/*
    Mock testing for: Auth::logout
    Result: does nothing if token is not found
*/
TEST_F(AuthTest, Logout_FailsIfSessionNotFound)
{

}

/*
    Mock testing for: Auth::logout
    Result: removes session if token exists
*/
TEST_F(AuthTest, Logout_SucceedsIfSessionExists)
{

}



/*
    Test sessions: Auth::create_session()
*/

/*
    Mock testing for: Auth::create_session
    Result: fails if username is empty
*/
TEST_F(AuthTest, CreateSession_FailsIfUsernameIsEmpty)
{

}

/*
    Mock testing for: Auth::create_session
    Result: fails if user not found in DB
*/
TEST_F(AuthTest, CreateSession_FailsIfUserNotFound)
{

}

/*
    Mock testing for: Auth::create_session
    Result: fails if session already active
*/
TEST_F(AuthTest, CreateSession_FailsIfSessionAlreadyExists)
{

}

/*
    Mock testing for: Auth::create_session
    Result: creates session for valid user
*/
TEST_F(AuthTest, CreateSession_SucceedsWithValidUser)
{

}



/*
    Test sessions: Auth::delete_session()
*/

/*
    Mock testing for: Auth::delete_session
    Result: does nothing if token not found
*/
TEST_F(AuthTest, DeleteSession_FailsIfTokenNotFound)
{

}

/*
    Mock testing for: Auth::delete_session
    Result: removes session if token exists
*/
TEST_F(AuthTest, DeleteSession_SucceedsIfTokenExists)
{

}



/*
    Test sessions: Auth::is_active_session()
*/

/*
    Mock testing for: Auth::is_active_session
    Result: returns false if session is not active
*/
TEST_F(AuthTest, IsActiveSession_ReturnsFalseIfNotActive)
{

}

/*
    Mock testing for: Auth::is_active_session
    Result: returns false if session is expired
*/
TEST_F(AuthTest, IsActiveSession_ReturnsFalseIfExpired)
{

}

/*
    Mock testing for: Auth::is_active_session
    Result: returns true if session is active and not expired
*/
TEST_F(AuthTest, IsActiveSession_ReturnsTrueIfValid)
{

}



/*
    Test sessions: Auth::is_session_expired()
*/

/*
    Mock testing for: Auth::is_session_expired
    Result: returns true if time exceeded SESSION_TIMEOUT
*/
TEST_F(AuthTest, IsSessionExpired_ReturnsTrueIfTimedOut)
{

}

/*
    Mock testing for: Auth::is_session_expired
    Result: returns false if within SESSION_TIMEOUT
*/
TEST_F(AuthTest, IsSessionExpired_ReturnsFalseIfWithinTimeout)
{

}



/*
    Test sessions: Auth::update_session_activity()
*/

/*
    Mock testing for: Auth::update_session_activity
    Result: updates last_activity to current time
*/
TEST_F(AuthTest, UpdateSessionActivity_UpdatesLastActivityTimestamp)
{

}



/*
    Test sessions: Auth::get_session()
*/

/*
    Mock testing for: Auth::get_session
    Result: returns nullptr if session not found
*/
TEST_F(AuthTest, GetSession_ReturnsNullptrIfNotFound)
{

}

/*
    Mock testing for: Auth::get_session
    Result: returns pointer to session if found
*/
TEST_F(AuthTest, GetSession_ReturnsSessionIfFound)
{

}



/*
    Test sessions: Auth::verify_session()
*/

/*
    Mock testing for: Auth::verify_session
    Result: returns false if token is invalid
*/
TEST_F(AuthTest, VerifySession_ReturnsFalseIfInvalidToken)
{

}

/*
    Mock testing for: Auth::verify_session
    Result: returns false if session inactive or expired
*/
TEST_F(AuthTest, VerifySession_ReturnsFalseIfInactiveOrExpired)
{

}

/*
    Mock testing for: Auth::verify_session
    Result: returns true if session is valid and active
*/
TEST_F(AuthTest, VerifySession_ReturnsTrueIfValid)
{

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}