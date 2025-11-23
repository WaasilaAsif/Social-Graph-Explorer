<<<<<<< HEAD
#pragma once
#include <iostream>
#include <stdexcept>
#include <typeinfo>

template <typename T>
class DynamicArray
{
private:
    T *arr;
    int capacity;
    int length;

    void resize()
    {
        capacity *= 2;
        T *newArr = new T[capacity];
        for (int i = 0; i < length; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    DynamicArray()
    {
        capacity = 10;
        length = 0;
        arr = new T[capacity];
    }

    DynamicArray(const DynamicArray &other)
    {
        capacity = other.capacity;
        length = other.length;
        arr = new T[capacity];
        for (int i = 0; i < length; i++)
            arr[i] = other.arr[i];
    }

    DynamicArray &operator=(const DynamicArray &other)
    {
        if (this != &other)
        {
            delete[] arr;

            capacity = other.capacity;
            length = other.length;
            arr = new T[capacity];
            for (int i = 0; i < length; i++)
                arr[i] = other.arr[i];
        }
        return *this;
    }

    ~DynamicArray()
    {
        delete[] arr;
    }

    void printType()
    {
        std::cout << "Datatypes stored: " << typeid(T).name() << std::endl;
    }
    void removeAt(int index)
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");

        for (int i = index; i < length - 1; i++)
            arr[i] = arr[i + 1];

        length--;
    }

    T &at(int index)
    {
        return get(index);
    }

    const T &at(int index) const
    {
        return get(index);
    }
    void push_back(const T &element)
    {
        if (length == capacity)
            resize();
        arr[length++] = element;
    }

    T &get(int index)
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");
        return arr[index];
    }

    const T &get(int index) const
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");
        return arr[index];
    }

    int size() const
    {
        return length;
    }

    void pop_back()
    {
        if (length > 0)
            length--;
    }
=======
#pragma once
#include <iostream>
#include <stdexcept>
#include <typeinfo>

template <typename T>
class DynamicArray
{
private:
    T *arr;
    int capacity;
    int length;

    void resize()
    {
        capacity *= 2;
        T *newArr = new T[capacity];
        for (int i = 0; i < length; i++)
            newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
    }

public:
    DynamicArray()
    {
        capacity = 10;
        length = 0;
        arr = new T[capacity];
    }

    DynamicArray(const DynamicArray &other)
    {
        capacity = other.capacity;
        length = other.length;
        arr = new T[capacity];
        for (int i = 0; i < length; i++)
            arr[i] = other.arr[i];
    }

    DynamicArray &operator=(const DynamicArray &other)
    {
        if (this != &other)
        {
            delete[] arr;

            capacity = other.capacity;
            length = other.length;
            arr = new T[capacity];
            for (int i = 0; i < length; i++)
                arr[i] = other.arr[i];
        }
        return *this;
    }

    ~DynamicArray()
    {
        delete[] arr;
    }

    void printType()
    {
        std::cout << "Datatypes stored: " << typeid(T).name() << std::endl;
    }
    void removeAt(int index)
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");

        for (int i = index; i < length - 1; i++)
            arr[i] = arr[i + 1];

        length--;
    }

    T &at(int index)
    {
        return get(index);
    }

    const T &at(int index) const
    {
        return get(index);
    }
    void push_back(const T &element)
    {
        if (length == capacity)
            resize();
        arr[length++] = element;
    }

    T &get(int index)
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");
        return arr[index];
    }

    const T &get(int index) const
    {
        if (index < 0 || index >= length)
            throw std::out_of_range("Index out of range");
        return arr[index];
    }

    int size() const
    {
        return length;
    }

    void pop_back()
    {
        if (length > 0)
            length--;
    }
>>>>>>> origin/aman-branch
};