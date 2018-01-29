cmake_minimum_required(VERSION 3.9)
project(PcapReader)

set(CMAKE_CXX_STANDARD 11)

include(FindPCAP.cmake)

add_executable(PcapReader main.cpp)

target_link_libraries(PcapReader ${PCAP_LIBRARY})