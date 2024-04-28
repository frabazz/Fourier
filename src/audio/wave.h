#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <string>
#include <vector>
#include <iostream>

#include "chunks.h"


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

            void operator>> (std::vector<double>* arr){
                for(int i = 0; i < subChunk1.numChannels; i++){
                    if(subChunk1.bitsPerSample == 8){
                        int8_t sample;
                        file.read((char*)&sample, sizeof(sample));
                        arr->push_back((double)sample / MAX_SAMPLE_8);
                    }

                    else if(subChunk1.bitsPerSample == 16){
                        int16_t sample;
                        file.read((char*)&sample, sizeof(sample));
                        arr->push_back((double)sample / MAX_SAMPLE_16);
                    }

                    else if(subChunk1.bitsPerSample == 32){
                        int32_t sample;
                        file.read((char*)&sample, sizeof(sample));
                        arr->push_back((double)sample / MAX_SAMPLE_16);
                    }

                }
            };
    };
}
