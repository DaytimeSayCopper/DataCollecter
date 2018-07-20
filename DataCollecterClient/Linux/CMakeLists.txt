cmake_minimum_required(VERSION 2.5)
project(DataCollecterClient)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-std=c++11)

set(CMKAE_THREAD_PREFER_PTHREAD)

aux_source_directory(./ SRC)
add_executable(collector ${SRC})
target_link_libraries(collector pthread)