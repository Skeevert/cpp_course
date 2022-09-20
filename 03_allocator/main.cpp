#include <iostream>
#include <memory>
#include <new>
#include <map>

#include "myallocator.h"
#include "myvector.h"

int factorial(int n) {
    int acc = 1;
    for (int i = 1; i <= n; i++) {
        acc *= i;
    }

    return acc;
}

int main() {
    std::map<int, int> std_map;

    for (int i = 0; i < 10; i++) {
        std_map[i] = factorial(i);
    }

    std::cout << "Map using standard allocator: ";
    for (const auto &pair : std_map) {
        std::cout << "[" << pair.first << ", " << pair.second << "] ";
    }
    std::cout << std::endl;


    std::map<int, int, std::less<int>, MyAllocator<std::pair<int, int>, 10>> test_map;

    for (int i = 0; i < 10; i++) {
        test_map[i] = factorial(i);
    }

    std::cout << "Map using my allocator";
    for (const auto &pair : test_map) {
        std::cout << "[" << pair.first << ", " << pair.second << "] ";
    }
    std::cout << std::endl;

    MyVector<int, MyAllocator<int, 10>> test_vector;
    
    for (int i = 0; i < 10; i++) {
        test_vector.push_back(i);
    }

    for(const auto &element : test_vector) {
        std::cout << element << ", ";
    }
    std::cout << std::endl;

	return 0;
}
