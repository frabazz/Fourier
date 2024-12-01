#include <cmath>
#include <string>

#pragma once

#define F_DECIMALS 1000 // 1000 = 3 decimals 

class TimeStamp {
public:
  double s;
  int m;
  int h;
  enum string_format {
    TSHOUR,   // hh:mm:ss.sss
    TSMINUTE, // mm:ss.sss
    TSSECOND  // ss.sss
  };

  TimeStamp(int h, int m, double s) {
    this->s = s;
    this->m = m;
    this->h = h;
  }

  TimeStamp(double seconds) {
    this->m = (int)(seconds) / 60;
    this->s = seconds - (this->m * 60);
    this->h = this->m / 60;
    this->m = this->m - (this->h * 60);
  }

  
  void fromSeconds(double seconds) {
    this->m = (int)(seconds) / 60;
    this->s = seconds - (this->m * 60);
    this->h = this->m / 60;
    this->m = this->m - (this->h * 60);
  }

  
  double toSeconds() {
    return (double)this->h * 3600 + (double)this->m * 60 + this->s;
  }

  std::string toString(string_format fmt) {
    std::string seconds = getSecondFormat();
    if (fmt == TSHOUR) {
      return std::to_string(h) + ":" +
             (m < 10 ? '0' + std::to_string(m) : std::to_string(m)) +
             (this->s < 10 ? '0' + seconds : seconds);
    } else if (fmt == TSMINUTE) {
      return std::to_string(m) + ":" + (this->s < 10 ? '0' + seconds : seconds);
    } else if (fmt == TSSECOND) {
      return seconds;
    } else {
      return toString(TSHOUR);
    }
  }

  string_format getDefaultFormat() {
    if (h == 0) {
      if (m == 0)
        return TSSECOND;
      else
        return TSMINUTE;
    } else
      return TSHOUR;
  }

  std::string toString() {
    if (h == 0) {
      if (m == 0)
        return toString(TSSECOND);
      else
        return toString(TSMINUTE);
    } else
      return toString(TSHOUR);
  }

private:
  std::string getSecondFormat() {
    
    std::string seconds = std::to_string(std::trunc(this->s * F_DECIMALS) / F_DECIMALS);
    // remove trailing zeros
    auto it = seconds.end() - 1;
    while (*it == '0' && it >= seconds.begin())
      --it;
    if (*it == '.')
      it++;
    seconds.erase(it + 1, seconds.end());
    return seconds;
  }
};
