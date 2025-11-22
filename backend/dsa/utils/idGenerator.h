#pragma once
class IDGenerator {
private:
    int currentId; 
public:
    IDGenerator() : currentId(0) {}  
    int getNextId() {
        return ++currentId;  
    }
    void reset() {
        currentId = 0;
    }
};
