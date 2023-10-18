#include <inttypes.h>
#include <fstream>
#include <string>

namespace Chunks {

    class GenericSubChunk {
        public:
            std::string chunkID;
            uint32_t    chunkSize;
            char*       data;

            void readChunk(std::ifstream* stream);
            void printChunk();
            ~GenericSubChunk();
    };

    class SubChunk1{
        public:
            std::string chunkID[4];
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


    class SubChunk2{
        public:
            std::string chunkID[4];
            uint32_t    chunkSize;

            void readChunk(std::ifstream* stream);
            void printChunk();
    };


}
