cmake_minimum_required(VERSION 3.31)
project(WindowsOptimizer)

set(CMAKE_CXX_STANDARD 23)

add_executable(WindowsOptimizer main.cpp
        Optimizations/Profiles.cpp
        Optimizations/Tasks/SetRegistries.cpp
        Optimizations/Util/TemplateParser.cpp
        Optimizations/Tasks/DisableServices.cpp
)
