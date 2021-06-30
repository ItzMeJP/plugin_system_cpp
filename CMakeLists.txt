cmake_minimum_required(VERSION 3.16)
project(plugin_test_v1
        VERSION 28.06.2021
        DESCRIPTION
        "Implementation of a calculator using Plugin API")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

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
        #TODO
        )

add_library(calculator SHARED #Shared is to export it latter
        src/calculator.cpp
        )

add_library(base_operations SHARED #Shared is to export it latter
        src/base_operations.cpp # polymorphic base class
        )

# Plugins definitions
add_library(sum SHARED #Shared is to export it latter
        src/sum.cpp
        )

add_library(subtraction SHARED #Shared is to export it latter
        src/subtraction.cpp
        )

add_library(multiplication SHARED #Shared is to export it latter
        src/multiplication.cpp
        )

add_library(division SHARED #Shared is to export it latter
        src/division.cpp
        )

## Set dependencies of the library
target_link_libraries(base_operations
        )
target_link_libraries(sum
        base_operations
        )
target_link_libraries(subtraction
        base_operations
        )
target_link_libraries(division
        base_operations
        )
target_link_libraries(multiplication
        base_operations
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
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/plugin_handling/plugin_handling.h;include/plugin_handling/interfaces.h"
        )

set_target_properties(base_operations PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/base_operations.h"
        )

set_target_properties(sum PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/sum.h"
        )

set_target_properties(subtraction PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/subtraction.h"
        )

set_target_properties(multiplication PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/multiplication.h"
        )

set_target_properties(division PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/division.h"
        )

set_target_properties(base_operations PROPERTIES
        VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/base_operations.h"
        )

configure_file(sum.pc.in sum.pc @ONLY)
configure_file(subtraction.pc.in subtraction.pc @ONLY)
configure_file(multiplication.pc.in multiplication.pc @ONLY)
configure_file(division.pc.in division.pc @ONLY)
configure_file(base_operations.pc.in base_operations.pc @ONLY)
configure_file(plugin_handling.pc.in plugin_handling.pc @ONLY)

install(TARGETS sum subtraction multiplication division
        LIBRARY DESTINATION ${PLUGINS_DIR_FOLDER}
        PUBLIC_HEADER DESTINATION ${PLUGINS_DIR_FOLDER}/headers)

install(TARGETS base_operations plugin_handling
        LIBRARY DESTINATION ${PLUGINS_DIR_FOLDER}
        PUBLIC_HEADER DESTINATION ${PLUGINS_DIR_FOLDER}/headers)

install(FILES ${CMAKE_BINARY_DIR}/sum.pc
              ${CMAKE_BINARY_DIR}/subtraction.pc
              ${CMAKE_BINARY_DIR}/multiplication.pc
              ${CMAKE_BINARY_DIR}/division.pc
              ${CMAKE_BINARY_DIR}/base_operations.pc
              ${CMAKE_BINARY_DIR}/plugin_handling.pc

        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig) # TODO: check this validity

#message(${CMAKE_BINARY_DIR})
#message(${CMAKE_INSTALL_DATAROOTDIR})

## Define an executable
add_executable(plugin_test_v1 src/main.cpp)

## Define the executable dependencies
target_link_libraries(plugin_test_v1
        calculator
        )
