#pragma once

#include <chrono>

typedef decltype(std::chrono::high_resolution_clock::now()) ctime_t;
typedef std::chrono::microseconds us_t; 

class Clock{
public:
  Clock(){
    curr_time = std::chrono::high_resolution_clock::now();
  }

  void tic(){
    curr_time = std::chrono::high_resolution_clock::now();
  }

  us_t toc(){
    auto last_time = curr_time;
    tic();
    return std::chrono::duration_cast<us_t> (curr_time - last_time);
  }

private:
  ctime_t curr_time;
};
