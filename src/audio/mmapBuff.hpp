#pragma once
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <inttypes.h>
#include <iostream>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace MemUtils {

template <typename T> class MmapBuff;

inline void *getFileMap(const char *filename, size_t *file_size) {
  int fd = open(filename, O_RDWR | O_CREAT, 0666);
  if (fd == -1) {
    throw std::runtime_error("open failed");
  }

  struct stat st;
  if (fstat(fd, &st) == -1) {
    close(fd);
    throw std::runtime_error("fstat failed");
  }

  *file_size = st.st_size;
  void *mem =
      (mmap(nullptr, *file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  close(fd);

  if (mem == MAP_FAILED)
    throw std::runtime_error("mmap failed");
  return mem;
}

inline void *getFileMapCreate(const char *filename, size_t file_size) {
  int fd = open(filename, O_RDWR | O_CREAT, 0666);
  if (fd == -1) {
    throw std::runtime_error("open failed");
  }

  struct stat st;
  if (fstat(fd, &st) == -1) {
    close(fd);
    throw std::runtime_error("fstat failed");
  }
  if (st.st_size != static_cast<off_t>(file_size)) {
    if (ftruncate(fd, file_size) == -1) {
      close(fd);
      throw std::runtime_error("ftruncate failed");
    }
  }

  void *mem =
      (mmap(nullptr, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
  close(fd);

  if (mem == MAP_FAILED)
    throw std::runtime_error("mmap failed");

  return mem;
}

class RawBuff {
  template <typename T> friend class MmapBuff;

public:
  RawBuff(const char *filename, size_t file_size);
  RawBuff(const char *filename);

  void read(char *pointer, size_t size);
  void readAt(char *pointer, size_t size, int offset);
  void write(const char *pointer, size_t size);
  void writeAt(char *pointer, size_t size, int offset);

private:
  char *mem;
  size_t size_bytes;
  size_t offset;
};

template <typename T> class MmapBuff {
public:
  MmapBuff(const char *filename, size_t file_size);

  MmapBuff(const char *filename);

  MmapBuff();

  MmapBuff(RawBuff *buff) {
    mem = (T *)(buff->mem + buff->offset);
    size_bytes = buff->size_bytes - buff->offset;
    initialized = true;
  }
  
  ~MmapBuff();

  T &get(int index);
  void set(int index, T val);
  void read(char *pointer, size_t size);
  void readAt(char *pointer, size_t size, int offset);
  void sync();

private:
  T *mem;
  size_t size_bytes;
  bool initialized = false;
};

template <typename T>
MmapBuff<T>::MmapBuff(const char *filename, size_t file_size)
    : size_bytes(file_size), mem(nullptr) {
  mem = (T *)MemUtils::getFileMapCreate(filename, file_size);
}

template <typename T>
MmapBuff<T>::MmapBuff(const char *filename) : mem(nullptr) {
  mem = (T *)MemUtils::getFileMap(filename, &size_bytes);
}

template <typename T> MmapBuff<T>::MmapBuff() : mem(nullptr) {}

template <typename T> T &MmapBuff<T>::get(int index) { return mem[index]; }

template <typename T> void MmapBuff<T>::set(int index, T val) {
  mem[index] = val;
}

template <typename T> void MmapBuff<T>::read(char *pointer, size_t size) {
  //
}

template <typename T>
void MmapBuff<T>::readAt(char *pointer, size_t size, int offset) {
  //
}

template <typename T> void MmapBuff<T>::sync() {
  if (msync(mem, size_bytes, MS_SYNC) == -1) {
    throw std::runtime_error("msync failed");
  }
}

template <typename T> MmapBuff<T>::~MmapBuff() {
  if (mem != nullptr && !initialized) {
    munmap(mem, size_bytes);
  }
}

} // namespace MemUtils
