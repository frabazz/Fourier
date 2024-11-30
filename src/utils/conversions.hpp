#include <string>

#pragma once

class TimeStamp {
public:
  double s;
  int m;
  int h;

  TimeStamp(int h, int m, double s) {
    this->s = s;
    this->m = m;
    this->h = h;
  }

  void toString(std::string &out) {

    std::string seconds = std::to_string(this->s);
    // remove trailing zeros
    auto it = seconds.end() - 1;
    while (*it == '0' && it >= seconds.begin())
      --it;
    if (*it == '.')
      it++;
    seconds.erase(it + 1, seconds.end());

    if (h == 0) {
      if (m == 0)
        out = seconds + " s";
      else
        out = (m < 10 ? '0' + std::to_string(m) : std::to_string(m)) + ":" +
              seconds;
    } else
      out = std::to_string(h) + ":" +
            (m < 10 ? '0' + std::to_string(m) : std::to_string(m)) + ":" +
            seconds;
  }
};
