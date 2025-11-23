#ifndef PAIR_H
#define PAIR_H
using namespace std;
#include <iostream>
template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;

    Pair() : first(), second() {}
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    // Overload the output stream operator for easy printing
    friend ostream& operator<<(ostream& os, const Pair<T1, T2>& pair) {
        os << "(" << pair.first << ", " << pair.second << ")";
        return os;
    }
};


#endif