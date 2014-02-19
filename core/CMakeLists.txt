cmake_minimum_required(VERSION 2.8)

PROJECT(turing)

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_LIBRARIES})

set(SOURCE_EXE main.cpp)

set(SOURCE_LIB 
		state.cpp
		command.cpp
		tape.cpp
		console_printer.cpp
		parser.cpp
		program.cpp
	)

add_library(libturing STATIC ${SOURCE_LIB})

add_executable(turing ${SOURCE_EXE})

target_link_libraries(turing libturing ${Boost_LIBRARIES})