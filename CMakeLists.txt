cmake_minimum_required(VERSION 3.20)
project(cman VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Add the include folder so you can do #include <mytool/App.hpp>
include_directories(include)

#2.Gather all your source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 3. Create the executable
add_executable(cman ${SOURCES})

# 4. Setup Tests 
# enable_testing()
# add_subdirectory(tests)

