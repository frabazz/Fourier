#pragma once

#include "membuff.hpp"
#include <bits/stdc++.h>
#include <fstream>

template<typename T>
class FStreambuff : public Membuff<T> {
public:
  FStreambuff(std::fstream &file) : file(file) {}

  T& get(int index) {
    file.seekg(index * sizeof(T));
    T ris;
    file.read((char *)&ris, sizeof(T));
    return ris;
  }

  void set(int index, T val) {
    file.seekp(index * sizeof(T));
    file.write((const char*)&val, sizeof(T));
  }

private:
  std::fstream &file;
};
