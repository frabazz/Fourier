#include <gtest/gtest.h>
#include <complex>
#include "../src/math/algo.hpp"
#include "../src/audio/mmapBuff.hpp"

#define TEST_FILENAME_IN "input.bin"
#define TEST_FILENAME_OUT "output.bin"
#define TEST_FILENAME_OUT2 "output2.bin"
#define FFT_SIZE 16
#define BUFF_SIZE (FFT_SIZE * sizeof(std::complex<double>))
#define EPS 0.01


TEST(FFT_ALGO, FFT_STD) {
  auto inbuff = MmapBuff<double>(TEST_FILENAME_IN, BUFF_SIZE);
  auto outbuff = MmapBuff<std::complex<double>>(TEST_FILENAME_OUT, BUFF_SIZE);
  auto outbuff2 = MmapBuff<std::complex<double>>(TEST_FILENAME_OUT2, BUFF_SIZE);

  for(int i = 0; i < FFT_SIZE; ++i)
    inbuff.set(i, i);
  
  Algo::DFT(inbuff, outbuff, FFT_SIZE);
  Algo::FFT(inbuff, outbuff2, FFT_SIZE);

  for(int i = 0; i < FFT_SIZE; ++i){
    std::complex<double> f1 = outbuff.get(i);
    std::complex<double> f2 = outbuff2.get(i);
    EXPECT_TRUE(std::abs(f1-f2) < EPS);
  }
  
}


TEST(FFT_ALGO, FFT_MP) {
  auto inbuff = MmapBuff<double>(TEST_FILENAME_IN, BUFF_SIZE);
  auto outbuff = MmapBuff<std::complex<double>>(TEST_FILENAME_OUT, BUFF_SIZE);
  auto outbuff2 = MmapBuff<std::complex<double>>(TEST_FILENAME_OUT2, BUFF_SIZE);

  for(int i = 0; i < FFT_SIZE; ++i)
    inbuff.set(i, i);
  
  Algo::DFT(inbuff, outbuff, FFT_SIZE);
  Algo::FFTMP(inbuff, outbuff2, FFT_SIZE);

  for(int i = 0; i < FFT_SIZE; ++i){
    std::complex<double> f1 = outbuff.get(i);
    std::complex<double> f2 = outbuff2.get(i);
    EXPECT_TRUE(std::abs(f1-f2) < EPS);
  }  
}
