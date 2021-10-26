# cmake_minimum_required(VERSION <specify CMake version here>)
project(screenShare)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(SFML_ROOT "./SFML-2.5.1")

# find sfml
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(screenShare src/main.cpp src/Screen/Screen.cpp src/Screen/Screen.h)
target_link_libraries(screenShare sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
