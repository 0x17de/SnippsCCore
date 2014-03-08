cmake_minimum_required(VERSION 2.8)

project(SnippsCCore)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib")

find_library(sqlite sqlite3 REQUIRED)

file(GLOB src src/*.c src/*.h)
include_directories(${sqlite_path})
add_library(SnippsCCore ${src})
target_link_libraries(SnippsCCore ${sqlite})

file(GLOB srcTest test/*.c test/*.h)
include_directories(src)
add_executable(SnippsCCoreTest ${srcTest})
target_link_libraries(SnippsCCoreTest SnippsCCore)

