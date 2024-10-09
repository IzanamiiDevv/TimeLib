#include <iostream>
#include "TimeLib.h"

int main() {

    TimeLib::setTimeout(10, nullptr, [](){printf("Test");});
    std::cout << "Hello Wrodl" << std::endl;

    TimeLib::Interval* obj = new TimeLib::Interval();
    obj->setInterval([](){
        std::cout << "Hello Guys" << std::endl;
    }, 1000);
    
    std::cin.get();

    obj->stopInterval();
    delete obj;

    std::cout << "The Program is Ended" << std::endl;
    return 0;
}