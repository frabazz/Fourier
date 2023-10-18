#include <fstream>
#include <iostream>
#include <string>
#include <inttypes.h>

#include "wave.h"

using namespace std;
using namespace Wave;
using namespace Chunks;

WaveFile::WaveFile(string filename){
    this -> filename = filename;
}

int WaveFile::open(){
    char* buffer = new char[4];
    uint32_t chunkSize;

    file = ifstream(filename, ios::binary);
    if(!file) return 0;

    file.read(buffer, 4);
    if(string(buffer, 4) != RIFF_NAME) return 0;
    file.read((char*)&chunkSize, sizeof(uint32_t));

    file.read(buffer, 4);
    if(string(buffer, 4) != FORMAT_NAME){
        cout << string(buffer, 4) << endl;
        return 0;
    }

    string bufferStr;
    bool last = false;

    chunks = vector<GenericSubChunk>();

    while(!last){
        file.read(buffer, 4);
        bufferStr = string(buffer, 4);

        if(bufferStr == SUBCHUNK_NAME_1){
            subChunk1 = SubChunk1();
            subChunk1.readChunk(&file);
        }
        else if(bufferStr == SUBCHUNK_NAME_2){
            subChunk2 = SubChunk2();
            subChunk2.readChunk(&file);
            last = true;
        }
        else{
            GenericSubChunk chunk = GenericSubChunk();
            chunk.readChunk(&file);
            chunks.push_back(chunk);
        }
    }

    return 1;
}

void WaveFile::printInfo(){
    subChunk1.printChunk();
    for(auto chunk : chunks)
        chunk.printChunk();
    subChunk2.printChunk();
}
