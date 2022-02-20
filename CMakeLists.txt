cmake_minimum_required(VERSION 3.21)
project(assignment_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(assignment_3
        AnubroluProcessor.c
        BMPHandler.c
        BMPHandler.h
        Image.c
        Image.h
        test2.bmp
        ttt.bmp
        wb.bmp)
