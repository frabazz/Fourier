#include <cstddef>
#include <fstream>
#include <string>
#include <vector>
#include "chunks.h"

#define SUBCHUNK_NAME_1 "fmt "
#define SUBCHUNK_NAME_2 "data"

namespace Wave {

    class WaveFile{
        public:
            WaveFile(std::string filename);
            int open();
            void printInfo();
            bool sanityCheck();


            template<int, std::size_t n>
            void operator >> (std::array <int, n>);

        private:
            std::ifstream file;
            std::string filename;
            Chunks::RIFFChunk riffChunk;
            Chunks::SubChunk1 subChunk1;
            Chunks::SubChunk2 subChunk2;
            std::vector <Chunks::GenericSubChunk> chunks;

    };
}
