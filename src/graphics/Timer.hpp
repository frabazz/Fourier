#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <chrono>

namespace MyTimer{

class Timer{
    public:
        Timer(){
            _start_time = std::chrono::system_clock::now();
        }

        int measure(){
            auto now = std::chrono::system_clock::now();
            auto delta = std::chrono::duration_cast<std::chrono::microseconds>(now - _start_time);
            return delta.count();
        }

        void restart(){
            _start_time = std::chrono::system_clock::now();
        }
    private:
        decltype(std::chrono::system_clock::now()) _start_time;
};

}
#endif
