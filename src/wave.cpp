#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <inttypes.h>
#include <vector>
#include <array>

#include "wave.h"

using namespace std;
using namespace Wave;
using namespace Chunks;

WaveFile::WaveFile(string filename){
    this -> filename = filename;
    riffChunk = RIFFChunk();
    subChunk1 = SubChunk1();
    subChunk2 = SubChunk2();
    chunks = vector<GenericSubChunk>();
    sampleSize = -1;
}

int WaveFile::open(){

    file = ifstream(filename, ios::binary);
    if(!file){
        cout << "error opening in file" << endl;
        return 0;
    }

    Chunk tmpChunk = Chunk();
    tmpChunk.readChunkID(&file);

    riffChunk.setChunkID(tmpChunk.chunkID);
    riffChunk.readChunk(&file);
    if(!riffChunk.sanityCheck()){
        cout << "the file is not either riff or wave type" << endl;
        return 0;
    }

    bool last = false;

    chunks = vector<GenericSubChunk>();

    while(!last){
        tmpChunk.readChunkID(&file);

        if(tmpChunk.chunkID == SUBCHUNK_NAME_1){
            subChunk1.setChunkID(tmpChunk.chunkID);
            subChunk1.readChunk(&file);
        }
        else if(tmpChunk.chunkID == SUBCHUNK_NAME_2){
            subChunk2.setChunkID(tmpChunk.chunkID);
            subChunk2.readChunk(&file);
            last = true;
        }
        else{
            GenericSubChunk chunk = GenericSubChunk();
            chunk.setChunkID(tmpChunk.chunkID);
            chunk.readChunk(&file);
            chunks.push_back(chunk);
        }
    }

    sampleSize = subChunk2.chunkSize/ subChunk1.numChannels / (subChunk1.bitsPerSample/8);

    return 1;
}



void WaveFile::printInfo(){
    subChunk1.printChunk();
    for(auto chunk : chunks)
        chunk.printChunk();
    subChunk2.printChunk();

    cout << "[GENERAL INFO]" << endl;
    cout << "no of samples: " << sampleSize << endl;
}
