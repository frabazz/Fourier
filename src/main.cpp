#include "benchmarks/membuff.hpp"
#include <fstream>
#include "benchmarks/algo.hpp"

#define filename "output.txt"

int main(int argc, char* argv[]) {
  std::fstream input =
    std::fstream("input.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);

  std::fstream output =
    std::fstream("output.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);

  auto inbuff = Membuff<double>(input);
  auto outbuff = Membuff<std::complex<double>>(output);

  for(int i = 0; i < 8; ++i)
    inbuff.set(i, i);
  
  Algo::FFT(inbuff, outbuff, 8);
  for (int i = 0; i < 8; ++i)
    std::cout << outbuff.get(i) << " ";
  return 0;
}
