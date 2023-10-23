#include <cstdint>
#include <fstream>
#include <initializer_list>
#include <inttypes.h>
#include <iostream>
#include <cstdio>

#include "chunks.h"


using namespace std;
using namespace Chunks;

typedef initializer_list<uint32_t*> U32l;
typedef initializer_list<uint16_t*> U16l;

// Chunk Implementation

void Chunk::readU16s(ifstream* stream, U16l uints){
    for(auto u : uints)
        (*stream).read((char*)u, sizeof(uint16_t));
}


void Chunk::readU32s(ifstream* stream, U32l uints){
    for(auto u : uints)
        (*stream).read((char*)u, sizeof(uint32_t));
}

void Chunk::readU16(ifstream* stream, uint16_t* u){
    (*stream).read((char*)u, sizeof(uint16_t));
}

void Chunk::readU32(ifstream* stream, uint32_t* u){
    (*stream).read((char*)u, sizeof(uint32_t));
}

string Chunk::readString(ifstream* stream, unsigned int size){
    char* tmp = new char[size+1];
    (*stream).read(tmp, size);
    tmp[size] = '\0';
    string ris = tmp;
    delete[] tmp;
    return ris;
}

void Chunk::setChunkID(string chunkID){
    this -> chunkID = chunkID;
}

void Chunk::readChunkID(ifstream* stream){
    chunkID = readString(stream, 4);
}

// RIFFChunk Implementation

void RIFFChunk::readChunk(ifstream* stream){
    readU32(stream, &chunkSize);
    format = readString(stream, 4);
}

bool RIFFChunk::sanityCheck(){
    return (
        chunkID == RIFF_NAME &&
        format == FORMAT_NAME
    );
}


// GenericSubChunk Implemenation

void GenericSubChunk::readChunk(ifstream* stream){
    readU32(stream, &chunkSize);
    data = new char[chunkSize+1];
    (*stream).read(data, chunkSize*sizeof(char));
    data[chunkSize] = '\0';
}

void GenericSubChunk::printChunk(){
    cout << "[" << chunkID << "]" << endl;
    cout << "Chunk Size: " << chunkSize << endl;
    cout << "Ascii Data: ";
    for(int i = 0;i < chunkSize;i++){
        cout << *(data+i);
    }
    cout << endl;
}

GenericSubChunk::~GenericSubChunk(){
    //delete[] data;
}

// SubChunk1 Implementation

void SubChunk1::readChunk(ifstream* stream){
    readU32(stream, &chunkSize);
    readU16s(stream, {&audioFormat, &numChannels});
    readU32s(stream, {&sampleRate, &byteRate});
    readU16s(stream, {&blockAlign, &bitsPerSample});
}

void SubChunk1::printChunk(){
    cout << "[" << chunkID << "]" << endl;
    cout << "Chunk Size: " << chunkSize << endl;
    cout << "Audio Format: " << audioFormat << endl;
    cout << "No of Channels: " << numChannels << endl;
    cout << "Sample Rate: " << sampleRate << endl;
    cout << "Byte Rate: " << byteRate << endl;
    cout << "Block Align: " << blockAlign << endl;
    cout << "Bits Per Sample: " << bitsPerSample << endl << endl;

}

bool SubChunk1::sanityCheck(){
        return (
            byteRate == sampleRate * numChannels * (bitsPerSample / 8) &&
            blockAlign == numChannels * (bitsPerSample / 8) &&
            audioFormat == 1 &&
            chunkSize == 16 &&
            (bitsPerSample == 8) || (bitsPerSample == 16) || (bitsPerSample == 32)
        );
}

// SubChunk2 Implementation

void SubChunk2::readChunk(ifstream* stream){
    readU32(stream, &chunkSize);
}

void SubChunk2::printChunk(){
    cout << "[" << chunkID << "]" << endl;
    cout << "Chunk Size(Data size): " << chunkSize << endl << endl;
}
