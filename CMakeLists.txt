project (Jarbash)

cmake_minimum_required (VERSION 2.6)

link_directories(/usr/local/lib/)
include_directories(/usr/local/include)
include_directories(src/include/)

add_executable(jarbash src/main.cpp src/http.cpp)
target_link_libraries(jarbash cdk ncursesw panel m curl curlpp)
