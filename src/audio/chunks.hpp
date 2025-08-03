#ifndef FCHUNK_H
#define FCHUNK_H

#include <initializer_list>
#include <inttypes.h>

#include "mmapBuff.hpp"
#include <string>

#define FORMAT_NAME "WAVE"
#define RIFF_NAME "RIFF"
#define SUBCHUNK_NAME_1 "fmt "
#define SUBCHUNK_NAME_2 "data"

namespace Chunks {

class Chunk {
public:
  std::string chunkID;
  void readChunkID(MemUtils::RawBuff *stream);
  void setChunkID(std::string chunkID);

protected:
  void readU32s(MemUtils::RawBuff *stream,
                std::initializer_list<uint32_t *> uints);
  void readU16s(MemUtils::RawBuff *stream,
                std::initializer_list<uint16_t *> uints);
  void readU32(MemUtils::RawBuff *stream, uint32_t *u);
  void readU16(MemUtils::RawBuff *stream, uint16_t *u);
  void writeU32s(MemUtils::RawBuff *stream,
                std::initializer_list<uint32_t *> uints);
  void writeU16s(MemUtils::RawBuff *stream,
                std::initializer_list<uint16_t *> uints);
  void writeU32(MemUtils::RawBuff *stream, uint32_t *u);
  void writeU16(MemUtils::RawBuff *stream, uint16_t *u);

  std::string readString(MemUtils::RawBuff *stream, unsigned int size);
  void writeString(MemUtils::RawBuff *stream, std::string data);
};

class RIFFChunk : public Chunk {
public:
  uint32_t chunkSize;
  std::string format;

  void readChunk(MemUtils::RawBuff *stream);
  void writeChunk(MemUtils::RawBuff* stream, uint32_t chunkSize);
  void printChunk();
  bool sanityCheck();
};

class GenericSubChunk : public Chunk {
public:
  uint32_t chunkSize;
  char *data;

  void readChunk(MemUtils::RawBuff *stream);
  void printChunk();
  ~GenericSubChunk();
};


struct SubChunk1Data {
  uint32_t chunkSize;
  uint16_t audioFormat;
  uint16_t numChannels;
  uint32_t sampleRate;
  uint32_t byteRate;
  uint16_t blockAlign;
  uint16_t bitsPerSample;
};
  
class SubChunk1 : public Chunk {
public:
  uint32_t chunkSize;
  uint16_t audioFormat;
  uint16_t numChannels;
  uint32_t sampleRate;
  uint32_t byteRate;
  uint16_t blockAlign;
  uint16_t bitsPerSample;
  
  void readChunk(MemUtils::RawBuff *stream);
  void writeChunk(MemUtils::RawBuff *stream, SubChunk1Data* data);
  
  void printChunk();
  bool sanityCheck();
};

class SubChunk2 : public Chunk {
public:
  uint32_t chunkSize;

  void readChunk(MemUtils::RawBuff *stream);
  void writeChunk(MemUtils::RawBuff *stream, uint32_t chunkSize);
  void printChunk();
};

  
} // namespace Chunks

#endif
