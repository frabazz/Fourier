#ifndef WAVE_FILE_H
#define WAVE_FILE_H

#include <fstream>
#include <string>
#include <variant>
#include <vector>

#include "mmapBuff.hpp"
#include "chunks.hpp"

#define MAX_SAMPLE_8 128.0
#define MAX_SAMPLE_16 32768.0
#define MAX_SAMPLE_32 2147483648.0
#define WRITE_MARGIN 300  

namespace Wave {

class WaveFile {

private:
  std::variant < MemUtils::MmapBuff<int8_t>, MemUtils::MmapBuff<int16_t>,
                 MemUtils::MmapBuff<int32_t>> wave_file;
  std::string filename;
  double max_sample;
  decltype(std::ifstream().tellg()) startPos;

public:
  int sampleSize;
  Chunks::RIFFChunk riffChunk;
  Chunks::SubChunk1 subChunk1;
  Chunks::SubChunk2 subChunk2;
  std::vector<Chunks::GenericSubChunk> chunks;

  WaveFile(std::string filename);
  int open();
  void open(std::string filename, int sample_size);
  void printInfo();
  bool sanityCheck();
  void readSample(std::vector<double> *sample);
  void readSample(double *sample);
  double getSample(int index);
  void setSample(int index, double sample);
  void seek(int samples);
  decltype(std::ifstream().tellg()) tell();
  void seekStart();
  void close();
  
};
} // namespace Wave

#endif
