#pragma once
#include <string>

class IDGenerator {
private:
    static int currentId;
    static const std::string ID_FILE_PATH;
    
    static void saveToFile();
    static void loadFromFile();

public:
    static int getNextId();
    static void reset();
    static void initialize();
    static int getCurrentId();
};
