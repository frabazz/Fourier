#include <iostream>
#include "audio/wave.hpp"

int main() {

  Wave::WaveFile file = Wave::WaveFile("../assets/sin2.wav");
  file.open();

  file.printInfo();

  Wave::WaveFile file2 = Wave::WaveFile("");
  file2.open("test.wav", file.sampleSize);
  for (int i = 0; i < file.sampleSize; ++i) 
    file2.setSample(i, file.getSample(i));
  return 0;
}
