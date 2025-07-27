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
        sum += mod * std::polar(1.0, phase);
      }

      out.set(i, sum);
    }

  }

  static void FFT(Membuff<double> &in, Membuff<std::complex<double>> &out,
                  int size) {
    
    size = (int)log2(size);
    for (uint32_t i = 0; i < size; ++i) {
      uint32_t j = reverse_bits(i, size/2 - 1);
      out.set(i, std::complex<double>(in.get(j)));
      out.set(j, std::complex<double>(in.get(i)));
      }

    int m = 2;
    while(m <= size){
      int half_m = m / 2;
      std::complex<double> w_m = std::polar(1.0, (-2*M_PI) / (m));

      for(int k = 0; k < size; k += m){
        std::complex<double> w = std::complex<double>(1.0, 0.0);
        for(int j = 0; j < half_m; ++j){
          auto t = w * out.get(k + j + half_m);
          auto u = out.get(k + j);
          out.set(k + j, u+t);
          out.set(k + j + half_m, u -t);
          w *= w_m;
        }
      }

      m*=2;
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
