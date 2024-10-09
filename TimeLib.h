#pragma once
#include <ctime>
#include <thread>
#include <chrono>
#include <ostream>
#include <cstdint>
#include <atomic>
#include <functional>

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

    // Interval Class
    class Interval {
    private:
        std::atomic<bool> running;
        std::thread intervalThread;
        void(*fn)();
        
    public:
        Interval() : running(false), fn(nullptr) {}
        
        void setInterval(void(*fn)(), unsigned int ms);

        void setLifetime(unsigned int lifetimeMs, unsigned int intervalMs);
        
        void stopInterval();

        ~Interval() {
            stopInterval();
        }
    };

}

// Implementation of setInterval method
void TimeLib::Interval::setInterval(void(*fn)(), unsigned int ms) {
    this->fn = fn;
    this->running = true;
    intervalThread = std::thread([this, ms]() {
        while (this->running) {
            if (this->fn != nullptr)
                this->fn();
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        }
    });
    intervalThread.detach();
}

void TimeLib::Interval::setLifetime(unsigned int lifetimeMs, unsigned int intervalMs) {
    std::thread lifetimeThread([this, lifetimeMs, intervalMs]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(lifetimeMs));
        stopInterval();
    });
    lifetimeThread.detach();
}

void TimeLib::Interval::stopInterval() {
    this->running = false;
    if (intervalThread.joinable()) {
        intervalThread.join();
    }
}
