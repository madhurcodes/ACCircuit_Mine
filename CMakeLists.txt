cmake_minimum_required(VERSION 3.6)
project(ACCircuit)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES myheader.h parser.tab.h multigraph.c parser.tab.c  lex.yy.c   main.c)
add_executable(ACCircuit ${SOURCE_FILES})