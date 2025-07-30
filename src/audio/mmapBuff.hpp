#pragma once
#include "membuff.hpp"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <cstdlib>
#include <cstring>

template <typename T>
class MmapBuff : public Membuff<T> {
public:
  MmapBuff(const char* filename, size_t size_in_bytes)
      : size_bytes(size_in_bytes), mem(nullptr), buffer(nullptr) {
    
    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
      throw std::runtime_error("open failed");
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
      close(fd);
      throw std::runtime_error("fstat failed");
    }
    if (st.st_size != static_cast<off_t>(size_bytes)) {
      if (ftruncate(fd, size_bytes) == -1) {
        close(fd);
        throw std::runtime_error("ftruncate failed");
      }
    }

    mem = (T*)(mmap(nullptr, size_bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    close(fd);

    if (mem == MAP_FAILED) {
      throw std::runtime_error("mmap failed");
    }
  }

  ~MmapBuff() {
    if (mem != nullptr) {
      munmap(mem, size_bytes);
    }
    if (buffer != nullptr) {
      free(buffer);
    }
  }

  T& get(int index) override {
    return mem[index];
  }

  void set(int index, T val) override {
    mem[index] = val;
  }

  void sync() {
    if (msync(mem, size_bytes, MS_SYNC) == -1) {
      throw std::runtime_error("msync failed");
    }
  }

private:
  T* mem;
  T* buffer;
  const size_t size_bytes;
};
