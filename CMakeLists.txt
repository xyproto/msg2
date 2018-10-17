cmake_minimum_required(VERSION 3.12)
project(msg2)

# Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Os -pipe -fPIC -fno-plt -fstack-protector-strong -Wall -Wshadow -pedantic -Wno-parentheses -Wfatal-errors")

# Add source files
add_executable(msg2 main.cpp)

# Prepare an installation target
install (TARGETS msg2 DESTINATION bin)
