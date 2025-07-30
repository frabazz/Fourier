#include "membuff.hpp"
#include "mmapBuff.hpp"
#include <bits/stdc++.h>
#include <complex.h>
#include <cstdint>
#include <immintrin.h>
#include <omp.h>

class Algo {
public:
  static void DFT(MmapBuff<double> &in, MmapBuff<std::complex<double>> &out,
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

    out.sync();
  }

  static void FFT(MmapBuff<double> &in, MmapBuff<std::complex<double>> &out,
                  int size) {

    int log2n = std::log2(size);

    for (int i = 0; i < size; ++i) {
      int j = reverse_bits(i, log2n);
      if (i < j) {
        std::complex<double> temp_i(in.get(i), 0.0);
        std::complex<double> temp_j(in.get(j), 0.0);
        out.set(i, temp_j);
        out.set(j, temp_i);
      } else if (i == j) {
        out.set(i, std::complex<double>(in.get(i), 0.0));
      }
    }

    for (int len = 2; len <= size; len <<= 1) {
      int half_len = len >> 1;
      std::complex<double> w_len = std::polar(1.0, -2 * M_PI / len);

      for (int i = 0; i < size; i += len) {
        std::complex<double> w = 1;

        for (int j = 0; j < half_len; ++j) {
          std::complex<double> u = out.get(i + j);
          std::complex<double> v = w * out.get(i + j + half_len);

          out.set(i + j, u + v);
          out.set(i + j + half_len, u - v);

          w *= w_len;
        }
      }
    }
    out.sync();
  }

  static void FFTMP(MmapBuff<double> &in, MmapBuff<std::complex<double>> &out,
                    int size) {

    int log2n = std::log2(size);

    for (int i = 0; i < size; ++i) {
      int j = reverse_bits(i, log2n);
      if (i < j) {
        std::complex<double> temp_i(in.get(i), 0.0);
        std::complex<double> temp_j(in.get(j), 0.0);
        out.set(i, temp_j);
        out.set(j, temp_i);
      } else if (i == j) {
        out.set(i, std::complex<double>(in.get(i), 0.0));
      }
    }

    for (int len = 2; len <= size; len <<= 1) {
      int half_len = len >> 1;
      std::complex<double> w_len = std::polar(1.0, -2 * M_PI / len);
      std::complex<double> w;
#pragma omp parallel for private(w)
      for (int i = 0; i < size; i += len) {
        w = 1;

        for (int j = 0; j < half_len; ++j) {
          std::complex<double> u = out.get(i + j);
          std::complex<double> v = w * out.get(i + j + half_len);

          out.set(i + j, u + v);
          out.set(i + j + half_len, u - v);

          w *= w_len;
        }
      }
    }

    out.sync();
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
