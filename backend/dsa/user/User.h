#pragma once
#include <string>
#include "../data_structures/DynamicArray.h"

class User {
private:
    static int currentId;  // shared auto-ID generator

    int id;
    std::string name;
    std::string password;
    DynamicArray<std::string> posts;  // store user's posts

public:
    // Constructor automatically assigns a unique ID
    User(const std::string& name, const std::string& password);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getPassword() const;
    DynamicArray<std::string>& getPosts(); // returns reference to posts

    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setPassword(const std::string& newPassword) { password = newPassword; }

    // Post management
    void createPost(const std::string& content);
    bool deletePost(int index);  // returns true if deleted, false if invalid index
};
