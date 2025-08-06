#include "audioFX.hpp"
#include "mmapBuff.hpp"
#include "wave.hpp"
#include "../math/algo.hpp"
#include <algorithm>
#include <complex>

#define SPEC_SUFF ".eq.bin"
#define OUT_SUFF ".out.bin"

AudioFX::AudioFX(Wave::WaveFile &audioIn){
  sampleSize = 1024;
  int channels = audioIn.subChunk1.numChannels;
  
  while(sampleSize < audioIn.sampleSize)
    sampleSize <<= 1;
  
  sampleRate = audioIn.subChunk1.sampleRate;

  size_t size = sampleSize * sizeof(std::complex<double>);
  samples = new MemUtils::MmapBuff<std::complex<double>>((audioIn.filename + OUT_SUFF).c_str(), size);
  spectrum = new MemUtils::MmapBuff<std::complex<double>>((audioIn.filename + SPEC_SUFF).c_str(), size);

  for (int frame = 0; frame < audioIn.sampleSize; ++frame) {
    double sum = 0;
    for (int ch = 0; ch < channels; ++ch) {
      sum += audioIn.getSample(frame * channels + ch);
    }
    samples->set(frame, sum / (double)channels);
  }

  for (int i = audioIn.sampleSize; i < sampleSize; ++i)
    samples->set(i, std::complex<double>(0.0, 0.0));

  
  freqDirty = true;
  sampleDirty = false;  
}

void AudioFX::calcFFT() {
  if (freqDirty) {
    std::cout << "computing FFT..." << std::endl;
    Algo::defaultFFT(*samples, *spectrum, sampleSize);
    freqDirty = false;
  }
}

void AudioFX::calcSamples() {
  if (sampleDirty) {
    std::cout << "computing IFFT..." << std::endl;
    Algo::defaultIFFT(*spectrum, *samples, sampleSize);
    sampleDirty = false;
  }
}

std::complex<double> AudioFX::getFreq(int freq) {
  calcFFT();
  return spectrum->get(freq);
}

void AudioFX::setFreq(int index, std::complex<double> freq) {
  spectrum->set(index, freq);
  sampleDirty = true;
}

void AudioFX::exportToWav(std::string filename) {
  calcFFT();
  calcSamples();

  Wave::WaveFile wave = Wave::WaveFile("");
  wave.open(filename, sampleSize);

  for (int i = 0; i < sampleSize; ++i) {
    double sample = samples->get(i).real();
    wave.setSample(i, std::clamp(sample, -0.99, 0.99));
  }
}

inline double dB2Lin(double x) {
  return std::pow(10.0, x/20.0);
}

double myEQCurve(double freq) {
  if (freq < 400) return dB2Lin(0);
  return 1.0;
}


void AudioFX::bassBoost() {
  calcFFT();
  std::cout << "applying bass boost" << std::endl;
  for (int k = 0; k <= sampleSize / 2; ++k) {
    double freq = k * (double)sampleRate / sampleSize;
    double gain = myEQCurve(freq);  
  std::complex<double> bin = spectrum->get(k);
  spectrum->set(k, bin * gain);
  if (k > 0 && k < sampleSize / 2)
    spectrum->set(sampleSize - k, std::conj(bin * gain));
}
  sampleDirty = true;

}
