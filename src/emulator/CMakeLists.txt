cmake_minimum_required(VERSION 2.8)
project(ubr_emulator)

include_directories(src/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCES
    main.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})
