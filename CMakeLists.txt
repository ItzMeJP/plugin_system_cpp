cmake_minimum_required(VERSION 3.16)
project(plugin_test_v1
        VERSION 01.07.2021
        DESCRIPTION
        "Implementation of a calculator using Plugin API")

set(CMAKE_C_COMPILER "gcc-10")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")
set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)

get_filename_component(CURRENT_DIR ./ ABSOLUTE)

set (INSTALL_PLUGIN_SYSTEM_MANAGEMENT_IN_ROOT True)
set(PLUGINS_DIR_FOLDER ${CURRENT_DIR}/plugins)

#message(${PLUGINS_DIR_FOLDER})

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
        include
        include/plugin_system_management
)

## Declare a C++ library

# Main lib definition
add_library(plugin_system_management SHARED #Shared is to export it latter
        src/plugin_system_management/plugin_system_management.cpp
        src/plugin_system_management/factory.cpp
        src/plugin_system_management/plugin.cpp
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
        plugin_system_management
        sum # REMOVE THIS TO PLUGIN TESTS
        multiplication # REMOVE THIS TO PLUGIN TESTS
        division
        subtraction
        )

target_link_libraries(plugin_system_management
        dl
        )

# To export the lib and install it

set_target_properties(plugin_system_management PROPERTIES
        #VERSION ${PROJECT_VERSION}
        PUBLIC_HEADER "include/plugin_system_management/plugin_system_management.h;include/plugin_system_management/factory.h"
        PRIVATE_HEADER "include/plugin_system_management/plugin.h;include/plugin_system_management/interfaces.h"
        )

target_include_directories(plugin_system_management PRIVATE ./include/)

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
configure_file(ConfigFiles/plugin_system_management.pc.in plugin_system_management.pc @ONLY)

install(TARGETS sum subtraction multiplication division
        LIBRARY DESTINATION ${PLUGINS_DIR_FOLDER}
        PUBLIC_HEADER DESTINATION ${CMAKE_BINARY_DIR}/public_headers
        )

install(FILES ${CMAKE_BINARY_DIR}/sum.pc
        ${CMAKE_BINARY_DIR}/subtraction.pc
        ${CMAKE_BINARY_DIR}/multiplication.pc
        ${CMAKE_BINARY_DIR}/division.pc
        DESTINATION ${CMAKE_BINARY_DIR}/pkgconfig)


if(${INSTALL_PLUGIN_SYSTEM_MANAGEMENT_IN_ROOT})
    MESSAGE(">>>>> The plugin_system_management is set to be installed in root. Use sudo to install." )
    install(TARGETS plugin_system_management
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/plugin_system_management
            PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/plugin_system_management)

    install(FILES ${CMAKE_BINARY_DIR}/plugin_system_management.pc
            DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

else()
    # Installing plugin_system_management locally
    MESSAGE(">>>>> The plugin_system_management is set to be installed locally." )
    install(TARGETS plugin_system_management
            LIBRARY DESTINATION ${CMAKE_BINARY_DIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_BINARY_DIR}/public_headers)

    install(FILES ${CMAKE_BINARY_DIR}/plugin_system_management.pc
            DESTINATION ${CMAKE_BINARY_DIR}/pkgconfig)
endif()







## Define an executable
add_executable(calculator_app src/main.cpp)

## Define the executable dependencies
target_link_libraries(calculator_app
        calculator
        )