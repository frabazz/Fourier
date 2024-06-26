#include "workers.hpp"
#include "wave.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <complex>
#include <fstream>
#include <string>

using namespace audio_workers;
using std::fstream;
using std::string;

namespace {

uint32_t reverse(uint32_t x, int s) {
  uint32_t r = x & 1; // get leftmost bit
  int size = s - 1;
  for (x >>= 1; x; x >>= 1) {
    size--;
    r <<= 1;
    r = r | x & 1;
  }
  r <<= size;
  return r;
}

template<typename T> class fileVector{
public:
  fileVector(string filename){
    _stream = fstream(filename, std::ios::binary | std::ios::out);
    if(!_stream.is_open())
      std::cout << "error!" << std::endl;
    _stream.close();
    _stream = fstream(filename, std::ios::binary | std::ios::in | std::ios::out);
    _size = 0;
    _curr = 0; // TODO: 0?
  } 
  
  void push_back(T x){
    //TODO: all function should point at last elem
    _stream.write((char*)&x, sizeof(T));
    _size++;
    _curr += sizeof(T);
  }

  void swap(int i1, int i2){
    T x1, tmp;
    // v[i1] -> x1
    _stream.seekg(i1 * sizeof(T), std::ios::beg);
    _stream.read((char*)&x1, sizeof(T));

    //v[i2] -> tmp
    _stream.seekg(i2 * sizeof(T), std::ios::beg);
    _stream.read((char*)&tmp, sizeof(T));

    //x1 -> v[i2]
    _stream.seekp(i2 * sizeof(T), std::ios::beg);
    _stream.write((char*)&x1, sizeof(T));

    //tmp -> v[i1]
    _stream.seekp(i1 * sizeof(T), std::ios::beg);
    _stream.write((char*)&tmp, sizeof(T));
  }

  T at(int i){
    int x;
    _stream.seekg(i * sizeof(T), std::ios::beg);
    _stream.read((char*)&x, sizeof(T));
    return x;

  }

  void set(int i, T x){
    _stream.seekp(i * sizeof(T), std::ios::beg);
    _stream.write((char*)&x, sizeof(T));
  }
  
  int size(){
    return _size;
  }

  void close(){
    _stream.close();
  }
  
private:
  std::ios::pos_type _curr;
  int _size;
  fstream _stream;
};

void FFT(fileVector<std::complex<double>>* samples, string filename, int isign) {
  int N = samples->size();
  if (N & (N - 1)) {
    std::cout << "N is not 2 power" << std::endl;
    return;
  }

  int p = 1;
  while (N >> (p + 1))
    p++;

  for (int i = 0; i < N / 2; ++i) {
    int r = reverse(i, p);
    //std::swap(v[i], v[r]);
    samples->swap(i, r);
  }

  
  /*
  auto v_copy = std::vector<std::complex<double>>(v);
  auto v_out = std::vector<std::complex<double>>(N);
  for (int k = 0; k < N; ++k) {
    int l = 2;
    for (int i = 0; i < p; ++i) {
      for (int j = 0; j < N; j += l) {
        std::complex odd = v_copy[j + (l >> 1)];
        v_copy[j] = v_copy[j] + std::polar(1.0, (-1) * (2 * M_PI * k) / N) * odd;
      }
      l <<= 1; // io
    }

    v_out[k] = v_copy[0];
  }
  */

  for (int s = 1; s <= p; ++s) {
        int m = 1 << s;
        std::complex<double> wm = std::polar(1.0, isign * 2.0 * M_PI / m);
        for (int k = 0; k < N; k += m) {
            std::complex<double> w = 1.0;
            for (int j = 0; j < m / 2; ++j) {
	      std::complex<double> t = w * samples->at(k + j + m / 2);
	      std::complex<double> u = samples->at(k + j);
	      samples->set(k + j , u + t);
              samples->set(k + j + m / 2, u - t);
                w *= wm;
            }
        }
    }
    
}

} // namespace

