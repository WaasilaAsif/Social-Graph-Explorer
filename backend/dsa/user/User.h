#pragma once
#include <string>

class User {
private:
    static int currentId;  // shared auto-ID generator

    int id;
    std::string name;
    std::string password;

public:
    // Constructor automatically assigns a unique ID
    User(const std::string& name, const std::string& password);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getPassword() const;

    // Setters (inline)
    void setName(const std::string& newName) { name = newName; }
    void setPassword(const std::string& newPassword) { password = newPassword; }
};
