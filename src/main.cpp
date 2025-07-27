#include "benchmarks/membuff.hpp"
#include <fstream>
#include "benchmarks/algo.hpp"
#include "benchmarks/clock.hpp"
#include <random>

#define filename "output.txt"

void rgen_file(std::fstream& ofs, std::size_t byte_count) {
    if (!ofs) {
        std::cerr << "Errore apertura file\n";
        return;
    }

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);

    constexpr std::size_t buffer_size = 4096;
    std::vector<unsigned char> buffer(buffer_size);

    std::size_t bytes_written = 0;
    while (bytes_written < byte_count) {
        std::size_t chunk = std::min(buffer_size, byte_count - bytes_written);
        for (std::size_t i = 0; i < chunk; ++i) {
            buffer[i] = dist(gen);
        }
        ofs.write(reinterpret_cast<char*>(buffer.data()), chunk);
        bytes_written += chunk;
    }
}

int main(int argc, char* argv[]) {

  int size = 1 << 12;
  
  std::fstream input =
    std::fstream("input.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);

  std::fstream output =
    std::fstream("output.bin", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
  std::cout << "starting file gen..." << std::endl;
  rgen_file(input, size * sizeof(double));
  std::cout << "end file gen" << std::endl;
  
  auto inbuff = Membuff<double>(input);
  auto outbuff = Membuff<std::complex<double>>(output);
  
  Clock c = Clock();
  c.tic();
  Algo::DFT(inbuff, outbuff, size);
  int el = c.toc().count();
  std::cout << "DFT: " << el << " us" << std::endl;

  for(int i = 0; i < 10; ++i)
    std::cout << outbuff.get(i) << std::endl;
  
  c.tic(); 
  Algo::FFT(inbuff, outbuff, size);
  el = c.toc().count();
  std::cout << "FFT: " << el << " us" << std::endl;

  for(int i = 0; i < 10; ++i)
    std::cout << outbuff.get(i) << std::endl;
  
  return 0;
}


