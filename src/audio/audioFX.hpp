#pragma once

#include "mmapBuff.hpp"

namespace Wave {
  class WaveFile;
}

class AudioFX {
public:
  AudioFX(Wave::WaveFile& audioFile);
  std::complex<double> getFreq(int freq);
  double getSample(int index);
  void setFreq(int index, std::complex<double> freq);
  void exportToWav(std::string filename);
  void bassBoost();

private:
  MemUtils::MmapBuff<std::complex<double>>* samples;
  MemUtils::MmapBuff<std::complex<double>>* spectrum;
  bool freqDirty;
  bool sampleDirty;
  int sampleSize;
  int sampleRate;
  void calcFFT();
  void calcSamples();
};


