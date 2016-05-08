cmake_minimum_required(VERSION 3.3)
project(HtmlToJson)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/libs/json/json/json-forwards.h
    src/libs/json/json/json.h
    src/libs/json/jsoncpp.cpp
    src/ConfigKeys.h
    src/main.cpp
    src/Parser.cpp
    src/Parser.h
    src/ParserUtils.cpp
    src/ParserUtils.h
    src/Path.cpp
    src/Path.h)

add_executable(HtmlToJson ${SOURCE_FILES})