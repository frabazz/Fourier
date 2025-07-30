#include <fstream>
#include "../src/math/algo.hpp"
#include "clock.hpp"
#include "benchmarks/mmapBuff.hpp"
#include <random>
#include <omp.h>

#define INPUT_FILENAME "input.bin"
#define OUTPUT_FILENAME "output.bin"

using FFTimpl = std::function<void(MmapBuff<double>&, MmapBuff<std::complex<double>>&, int)>;

template<typename T> using Vec = std::vector<T>;

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

void init_files(int size) {
    
    std::fstream input =
      std::fstream(INPUT_FILENAME, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
    std::cout << "starting file gen with size: " << size <<  std::endl;
    rgen_file(input, size * sizeof(double));
    input.close();
    
}

int benchmark(int size, FFTimpl impl) {
    auto inbuff = MmapBuff<double>(INPUT_FILENAME, size * sizeof(double));
    auto outbuff = MmapBuff<std::complex<double>>(OUTPUT_FILENAME, size * sizeof(std::complex<double>));
    inbuff.sync();
  
    Clock c = Clock();
    c.tic();
    impl(inbuff, outbuff, size);
    int el = c.toc().count();
    outbuff.sync();
    return el;
}

void gen_csv(std::string filename, Vec<int> sizes, std::map<std::string, Vec<int>> benchmarks) {
  std::ofstream csv = std::ofstream(filename);
  csv << "impl,dim,time_us" << std::endl;
  for (auto b : benchmarks) {
    auto t = b.second;
    for (int i = 0;i < sizes.size(); ++i)
      csv << b.first << "," << sizes[i] << "," << t[i] << std::endl;
  }
}

int main(int argc, char* argv[]) {

  std::map<std::string, FFTimpl> impls = {
    {"fft_openmp", Algo::FFTMP}
    //{"fft_std", Algo::FFT},
    //    {"fft_local", Algo::FFTLocal}
  };

  std::map<std::string, Vec<int>> benchmarks;
  for (auto k : impls)
    benchmarks[k.first] = Vec<int>();

  Vec<int> sizes = Vec<int>();
  for (int j = 10; j < 25; ++j)
    sizes.push_back(1 << j);

  std::cout << "using " << omp_get_max_threads() << " threads" << std::endl;
  
  std::cout << "running benchmarks..." << std::endl;
  /*for(auto size : sizes){
    std::cout << "size: " << size << std::endl;
    for (auto impl : impls) {
      int t = benchmark(size, impl.second);
      benchmarks[impl.first].push_back(t);
    }
  }
  std::cout << "generating csv" << std::endl;
  gen_csv("benchs.csv", sizes, benchmarks);
  */
  benchmark(1<<25, Algo::FFTMP);
  return 0;
}


