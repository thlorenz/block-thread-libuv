cmake_minimum_required(VERSION 3.9)

project(block_thread)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -g")
set(CMAKE_*_LINKER_FLAGS " -v ${UV_LIB}")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/../deps/uv/include)

file(GLOB main_headers ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB main_sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB uv_headers ${PROJECT_SOURCE_DIR}/../deps/uv/include/*.h)
file(GLOB uv_sources ${PROJECT_SOURCE_DIR}/../deps/uv/*.cc)
file(GLOB uv_unix_sources ${PROJECT_SOURCE_DIR}/../deps/uv/unix/*.cc)

add_executable(block_thread
  ${main_sources} ${main_headers}
  ${uv_sources} ${uv_unix_sources} ${uv_headers}
)

source_group(root FILES ${main_sources} ${main_headers})
source_group(uv FILES ${uv_sources} ${uv_unix_sources} ${uv_headers})
