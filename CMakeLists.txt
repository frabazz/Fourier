cmake_minimum_required(VERSION 3.15)
project(Fourier VERSION 1.0 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake OPTIONAL)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

find_package(sdl2 REQUIRED)
find_package(OpenMP REQUIRED)
find_package(GTest REQUIRED)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")

add_executable(exec ${SOURCE_FILES})

target_include_directories(exec PRIVATE
    ${SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(exec PRIVATE
#        -O3
#        -mavx2
#        -mfma
         -fopenmp
         -g
#        -march=native
#        -ftree-vectorize
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(exec PRIVATE
        /O2
        /arch:AVX2
    )
endif()

target_link_libraries(exec PRIVATE
    SDL2::SDL2 SDL2_image SDL2_ttf
    OpenMP::OpenMP_CXX
)

enable_testing()
add_subdirectory(tests)
