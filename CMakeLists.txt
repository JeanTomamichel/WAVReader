#cmake minimum version required 
cmake_minimum_required(VERSION 3.10)

#verbose 
set( CMAKE_VERBOSE_MAKEFILE on )

#project name
project(WAVReader VERSION 0.0.1)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#configure Header File for version number
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Header/WavReaderConfig.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Header/WavReaderConfig.h)

set(SOURCE 
	${CMAKE_CURRENT_SOURCE_DIR}/Source/WavReader.cpp
	)

set(HEADER 
	${CMAKE_CURRENT_SOURCE_DIR}/Header/WavReader.h
	${CMAKE_CURRENT_SOURCE_DIR}/Header/WavReaderConfig.h
	)
	
#add the exectutable 
add_executable(WAVReader ${SOURCE} ${HEADER})

#include target directory for configured file 
target_include_directories(WAVReader PUBLIC 
							"${PROJECT_BINARY_DIR}"
						)

#specify C++ standard 
set(CMAKE_CXX_STANDARD            17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
