#include <iostream>
#include<typeinfo>
#include "dsa/containers/DynamicArray.h"
#include "dsa/utils/Pair.h"
#include "dsa/utils/idGenerator.h"
#include<string>
int main() {
    DynamicArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);

    for(int i = 0; i < arr.size(); i++)
        std::cout << arr.get(i) << std::endl;
    Pair<std::string,int> p("Hey",7);
    p.printTypes();
    IDGenerator ourGenerator;
    std::cout<< ourGenerator.getNextId()<<std::endl;
std::cout<< ourGenerator.getNextId()<<std::endl;
std::cout<< ourGenerator.getNextId()<<std::endl;
std::cout<< ourGenerator.getNextId()<<std::endl;
    return 0;
}
