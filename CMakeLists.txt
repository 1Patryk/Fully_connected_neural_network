cmake_minimum_required(VERSION 3.1)

project(FirstProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	Include/Fully_connected_network.hpp
	Src/main.cpp
	Src/Fully_connected_network.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})