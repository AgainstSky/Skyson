cmake_minimum_required(VERSION 3.20)
project(Skyson)

set(CMAKE_CXX_STANDARD 14)

add_executable(Skyson main.cpp JsonToken.h  JsonObject.cpp JsonObject.h Skyson.cpp Skyson.h)
