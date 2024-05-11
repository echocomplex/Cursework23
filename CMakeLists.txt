CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

PROJECT(Cursework)

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(src/headers)

ADD_EXECUTABLE(
    Cursework src/main.cpp
    src/List.hpp
    src/Cursework.cpp
    src/Cursework.hpp
    src/Student.hpp
    src/Student.cpp
)