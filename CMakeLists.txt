cmake_minimum_required(VERSION 3.15)
project(code_analyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(analyzer
    src/main.cpp
    src/FileScanner.cpp
    src/CodeParser.cpp
    src/Report.cpp
    src/DuplicateDetector.cpp
    src/ReviewContext.cpp
)
