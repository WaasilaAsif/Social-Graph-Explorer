#include "IDGenerator.h"
#include <fstream>
#include <iostream>

int IDGenerator::currentId = 0;
const std::string IDGenerator::ID_FILE_PATH = "../storage/local_db/current_id.txt";

void IDGenerator::saveToFile() {
    std::ofstream file(ID_FILE_PATH);
    if (file.is_open()) {
        file << currentId;
        file.close();
    } else {
        std::cerr << "Warning: Could not save current ID to file" << std::endl;
    }
}

void IDGenerator::loadFromFile() {
    std::ifstream file(ID_FILE_PATH);
    if (file.is_open()) {
        file >> currentId;
        file.close();
        std::cout << "IDGenerator loaded from file: starting at ID " << (currentId + 1) << std::endl;
    } else {
        // File doesn't exist, initialize from users.json
        std::ifstream usersFile("../storage/local_db/users.json");
        if (usersFile.is_open()) {
            std::string line;
            int maxId = 0;
            while (std::getline(usersFile, line)) {
                // Simple parsing to find "id": number patterns
                size_t idPos = line.find("\"id\":");
                if (idPos != std::string::npos) {
                    size_t numStart = line.find_first_of("0123456789", idPos);
                    if (numStart != std::string::npos) {
                        int id = std::stoi(line.substr(numStart));
                        if (id > maxId) {
                            maxId = id;
                        }
                    }
                }
            }
            usersFile.close();
            currentId = maxId;
            std::cout << "IDGenerator initialized from users.json: found max ID " << maxId << ", starting at ID " << (currentId + 1) << std::endl;
            saveToFile(); // Save for next time
        } else {
            std::cout << "IDGenerator: No existing data found, starting at ID 1" << std::endl;
            currentId = 0;
        }
    }
}

int IDGenerator::getNextId() {
    int nextId = ++currentId;
    saveToFile(); // Persist after each ID generation
    return nextId;
}

void IDGenerator::reset() {
    currentId = 0;
    saveToFile();
}

void IDGenerator::initialize() {
    loadFromFile();
}

int IDGenerator::getCurrentId() {
    return currentId;
}