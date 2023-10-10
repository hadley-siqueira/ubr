cmake_minimum_required(VERSION 2.8)
project(ubr_assembler)

include_directories(src/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(ASSEMBLER_SRC
    assembler/assembler.cc
    binary_output/binary_output.cc
    command/command.cc
    align_directive/align_directive.cc
    data_directive/data_directive.cc
    instruction/instruction.cc
    label/label.cc
    module/module.cc
    parser/parser.cc
    scanner/scanner.cc
    section/section.cc
    symbol/symbol.cc
    symbol_table/symbol_table.cc
    token/token.cc
    value/value.cc
)

set(SOURCES
    main.cc
    ${ASSEMBLER_SRC}
)

add_executable(${PROJECT_NAME} ${SOURCES})
