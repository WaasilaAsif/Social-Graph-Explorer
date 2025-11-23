<<<<<<< HEAD
#pragma once
#include<iostream>
#include<typeinfo>
template <typename A, typename B>
struct Pair {
    A first;
    B second;
public:
    Pair() {} 
    Pair(const A& a, const B& b) {
        first = a;
        second = b;
    }
    void printTypes(){
        std::cout<<"A: "<<typeid(A).name()<<std::endl;
        std::cout<<"B: "<<typeid(B).name()<<std::endl;
    }

};
=======
#pragma once
#include<iostream>
#include<typeinfo>
template <typename A, typename B>
struct Pair {
    A first;
    B second;
public:
    Pair() {} 
    Pair(const A& a, const B& b) {
        first = a;
        second = b;
    }
    void printTypes(){
        std::cout<<"A: "<<typeid(A).name()<<std::endl;
        std::cout<<"B: "<<typeid(B).name()<<std::endl;
    }

};
>>>>>>> origin/aman-branch
