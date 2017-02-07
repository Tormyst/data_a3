cmake_minimum_required(VERSION 2.8.11)
project(data_a3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

include_directories( ${data_a3_SOURCE_DIR}/include )
set(SOURCE_FILES src/main.cpp src/loadCSV.cpp src src/database.cpp src/frequentSet.cpp include/frequentSet.h)
add_executable(data_a3 ${SOURCE_FILES})
