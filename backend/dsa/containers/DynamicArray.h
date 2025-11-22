#pragma once
#include<iostream>
#include <stdexcept> 
#include<typeinfo> 
template <typename T>
class DynamicArray {
private:
    T* arr;         
    int capacity;   
    int length;      
    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < length; i++)
            newArr[i] = arr[i];  // copy old elements
        delete[] arr;
        arr = newArr;
    }

public:
    DynamicArray() {
        capacity = 10;
        length = 0;
        arr = new T[capacity];
    }
    ~DynamicArray() {
        delete[] arr;
    }
    void printType(){
        std::cout<<"Datatypes stored: "<<typeid(T).name()<<std::endl;
    }
    void push_back(const T& element) {
        if (length == capacity) resize();
        arr[length++] = element;
    }
    T& get(int index) {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");
        return arr[index];
    }
    int size() {
        return length;
    }
    void pop_back() {
        if (length > 0) length--;
    }
};
