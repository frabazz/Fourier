#include <cstdint>
#include <fstream>
#include <inttypes.h>
#include <iostream>
#include <cstdio>

#include "chunks.h"


using namespace std;
using namespace Chunks;

void GenericSubChunk::readChunk(ifstream* stream){
    *stream >> chunkSize;
    data = new char[ (int)chunkSize ];
    (*stream).read(data, chunkSize);
}

void GenericSubChunk::printChunk(){
    cout << "Chunk Size: " << chunkSize << endl;
    cout << "Ascii Data: ";
    printf("%.*s", chunkSize, data);
}

GenericSubChunk::~GenericSubChunk(){
    delete data;
}



void SubChunk1::readChunk(ifstream* stream){
    *stream >> audioFormat;
    *stream >> numChannels;
    *stream >> sampleRate;
    *stream >> byteRate;
    *stream >> blockAlign;
    *stream >> bitsPerSample;
}

void SubChunk1::printChunk(){
    cout << "Chunk Size: " << chunkSize << endl;
    cout << "Audio Format: " << audioFormat << endl;
    cout << "No of Channels: " << numChannels << endl;
    cout << "Sample Rate: " << sampleRate << endl;
    cout << "Byte Rate: " << byteRate << endl;
    cout << "Block Align: " << blockAlign << endl;
    cout << "Bits Per Sample: " << bitsPerSample << endl;

}

bool SubChunk1::sanityCheck(){
        return (
            byteRate == sampleRate * numChannels * (bitsPerSample / 8) &&
            blockAlign == numChannels * (bitsPerSample / 8) &&
            audioFormat == 1 &&
            chunkSize == 16
        );
}


void SubChunk2::readChunk(ifstream* stream){
    *stream >> chunkSize;
}

void SubChunk2::printChunk(){
    cout << "Chunk Size(Data size): " << chunkSize << endl;
}
