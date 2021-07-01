cmake_minimum_required(VERSION 3.16)
project(plugin_test_v1
        VERSION 01.07.2021
        DESCRIPTION
        "Implementation of a calculator using Plugin API")

set(CMAKE_C_COMPILER "gcc-10")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

get_filename_component(CURRENT_DIR ./ ABSOLUTE)
set(PLUGINS_DIR_FOLDER ${CURRENT_DIR}/plugins)

#message(${PLUGINS_DIR_FOLDER})

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
        include
)

## Declare a C++ library

# Main lib definition
add_library(plugin_handling SHARED #Shared is to export it latter
        src/plugin_handling/plugin_handling.cpp
        src/plugin_handling/factory.cpp

        #TODO
        )

add_library(calculator SHARED #Shared is to export it latter
        src/calculator.cpp
        )

# Plugins definitions
add_library(sum SHARED #Shared is to export it latter
        src/plugins/sum.cpp
        )

add_library(subtraction SHARED #Shared is to export it latter
        src/plugins/subtraction.cpp
        )

add_library(multiplication SHARED #Shared is to export it latter
        src/plugins/multiplication.cpp
        )

add_library(division SHARED #Shared is to export it latter
        src/plugins/division.cpp
        )

## Set dependencies of the library

target_link_libraries(sum
        )
target_link_libraries(subtraction
        )
target_link_libraries(division
        )
target_link_libraries(multiplication
        )

target_link_libraries(calculator
        plugin_handling
        sum # REMOVE THIS TO PLUGIN TESTS
        multiplication # REMOVE THIS TO PLUGIN TESTS
        division
        subtraction
        )

target_link_libraries(plugin_handling
        dl
        )

# To export the lib and install it

set_target_properties(plugin_handling PROPERTIES
        #VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/plugin_handling/plugin_handling.h;include/plugin_handling/interfaces.h"
        )

set_target_properties(sum PROPERTIES
        #VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/plugins/sum.h"
        )

set_target_properties(subtraction PROPERTIES
        #VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/plugins/subtraction.h"
        )

set_target_properties(multiplication PROPERTIES
        #VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/plugins/multiplication.h"
        )

set_target_properties(division PROPERTIES
        #VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/plugins/division.h"
        )

configure_file(ConfigFiles/sum.pc.in sum.pc @ONLY)
configure_file(ConfigFiles/subtraction.pc.in subtraction.pc @ONLY)
configure_file(ConfigFiles/multiplication.pc.in multiplication.pc @ONLY)
configure_file(ConfigFiles/division.pc.in division.pc @ONLY)
configure_file(ConfigFiles/plugin_handling.pc.in plugin_handling.pc @ONLY)

install(TARGETS sum subtraction multiplication division
        LIBRARY DESTINATION ${PLUGINS_DIR_FOLDER}
        PUBLIC_HEADER DESTINATION ${CMAKE_BINARY_DIR}/public_headers
        )

install(TARGETS plugin_handling
        LIBRARY DESTINATION ${CMAKE_BINARY_DIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_BINARY_DIR}/public_headers)

install(FILES ${CMAKE_BINARY_DIR}/sum.pc
              ${CMAKE_BINARY_DIR}/subtraction.pc
              ${CMAKE_BINARY_DIR}/multiplication.pc
              ${CMAKE_BINARY_DIR}/division.pc
              ${CMAKE_BINARY_DIR}/plugin_handling.pc

        #DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig) # TODO: check this validity
        DESTINATION ${CMAKE_BINARY_DIR}/pkgconfig) # TODO: check this validity

#message(${CMAKE_BINARY_DIR})
#message(${CMAKE_INSTALL_DATAROOTDIR})

## Define an executable
add_executable(calculator_app src/main.cpp)

## Define the executable dependencies
target_link_libraries(calculator_app
        calculator
        )
