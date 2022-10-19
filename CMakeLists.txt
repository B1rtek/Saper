cmake_minimum_required(VERSION 3.04)
project(Saper)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    add_executable(Saper mainWindows.cpp)
else()
    add_executable(Saper mainLinux.cpp)
    target_link_libraries(Saper PRIVATE -lcurses)
endif()
