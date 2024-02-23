#ifndef FCHUNK_H
#define FCHUNK_H

#include <initializer_list>
#include <inttypes.h>
#include <fstream>
#include <string>

#define FORMAT_NAME "WAVE"
#define RIFF_NAME "RIFF"

namespace Chunks {

    class Chunk{
        public:
            std::string chunkID;
            void readChunkID(std::ifstream* stream);
            void setChunkID(std::string chunkID);
        protected:
            void readU32s(std::ifstream* stream, std::initializer_list<uint32_t*> uints);
            void readU16s(std::ifstream* stream, std::initializer_list<uint16_t*> uints);
            void readU32(std::ifstream* stream , uint32_t* u);
            void readU16(std::ifstream* stream , uint16_t* u);
            std::string readString(std::ifstream* stream, unsigned int size);
    };

    class RIFFChunk : public Chunk{
        public:
            uint32_t chunkSize;
            std::string format;

        void readChunk(std::ifstream* stream);
        void printChunk();
        bool sanityCheck();
    };

    class GenericSubChunk : public Chunk{
        public:
            uint32_t    chunkSize;
            char*       data;

            void readChunk(std::ifstream* stream);
            void printChunk();
            ~GenericSubChunk();
    };

    class SubChunk1 : public Chunk{
        public:
            uint32_t    chunkSize;
            uint16_t    audioFormat;
            uint16_t    numChannels;
            uint32_t    sampleRate;
            uint32_t    byteRate;
            uint16_t    blockAlign;
            uint16_t    bitsPerSample;

            void readChunk(std::ifstream* stream);
            void printChunk();
            bool sanityCheck();
    };


    class SubChunk2 : public Chunk{
        public:
            uint32_t    chunkSize;

            void readChunk(std::ifstream* stream);
            void printChunk();
    };


}

#endif
