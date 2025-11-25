#include "User.h"

// *** REMOVE THIS LINE ***
// int User::currentId = 0;  // Remove this

User::User(const std::string& name, const std::string& password)
    : name(name), password(password) 
{
    id = IDGenerator::getNextId();  // *** CHANGE THIS LINE ***
}

User::User() : name(""), password(""), id(0) {
    // Empty constructor doesn't get an ID
}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getPassword() const { return password; }
DynamicArray<std::string>& User::getPosts() { return posts; }

// Post management
void User::createPost(const std::string& content) {
    posts.push_back(content);
}

bool User::deletePost(int index) {
    if (index < 0 || index >= posts.size()) return false;
    
    // Shift elements left to remove the post
    for (int i = index; i < posts.size() - 1; i++) {
        posts.get(i) = posts.get(i + 1);
    }
    posts.pop_back();
    return true;
}
