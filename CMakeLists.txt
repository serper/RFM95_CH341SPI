# CH341SPI Project
# Copyright (c) 2025 Sergio Pérez
# Licensed under MIT License (see LICENSE file for details)

cmake_minimum_required(VERSION 3.10)
project(CH341SPI VERSION 1.0)

# Configure compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find libusb
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)
include_directories(${LIBUSB_INCLUDE_DIRS})
link_directories(${LIBUSB_LIBRARY_DIRS})

# Compile the library
file(GLOB LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(ch341_spi_lib STATIC ${LIB_SOURCES})
target_link_libraries(ch341_spi_lib ${LIBUSB_LIBRARIES})

# Compile the RFM95 example
add_executable(rfm95_example "${CMAKE_CURRENT_SOURCE_DIR}/example/rfm95_example.cpp")
target_link_libraries(rfm95_example ch341_spi_lib ${LIBUSB_LIBRARIES})

# Install
install(TARGETS ch341_spi_lib rfm95_example
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# Also install license and headers
install(FILES LICENSE DESTINATION share/doc/ch341spi)
install(DIRECTORY include/ DESTINATION include/ch341spi)