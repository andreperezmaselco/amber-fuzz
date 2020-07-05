cmake_minimum_required(VERSION 3.15.3)

project(amber-fuzz VERSION 1.0)

add_executable(amber-fuzz
               amber-fuzz.c
               amber/script.c
               amber/shader.c)

target_include_directories(amber-fuzz PUBLIC "${PROJECT_SOURCE_DIR}")
