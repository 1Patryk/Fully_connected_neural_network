cmake_minimum_required(VERSION 3.1)

project(FirstProject VERSION 0.1 LANGUAGES CXX )

set(SOURCES
	Include/Fully_connected_network.hpp
	Include/pbPlots.hpp
	Include/Read_BMP.hpp
	Include/supportLib.hpp
	Include/Windows.hpp
	Src/main.cpp
	Src/Fully_connected_network.cpp
	Src/pbPlots.cpp
	Src/Read_BMP.cpp
	Src/supportLib.cpp
	Src/Windows.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})