#include "User.h"

// Initialize static member
int User::currentId = 0;

User::User(const std::string& name, const std::string& password)
    : name(name), password(password) 
{
    id = ++currentId;  // auto-increment ID
}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getPassword() const { return password; }
