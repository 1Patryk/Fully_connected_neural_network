cmake_minimum_required(VERSION 3.16)

project(NeuralNetwork VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(NeuralNetwork
	Src/main.cpp
	Src/Fully_connected_network.cpp
)

target_link_libraries(NeuralNetwork PRIVATE Qt6::Widgets)