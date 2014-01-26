project(equation_parser)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

set (HEADERS
 ./calc.h
 ./grammar.h
 ./node.h
 ./ast.h
 ./operators.h
)


#add_subdirectory(gauss)

include_directories(.)

source_group ("Header Files" FILES ${HEADERS})

add_executable(${PROJECT_NAME} ${HEADERS} ${SRC_LIST})

