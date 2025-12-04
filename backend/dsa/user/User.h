#pragma once
#include <string>
#include "../containers/DynamicArray.h"
#include "../utils/IDGenerator.h" 

class User {
private:
    
    int id;
    std::string name;
    std::string password;
    DynamicArray<std::string> posts;

public:
    // Constructor automatically assigns a unique ID
    User(const std::string& name, const std::string& password);
    User(); 
    
    // Getters
    int getId() const;
    std::string getName() const;
    std::string getPassword() const;
    DynamicArray<std::string>& getPosts();

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setPassword(const std::string& newPassword) { password = newPassword; }

    // Post management
    void createPost(const std::string& content);
    bool deletePost(int index);
};
