# https://github.com/kartikkumar/cppbase

cmake_minimum_required(VERSION 3.9)
project(NetworkReader)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
set(INCLUDE_PATH "${PROJECT_PATH}/include")
set(RRD_LIBRARIES rrd)

include(FindPCAP.cmake)

include_directories(AFTER "${INCLUDE_PATH}")

add_executable(NetworkReader main.cpp src/pcap_reader.cpp include/pcap_reader.h src/rrd_reader.cpp include/rrd_reader.h include/reader_interface.h)

target_link_libraries(NetworkReader ${PCAP_LIBRARY} ${RRD_LIBRARIES})