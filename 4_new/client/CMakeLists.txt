cmake_minimum_required(VERSION 3.2)
project(ChatClient CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SrcFiles "${PROJECT_SOURCE_DIR}/src/*.cpp")

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/share)

add_executable(ChatClient ${SrcFiles})