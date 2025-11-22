#pragma once
#include <stdexcept>
#include <string>

class UserNotFoundError : public std::runtime_error {
public:
    UserNotFoundError(const std::string& msg = "User not found")
        : std::runtime_error(msg) {}
};

class DuplicateUserError : public std::runtime_error {
public:
    DuplicateUserError(const std::string& msg = "User already exists")
        : std::runtime_error(msg) {}
};

class InvalidLoginError : public std::runtime_error {
public:
    InvalidLoginError(const std::string& msg = "Invalid username or password")
        : std::runtime_error(msg) {}
};