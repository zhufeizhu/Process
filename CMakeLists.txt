project(PROCESS_MOCK)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(./src/ SRC)

add_executable(process ${SRC})