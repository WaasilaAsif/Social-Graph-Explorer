#pragma once

class IDGenerator {
private:
    static int currentId; 

public:
    static int getNextId() {
        return ++currentId;
    }

    static void reset() {
        currentId = 0;
    }
};

