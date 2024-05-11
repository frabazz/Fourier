#ifndef WAVE_FILE_H
#define WAVE_FILE_H

#include <fstream>
#include <string>
#include <vector>

#include "chunks.hpp"


#define SUBCHUNK_NAME_1 "fmt "
#define SUBCHUNK_NAME_2 "data"
#define MAX_SAMPLE_8 128.0
#define MAX_SAMPLE_16 32768.0
#define MAX_SAMPLE_32 2147483648.0

namespace Wave {

    class WaveFile{

        private:
            std::ifstream file;
            std::string filename;
            decltype(std::ifstream().tellg()) startPos;
        public:
            int sampleSize;
            Chunks::RIFFChunk riffChunk;
            Chunks::SubChunk1 subChunk1;
            Chunks::SubChunk2 subChunk2;
            std::vector <Chunks::GenericSubChunk> chunks;

            WaveFile(std::string filename);
            int open();
            void printInfo();
            bool sanityCheck();
            void readSample(std::vector<double>* sample);
            void readSample(double* sample);
            void seek(int samples);
            decltype(std::ifstream().tellg()) tell();
            void seekStart();
            void close();
    };
}

#endif
