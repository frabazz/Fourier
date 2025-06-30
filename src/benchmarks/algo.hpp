#include "membuff.hpp"
#include <bits/stdc++.h>
#include <cmath>
#include <complex.h>
#include <cstdint>
#include <cstdio>

class Algo {
public:
  static void DFT(Membuff<double> &in, Membuff<std::complex<double>> &out,
                  int size) {
    for (int i = 0; i < size; ++i) {
      std::complex<double> sum = 0;

      for (int j = 0; j < size; ++j) {
        double mod = in.get(j);
        double phase = -((2 * M_PI * i * j) / size);
        sum += std::polar(mod, phase);
      }

      out.set(i, sum);
    }
  }

  static void FFT(Membuff<double> &in, Membuff<std::complex<double>> &out,
                  int size) {
    //reverse bit permutation

    for (uint32_t i = 0; i < size; ++i) {
      uint32_t j = reverse_bits(i, size/2 - 1);
      std::printf("swapping %d with %d\n", i, j);
      out.set(i, std::complex<double>(in.get(j)));
      out.set(j, std::complex<double>(in.get(i)));
    }

         
  }


private:
  static uint32_t reverse_bits(uint32_t x, int n) {
    uint32_t result = 0;
    for (int i = 0; i < n; ++i) {
        uint32_t bit = (x >> i) & 1;
        result |= bit << (n - 1 - i);
    }
    return result;
}
};
