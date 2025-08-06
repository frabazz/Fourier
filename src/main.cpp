#include <iostream>
#include "audio/wave.hpp"
#include "audio/audioFX.hpp"
#include <complex>

int main() {

  Wave::WaveFile file = Wave::WaveFile("../assets/sixty.wav");
  file.open();

  file.printInfo();

  // Wave::WaveFile file2 = Wave::WaveFile("");
  // file2.open("test.wav", file.sampleSize);
  // for (int i = 0; i < file.sampleSize; ++i)
  //   file2.setSample(i, file.getSample(i));

  AudioFX fx = AudioFX(file);
  fx.bassBoost();
  fx.exportToWav("test2.wav");
  return 0;
}
