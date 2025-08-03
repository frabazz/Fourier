#include <cstdint>
#include <fstream>
#include <initializer_list>
#include <inttypes.h>
#include <iostream>

#include "chunks.hpp"
#include "mmapBuff.hpp"


using namespace std;
using namespace Chunks;

typedef initializer_list<uint32_t*> U32l;
typedef initializer_list<uint16_t*> U16l;


void Chunk::readU16s(MemUtils::RawBuff* stream, U16l uints){
    for(auto u : uints)
        stream->read((char*)u, sizeof(uint16_t));
}


void Chunk::readU32s(MemUtils::RawBuff* stream, U32l uints){
    for(auto u : uints)
        stream->read((char*)u, sizeof(uint32_t));
}

void Chunk::readU16(MemUtils::RawBuff* stream, uint16_t* u){
    stream->read((char*)u, sizeof(uint16_t));
}

void Chunk::readU32(MemUtils::RawBuff* stream, uint32_t* u){
    stream->read((char*)u, sizeof(uint32_t));
}

void Chunk::writeU16s(MemUtils::RawBuff* stream, U16l uints){
    for(auto u : uints)
        stream->write((char*)u, sizeof(uint16_t));
}


void Chunk::writeU32s(MemUtils::RawBuff* stream, U32l uints){
    for(auto u : uints)
        stream->write((char*)u, sizeof(uint32_t));
}

void Chunk::writeU16(MemUtils::RawBuff* stream, uint16_t* u){
    stream->write((char*)u, sizeof(uint16_t));
}

void Chunk::writeU32(MemUtils::RawBuff* stream, uint32_t* u){
    stream->write((char*)u, sizeof(uint32_t));
}


string Chunk::readString(MemUtils::RawBuff* stream, unsigned int size){
    char* tmp = new char[size+1];
    stream->read(tmp, size);
    tmp[size] = '\0';
    string ris = tmp;
    delete[] tmp;
    return ris;
}

void Chunk::writeString(MemUtils::RawBuff *stream, std::string data) {
  stream->write(data.c_str(), data.size());
}


void Chunk::setChunkID(string chunkID){
    this -> chunkID = chunkID;
}

void Chunk::readChunkID(MemUtils::RawBuff* stream){
    chunkID = readString(stream, 4);
}

// RIFFChunk Implementation

void RIFFChunk::readChunk(MemUtils::RawBuff* stream){
    readU32(stream, &chunkSize);
    format = readString(stream, 4);
}


void RIFFChunk::writeChunk(MemUtils::RawBuff *stream, uint32_t chunkSize) {
  writeString(stream, RIFF_NAME);
  writeU32(stream, &chunkSize);
  writeString(stream, FORMAT_NAME);
}

bool RIFFChunk::sanityCheck(){
    return (
        chunkID == RIFF_NAME &&
        format == FORMAT_NAME
    );
}


// GenericSubChunk Implemenation

void GenericSubChunk::readChunk(MemUtils::RawBuff* stream){
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

void SubChunk1::readChunk(MemUtils::RawBuff *stream) {
    readU32(stream, &chunkSize);
    readU16s(stream, {&audioFormat, &numChannels});
    readU32s(stream, {&sampleRate, &byteRate});
    readU16s(stream, {&blockAlign, &bitsPerSample});
}

void SubChunk1::writeChunk(MemUtils::RawBuff *stream, SubChunk1Data* data) {
  writeString(stream, SUBCHUNK_NAME_1);
  writeU32(stream, &data->chunkSize);
  writeU16s(stream, {&data->audioFormat, &data->numChannels});
  writeU32s(stream, {&data->sampleRate, &byteRate});
  writeU16s(stream, {&data->blockAlign, &data->bitsPerSample});
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

void SubChunk2::readChunk(MemUtils::RawBuff* stream){
    readU32(stream, &chunkSize);
}

void SubChunk2::writeChunk(MemUtils::RawBuff *stream, uint32_t chunkSize) {
  writeString(stream, SUBCHUNK_NAME_2);
  writeU32(stream, &chunkSize);
}



void SubChunk2::printChunk(){
    cout << "[" << chunkID << "]" << endl;
    cout << "Chunk Size(Data size): " << chunkSize << endl << endl;
}
