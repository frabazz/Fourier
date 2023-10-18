#include <fstream>
#include <string>
#include <vector>
#include "chunks.h"

#define SUBCHUNK_NAME_1 ""
#define SUBCHUNK_NAME_2 ""
#define RIFF_NAME "RIFF"
#define FORMAT_NAME "WAVE"

namespace Wave {

    class WaveFile{
        public:
            std::ifstream file;
            std::string filename;
            Chunks::SubChunk1 subChunk1;
            Chunks::SubChunk2 subChunk2;
            std::vector <Chunks::GenericSubChunk> chunks;

            WaveFile(std::string filename);
            int open();
            void printInfo();
            bool sanityCheck();
    };
}
