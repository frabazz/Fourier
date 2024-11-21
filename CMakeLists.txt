cmake_minimum_required(VERSION 3.10)
project(Fourier VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

set(CMAKE_BUILD_TYPE Debug)
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(CMAKE_CXX_FLAGS_DEBUG  "-g -lSDL2_ttf")
set(CMAKE_CXX_FLAGS "-lSDL2_ttf")
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.hpp")

add_executable(exec ${SOURCE_FILES})

target_include_directories(exec PUBLIC
    ${SOURCE_DIR}/graphics
    ${SOURCE_DIR}/audio
    ${SOURCE_DIR}/math
)

target_link_libraries(exec ${SDL2_LIBRARIES} ${SDL2_PATH} SDL2_image SDL2_ttf)
