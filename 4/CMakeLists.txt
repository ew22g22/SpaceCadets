cmake_minimum_required(VERSION 3.2)
project(chat_app CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE src_files "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(chat_app ${src_files})