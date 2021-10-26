# cmake_minimum_required(VERSION <specify CMake version here>)
project(screenShare)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(SFML_ROOT "./SFML-2.5.1")

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)
#include_directories(./SFML-2.5.1/include)
#link_directories(./SFML-2.5.1/lib)
##add_library(SFML SFML-2.5.1/bin/sfml-audio-2.dll SFML-2.5.1/bin/sfml-graphics-2.dll SFML-2.5.1/bin/sfml-system-2.dll SFML-2.5.1/bin/sfml-window-2.dll SFML-2.5.1/bin/sfml-network-2.dll)
##set_target_properties(SFML PROPERTIES LINKER_LANGUAGE C)

# find sfml
add_executable(screenShare main.cpp)
target_link_libraries(screenShare sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
