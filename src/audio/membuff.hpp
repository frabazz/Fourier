#pragma once

#include <bits/stdc++.h>

template<typename T>
class Membuff {
public:
  virtual T& get(int index) = 0;
  virtual void set(int index, T val) = 0;
  virtual void read(char *pointer, size_t size) = 0;
  size_t offset = 0;
};
