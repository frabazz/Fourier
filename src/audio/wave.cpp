#include <atomic>
#include <fstream>
#include <inttypes.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "chunks.hpp"
#include "mmapBuff.hpp"
#include "wave.hpp"

using namespace std;
using namespace Wave;
using namespace Chunks;

WaveFile::WaveFile(string filename) {
  this->filename = filename;
  riffChunk = RIFFChunk();
  subChunk1 = SubChunk1();
  subChunk2 = SubChunk2();
  chunks = vector<GenericSubChunk>();
  sampleSize = -1;
  startPos = -1;
}

int WaveFile::open() {

  auto rawBuff = MemUtils::RawBuff(filename.c_str());

  Chunk tmpChunk = Chunk();
  tmpChunk.readChunkID(&rawBuff);

  riffChunk.setChunkID(tmpChunk.chunkID);
  riffChunk.readChunk(&rawBuff);
  if (!riffChunk.sanityCheck()) {
    cout << "the file is not either riff or wave type" << endl;
    return 0;
  }

  bool last = false;

  chunks = vector<GenericSubChunk>();

  while (!last) {
    tmpChunk.readChunkID(&rawBuff);

    if (tmpChunk.chunkID == SUBCHUNK_NAME_1) {
      subChunk1.setChunkID(tmpChunk.chunkID);
      subChunk1.readChunk(&rawBuff);
    } else if (tmpChunk.chunkID == SUBCHUNK_NAME_2) {
      subChunk2.setChunkID(tmpChunk.chunkID);
      subChunk2.readChunk(&rawBuff);
      last = true;
    } else {
      GenericSubChunk chunk = GenericSubChunk();
      chunk.setChunkID(tmpChunk.chunkID);
      chunk.readChunk(&rawBuff);
      chunks.push_back(chunk);
    }
  }
  startPos = 0;
  sampleSize = subChunk2.chunkSize / subChunk1.numChannels /
               (subChunk1.bitsPerSample / 8);

  switch (subChunk1.bitsPerSample) {
  case 8:
    wave_file = MemUtils::MmapBuff<int8_t>(&rawBuff);
    max_sample = MAX_SAMPLE_8;
    break;
  case 16:
    wave_file = MemUtils::MmapBuff<int16_t>(&rawBuff);
    max_sample = MAX_SAMPLE_16;
    break;
  case 32:
    wave_file = MemUtils::MmapBuff<int32_t>(&rawBuff);
    max_sample = MAX_SAMPLE_32;
    break;
  default:
    throw std::runtime_error("unexpected bits per sample");
  }

  return 1;
}

void WaveFile::open(std::string name, int sampleSize) {
  max_sample = MAX_SAMPLE_16;
  uint16_t bitsPerSample = 16;
  this->sampleSize = sampleSize;
  //  = size(RIFF) + size(FMT) + size(DATA)
  size_t file_size = (12) + (24) + (8 + (bitsPerSample / 8) * sampleSize);
  std::cout << "allocating " << file_size << " bytes" << std::endl;
  auto rawBuff = MemUtils::RawBuff(name.c_str(), file_size);
  uint32_t riffChunkSize = file_size - 8;
  riffChunk.writeChunk(&rawBuff, riffChunkSize);

  uint32_t sampleRate = 48000;
  uint32_t fmtChunkSize = 16; // must be 16, 18 or 40
  uint16_t numChannels = 1;
  uint32_t byteRate = sampleRate * numChannels * bitsPerSample / 8;
  uint16_t blockAlign = numChannels * (bitsPerSample/8);
  SubChunk1Data s1data = {fmtChunkSize, 1, numChannels, sampleRate, byteRate, blockAlign, bitsPerSample};
  

  subChunk1.writeChunk(&rawBuff, &s1data);
  uint32_t chunkSize = (bitsPerSample / 8) * s1data.numChannels * sampleSize;
  subChunk2.writeChunk(&rawBuff, chunkSize);
  
  wave_file = MemUtils::MmapBuff<int16_t>(&rawBuff);

}

double WaveFile::getSample(int index) {
  return std::visit([index, this](auto &&wave) -> double {
    return wave.get(index)/this->max_sample;
  }, wave_file);
}

void WaveFile::setSample(int index, double sample) {
  std::visit([this, index, sample](auto &&wave) {
    int denormalized = sample * this->max_sample;
    //  std::cout << "denormalized: " << denormalized << std::endl;
    wave.set(index, denormalized);
  }, wave_file);
}

void WaveFile::printInfo() {
  subChunk1.printChunk();
  for (auto chunk : chunks)
    chunk.printChunk();
  subChunk2.printChunk();

  cout << "[GENERAL INFO]" << endl;
  cout << "no of samples: " << sampleSize << endl;

  int duration = (sampleSize) / subChunk1.sampleRate;

  cout << "duration: " << duration << "s" << endl;
}



void WaveFile::readSample(std::vector<double> *arr) {
  /*  for (int i = 0; i < subChunk1.numChannels; i++) {
    if (subChunk1.bitsPerSample == 8) {
      int8_t sample;
      wave_file.read((char *)&sample, sizeof(sample));
      arr->push_back((double)sample / MAX_SAMPLE_8);
    }

    else if (subChunk1.bitsPerSample == 16) {
      int16_t sample;
      wave_file.read((char *)&sample, sizeof(sample));
      arr->push_back((double)sample / MAX_SAMPLE_16);
    }

    else if (subChunk1.bitsPerSample == 32) {
      int32_t sample;
      wave_file.read((char *)&sample, sizeof(sample));
      arr->push_back((double)sample / MAX_SAMPLE_16);
    }
    }*/
}

void WaveFile::readSample(double *psample) {
  /*for (int i = 0; i < subChunk1.numChannels; i++) {
    if (subChunk1.bitsPerSample == 8) {
      int8_t sample;
      wave_file.read((char *)&sample, sizeof(sample));
      *psample = (double)sample / MAX_SAMPLE_8;
    }

    else if (subChunk1.bitsPerSample == 16) {
      int16_t sample;
      wave_file.read((char *)&sample, sizeof(sample));
      *psample = (double)sample / MAX_SAMPLE_16;
    }

    else if (subChunk1.bitsPerSample == 32) {
      int32_t sample;
      wave_file.read((char *)&sample, sizeof(sample));
      *psample = (double)sample / MAX_SAMPLE_32;
    }
    }*/
}

// move to file pointer to the amount of sample specified by the paramater from
// current position
void WaveFile::seek(int samples) {
  // TODO remove
  /*if (subChunk1.bitsPerSample == 8)
    wave_file.seekg(samples * subChunk1.numChannels * sizeof(int8_t), ios::cur);
  else if (subChunk1.bitsPerSample == 16)
    file.seekg(samples * subChunk1.numChannels * sizeof(int16_t), ios::cur);
  else if (subChunk1.bitsPerSample == 32)
  file.seekg(samples * subChunk1.numChannels * sizeof(int32_t), ios::cur);*/
}

decltype(std::ifstream().tellg()) WaveFile::tell() { /*return file.tellg();*/ }

void WaveFile::seekStart() { /*file.seekg(startPos, ios::beg); */ }

void WaveFile::close() { /*file.close(); */ }
