cmake_minimum_required(VERSION 3.28)
project(OS2_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(OS2_Project Server.cpp
        Client.cpp
)
