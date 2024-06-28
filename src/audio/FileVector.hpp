#ifndef FILE_VECTOR_H
#define FILE_VECTOR_H


#include <string>
#include <fstream>
#include <iostream>

using std::fstream;
using std::string;

template<typename T> class FileVector{
public:
  FileVector(string filename){
    _stream = fstream(filename, std::ios::binary | std::ios::out);
    if(!_stream.is_open())
      std::cout << "error!" << std::endl;
    _stream.close();
    _stream = fstream(filename, std::ios::binary | std::ios::in | std::ios::out);
    _size = 0;
    _curr = 0; // TODO: 0?
  } 
  
  void push_back(T x){
    //TODO: all function should point at last elem
    _stream.write((char*)&x, sizeof(T));
    _size++;
    _curr += sizeof(T);
  }

  void swap(int i1, int i2){
    T x1, tmp;
    // v[i1] -> x1
    _stream.seekg(i1 * sizeof(T), std::ios::beg);
    _stream.read((char*)&x1, sizeof(T));

    //v[i2] -> tmp
    _stream.seekg(i2 * sizeof(T), std::ios::beg);
    _stream.read((char*)&tmp, sizeof(T));

    //x1 -> v[i2]
    _stream.seekp(i2 * sizeof(T), std::ios::beg);
    _stream.write((char*)&x1, sizeof(T));

    //tmp -> v[i1]
    _stream.seekp(i1 * sizeof(T), std::ios::beg);
    _stream.write((char*)&tmp, sizeof(T));
  }

  T at(int i){
    int x;
    _stream.seekg(i * sizeof(T), std::ios::beg);
    _stream.read((char*)&x, sizeof(T));
    return x;

  }

  void set(int i, T x){
    _stream.seekp(i * sizeof(T), std::ios::beg);
    _stream.write((char*)&x, sizeof(T));
  }
  
  int size(){
    return _size;
  }

  void close(){
    _stream.close();
  }
  
private:
  std::ios::pos_type _curr;
  int _size;
  fstream _stream;
};


#endif
