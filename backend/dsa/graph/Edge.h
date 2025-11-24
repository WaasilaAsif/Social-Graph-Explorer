#ifndef EDGE_H
#define EDGE_H

class Edge {
public:
    int to;      // destination node ID
    int weight;  // edge weight

    Edge(int to, int weight = 1) : to(to), weight(weight) {}

    // Equality operator for removal
    bool operator==(const Edge& other) const {
        return to == other.to && weight == other.weight;
    }
    // Inequality operator
    bool operator!=(const Edge& other) const {
        return !(*this == other);
    }
};

#endif // EDGE_H