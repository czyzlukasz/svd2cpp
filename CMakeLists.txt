cmake_minimum_required(VERSION 3.10)
project(svd2cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(Src)
include_directories(cxxopts/include)
include_directories(tinyxml2)

add_library(ClassBuilder Src/ClassBuilder.cpp)
add_library(Builders Src/Builders.cpp)
add_library(XmlParser Src/XmlParser.cpp)
add_library(tinyxml2 tinyxml2/tinyxml2.cpp)

add_executable(svd2cpp Src/main.cpp)
target_link_libraries(svd2cpp ClassBuilder Builders XmlParser tinyxml2)