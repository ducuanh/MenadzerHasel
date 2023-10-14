cmake_minimum_required(VERSION 3.22)
project(DinhDucAnh)

set(CMAKE_CXX_STANDARD 20)

add_executable(DinhDucAnh main.cpp category.cpp category.h IOhandler.cpp IOhandler.h password.cpp password.h manager.cpp manager.h)
