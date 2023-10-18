cmake_minimum_required(VERSION 2.8)
project(ubr_emulator)

include_directories(src/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(EMULATOR_SRC
    emulator/emulator.cc
)

set(MEMORY_SRC
    memory/memory.cc

)

set(MEMORY_MANAGER_SRC
    memory_manager/memory_manager.cc
)

set(DEVICE_SRC
    device/device.cc
)

set(PROCESSOR_SRC
    processor/processor.cc
)

set(UTILS_SRC
    ../utils/utils.cc
)

set(SOURCES
    main.cc
    ${EMULATOR_SRC}
    ${MEMORY_SRC}
    ${MEMORY_MANAGER_SRC}
    ${DEVICE_SRC}
    ${PROCESSOR_SRC}
    ${UTILS_SRC}
)

add_executable(${PROJECT_NAME} ${SOURCES})
