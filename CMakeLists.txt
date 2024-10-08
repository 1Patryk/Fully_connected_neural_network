cmake_minimum_required(VERSION 3.16)

project(NeuralNetwork VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB ALL_SOURCE
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(NeuralNetwork ${ALL_SOURCE})

configure_file(
	${CMAKE_SOURCE_DIR}/NetworkConfig.h.in
	${CMAKE_SOURCE_DIR}/NetworkConfig.h)

install(TARGETS NeuralNetwork RUNTIME DESTINATION Binary)

#include(InstallRequiredSystemLibraries)
#set(CPACK_PACKAGE_VERSION_MAJOR "${NeuralNetwork_VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${NeuralNetwork_VERSION_MINOR}")
#set(CPACK_GENERATOR "TGZ")
#set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
