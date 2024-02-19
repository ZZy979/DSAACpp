cmake_minimum_required(VERSION 3.24)
project(DSAACpp)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
include(testing.cmake)

include_directories(${CMAKE_SOURCE_DIR})  # 头文件包含可相对于根目录
if(MSVC)
  add_compile_options(/utf-8)
endif()

add_subdirectory(ADT)
file(GLOB CHAPTERS RELATIVE ${CMAKE_SOURCE_DIR} ch*)
foreach(c IN ITEMS ${CHAPTERS})
  add_subdirectory(${c})
endforeach()
