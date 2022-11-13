cmake_minimum_required(VERSION 3.2)
project(ChatServer CXX)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SrcFiles "${PROJECT_SOURCE_DIR}/src/*.cpp")

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/share)

add_executable(ChatServer ${SrcFiles})