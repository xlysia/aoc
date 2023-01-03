cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(helloworld) #name of your project

include_directories(./)
include_directories(./headers)
add_executable(aoc main.cpp ./utils/cvutils.cpp ./utils/md5.cpp)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_compile_options(aoc PRIVATE -Wall -ggdb3)
target_link_libraries(aoc rt ${OpenCV_LIBS})