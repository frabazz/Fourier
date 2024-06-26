#ifndef AUDIO_WORKERS_H
#define AUDIO_WORKERS_H

#include "wave.hpp"
#include "../common.hpp"
#include <string>

namespace audio_workers {

  struct sample_read_params{
    Wave::WaveFile* wav;
    dpair* range;
    double* min_y;
    double* max_y;
    int npoints;
    std::vector<dpair>* data;
  };

  struct fft_read_params{
    std::string filename;
    dpair* range;
    double* min_y;
    double* max_y;
    int npoints;
    std::vector<dpair>* data;
  };
  
  
  void sample_read_worker(sample_read_params params);
  void fft_worker(Wave::WaveFile* wav, std::string filename);
  void fft_read_worker(fft_read_params params);
  }

#endif
