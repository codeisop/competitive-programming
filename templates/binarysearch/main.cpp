// main.cpp

#include <iostream>
#include "BinarySearch.h"

int main() {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13};

    int key = 7;
    int result = binarySearch(arr, key);

    if (result != -1) {
        std::cout << "Element found at index " << result << std::endl;
    } else {
        std::cout << "Element not found" << std::endl;
    }

    return 0;
}
