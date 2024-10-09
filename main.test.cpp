#include <iostream>
#include "TimeLib.h"

int main() {

    TimeLib::setTimeout(10, nullptr, [](){printf("Test");});
    std::cout << "Hello Wrodl" << std::endl;
    std::cin.get();
    return 0;
}