void audio_workers::sample_read_worker(sample_read_params params) {
  if (params.range->first < 0) {
    params.range->second += std::abs(params.range->first);
    params.range->first = 0;
    if (params.range->second > params.wav->sampleSize)
      params.range->second = params.wav->sampleSize;
  }

  if (params.range->second > params.wav->sampleSize) {
    params.range->first -= (params.range->second - params.wav->sampleSize);
    params.range->second = params.wav->sampleSize;
    if (params.range->first < 0)
      params.range->first = 0;
  }

  double delta =
      (params.range->second - params.range->first) / (double)(params.npoints);

  params.wav->seekStart();
  params.wav->seek(params.range->first);

  for (int i = 0; i < params.npoints - 1; ++i) {
    double sample = 0.0;
    params.wav->readSample(&sample);
    // std::cout << "read sample index " << params.range->first + (i+1) * delta
    // << " "; std::cout << "position : " << _wav_file->tell() << std::endl;
    //  std::cout << " of value " << sample << std::endl ;
    int cast_delta = i * delta;
    params.wav->seek((int)delta - 1);
    //_wav_file->seek((int)delta * (-1));
    params.data->push_back({(int)params.range->first + cast_delta, sample});
  }

  params.wav->seekStart(); // leave it as we got it!

  *params.min_y = -1.25;
  *params.max_y = 1.25;
  std::cout << "[SAMPLE READ WORKER] generated v of size: "
            << params.data->size() << std::endl;
  /*     *_wav_file = Wave::WaveFile("../assets/sin.wav");
      if(!_wav_file->open())
          std::cout << "error opening file" << std::endl;
  */
}


void audio_workers::fft_worker(Wave::WaveFile *wav, string filename){
  wav->seekStart();

  //TODO int32?
  int sample_size = wav->sampleSize;
  int fft_size = 1;
  
  while(fft_size < sample_size){
    fft_size <<= 1;
  }

  std::cout << "sample size : " << sample_size << " , fft_size: " << fft_size << std::endl; 

  auto v = fileVector<std::complex<double>>(filename);
  
  double sample;
  double pad = 0.0;
  int i = 0;

  for(i = 0;i < sample_size; ++i){
    double s;
    wav->readSample(&s);
    v.push_back({s, 0});
  }

  for(; i < fft_size; ++i)
    v.push_back(pad);

  for(i = 0;i < fft_size; ++i){
    v.set(i, v.at(i) * 0.5*(1-cos(2* M_PI * i)/fft_size)); //TODO: add multiple windowing functions
  }
  
  FFT(&v, filename, -1);
  /*
  for(int i = 0;i < fft_size >> 1; ++i)
    std::cout << "freq : " << i * 44100/fft_size << "Hz, amp : " << (fft[i])*(2.0/fft_size) << std::endl;
  */

  v.close();
  wav->seekStart();
}



void audio_workers::fft_read_worker(fft_read_params params) {
  const int maxFreq = 20000;
  if (params.range->first < 0) {
    params.range->second += std::abs(params.range->first);
    params.range->first = 0;
    if (params.range->second > maxFreq)
      params.range->second = maxFreq;
  }

  if (params.range->second > maxFreq) {
    params.range->first -= (params.range->second - maxFreq);
    params.range->second = maxFreq;
    if (params.range->first < 0)
      params.range->first = 0;
  }

  double delta =
      (params.range->second - params.range->first) / (double)(params.npoints);

  int j = params.range->first;
  auto v = fileVector<std::complex<double>>(params.filename);
  
  for (int i = 0; i < params.npoints - 1; ++i) {
    std::complex<double> sample = v.at(j);
    // std::cout << "read sample index " << params.range->first + (i+1) * delta
    // << " "; std::cout << "position : " << _wav_file->tell() << std::endl;
    //  std::cout << " of value " << sample << std::endl ;
    int cast_delta = i * delta;
    j += (int(delta) - 1) * (44100.0 / (double)v.size());
    
    //_wav_file->seek((int)delta * (-1));
    params.data->push_back({(int)params.range->first + cast_delta, std::abs(sample)/(double)v.size()});
  }

  v.close(); // leave it as we got it!

  *params.min_y = -1.25;
  *params.max_y = 1.25;
  std::cout << "[SAMPLE READ WORKER] generated v of size: "
            << params.data->size() << std::endl;
  /*     *_wav_file = Wave::WaveFile("../assets/sin.wav");
      if(!_wav_file->open())
          std::cout << "error opening file" << std::endl;
  */
}
