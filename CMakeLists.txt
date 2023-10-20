cmake_minimum_required(VERSION 3.10)
project("Fourier" VERSION 1.0)

set(CMAKE_SOURCE_DIR "./src/")
add_executable(Fourier src/test.cpp src/chunks.cpp src/wave.cpp)
