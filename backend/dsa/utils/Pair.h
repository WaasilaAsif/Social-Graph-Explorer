#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <typeinfo>

template <typename A, typename B>
struct Pair {
    A first;
    B second;

    Pair() : first(), second() {} 
    Pair(const A& a, const B& b) : first(a), second(b) {}
    
    void printTypes() {
        std::cout << "A: " << typeid(A).name() << std::endl;
        std::cout << "B: " << typeid(B).name() << std::endl;
    }

    // Overload the output stream operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const Pair<A, B>& p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
};

#endif // PAIR_H
