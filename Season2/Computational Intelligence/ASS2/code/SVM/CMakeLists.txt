cmake_minimum_required(VERSION 3.16)
project(SVM)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SVM
        svm.cpp
        svm.h
        main.cpp)
