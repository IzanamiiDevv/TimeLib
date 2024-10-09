#pragma once
#include <ctime>
#include <thread>
#include <chrono>
#include <ostream>
#include <cstdint>

namespace TimeLib {
    void sleep(unsigned int duration , void(*while_fn)(int)) {
        using namespace std::chrono_literals;
        for(unsigned int time = 0; time < duration; ++time) {
            if(while_fn != nullptr)
                while_fn(time + 1);
            std::this_thread::sleep_for(1s);
        }
    }

    void adv_sleep(uint32_t duration, uint16_t update, void(*while_fn)(int)) {
        for(unsigned int time = 0; time < duration; time += update) {
            if(while_fn != nullptr)
                while_fn(time);
            std::this_thread::sleep_for(std::chrono::milliseconds(update));
        }
    }

    void setTimeout(unsigned int duration , void(*while_fn)(int), void(*after_fn)()) {
        std::thread t([duration, while_fn, after_fn](){
            using namespace std::chrono_literals;
            for(unsigned int time = 0; time < duration; ++time) {
                if(while_fn != nullptr)
                    while_fn(time + 1);
                std::this_thread::sleep_for(1s);
            }
            
            after_fn();
        });
        t.detach();
    }

    void adv_setTimeout(uint32_t duration, uint16_t update, void(*while_fn)(int), void(*after_fn)()) {
        std::thread t ([duration, update, while_fn, after_fn](){
            for(unsigned int time = 0; time < duration; time += update) {
                if(while_fn != nullptr)
                    while_fn(time);
                std::this_thread::sleep_for(std::chrono::milliseconds(update));
            }

            after_fn();
        });
        t.detach();
    }

    
}