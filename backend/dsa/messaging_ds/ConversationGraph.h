#ifndef CONVERSATION_GRAPH_H
#define CONVERSATION_GRAPH_H

#include "../containers/HashMap.h"
#include "../containers/DynamicArray.h"
#include "../utils/Pair.h"
#include <string>
using namespace std;

class ConversationGraph {
private:
    // userID -> list of (neighbor, weight)
    HashMap<int, DynamicArray<Pair<int, int>>> adj;

public:
    ConversationGraph();

    void addInteraction(int userA, int userB);
    DynamicArray<int> getNeighbors(int user) const;
    int getInteractionWeight(int userA, int userB) const;
    bool userExists(int user) const;
    DynamicArray<int> getAllUsers() const;
    int getTotalInteractions(int user) const;
};

#endif
