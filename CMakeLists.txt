cmake_minimum_required (VERSION 2.6)
project (Jarbash)
add_executable(jarbash src/main.cpp)
target_link_libraries(jarbash ncursesw cdk panel) 
