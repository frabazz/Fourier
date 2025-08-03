#include "mmapBuff.hpp"

using namespace MemUtils;

RawBuff::RawBuff(const char *filename, size_t file_size)
      : size_bytes(file_size), mem(nullptr) {
    offset = 0;
    mem = (char *)MemUtils::getFileMapCreate(filename, file_size);
  }
RawBuff::RawBuff(const char *filename) : mem(nullptr) {
    offset = 0;
    mem = (char *)MemUtils::getFileMap(filename, &size_bytes);
  }
    
void RawBuff::read(char *pointer, size_t size) { 
memcpy(pointer, mem+offset, size);
 offset += size; 
}

void RawBuff::readAt(char *pointer, size_t size, int offset) {
    memcpy(pointer, mem + offset, size);
  }

void RawBuff::write(const char *pointer, size_t size) {
      memcpy( mem+offset, pointer, size);
 offset += size; 
}


void RawBuff::writeAt(char *pointer, size_t size, int offset) {
    memcpy(mem + offset, pointer, size);
}

