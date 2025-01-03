#include <fstream>
#include <iostream>
#include <string>
#include <inttypes.h>
#include <vector>

#include "wave.hpp"

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
    startPos = -1;
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
    startPos = file.tellg();
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


void WaveFile::readSample(std::vector<double>* arr){
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
}


void WaveFile::readSample(double* psample){
    for(int i = 0; i < subChunk1.numChannels; i++){
        if(subChunk1.bitsPerSample == 8){
            int8_t sample;
            file.read((char*)&sample, sizeof(sample));
            *psample = (double)sample / MAX_SAMPLE_8;
        }

        else if(subChunk1.bitsPerSample == 16){
            int16_t sample;
            file.read((char*)&sample, sizeof(sample));
            *psample = (double)sample / MAX_SAMPLE_16;
        }

        else if(subChunk1.bitsPerSample == 32){
            int32_t sample;
            file.read((char*)&sample, sizeof(sample));
            *psample = (double)sample / MAX_SAMPLE_32;
        }

    }
}

//move to file pointer to the amount of sample specified by the paramater from current position 
void WaveFile::seek(int samples){
    if(subChunk1.bitsPerSample == 8)
        file.seekg(samples * subChunk1.numChannels * sizeof(int8_t), ios::cur);
    else if(subChunk1.bitsPerSample == 16)
        file.seekg(samples * subChunk1.numChannels * sizeof(int16_t), ios::cur);
    else if(subChunk1.bitsPerSample == 32)
        file.seekg(samples * subChunk1.numChannels * sizeof(int32_t), ios::cur);
}

decltype(std::ifstream().tellg()) WaveFile::tell(){
    return file.tellg();
}

void WaveFile::seekStart(){
    file.seekg(startPos, ios::beg);
}

void WaveFile::close(){
    file.close();
}
