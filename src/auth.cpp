#include <../include/auth.h>
#include <../include/app.h>
#include <../include/log.h>
#include <../include/user.h>
#include <sodium.h>
#include <iostream>
#include <string>

// Development of auth.cpp is in progress.

Logger auth_logger("../logs/genpass.log");

Auth::Auth()
{
    auth_logger.log(Log_level::INFO, "Auth constructor called.");
}

Auth::~Auth()
{
    auth_logger.log(Log_level::INFO, "Auth destructor called.");
}