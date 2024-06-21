#ifndef AUDIO_WORKERS_H
#define AUDIO_WORKERS_H

#include "wave.hpp"
#include "../common.hpp"

namespace audio_workers {

  struct sample_read_params{
    Wave::WaveFile* wav;
    dpair* range;
    double* min_y;
    double* max_y;
    int npoints;
    std::vector<dpair>* data;
  };

  void sample_read_worker(sample_read_params params);

}

#endif
