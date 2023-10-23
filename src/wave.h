#include <cstddef>
#include <cstdint>
#include <fstream>
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
                    switch(subChunk1.bitsPerSample){
                        case 8:
                            int8_t i8;
                            file.read((char*)&i8, sizeof(int8_t));
                            (*arr).push_back(((double)i8/MAX_SAMPLE_8));
                            break;
                        case 16:
                            int16_t i16;
                            file.read((char*)&i16, sizeof(int16_t));
                            (*arr).push_back(((double)i16/MAX_SAMPLE_16)) ;
                            break;
                        case 32:
                            int32_t i32;
                            file.read((char*)&i32, sizeof(int32_t));
                            (*arr).push_back(((double)i32/MAX_SAMPLE_32));
                            break;
                    }
                }
            };

        private:
            std::ifstream file;
            std::string filename;
    };
}
