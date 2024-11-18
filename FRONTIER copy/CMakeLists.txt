# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly

cmake_minimum_required(VERSION 3.16)

# Include ESP-IDF project definition
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Add extra components directories (e.g., tinyshm)
list(APPEND EXTRA_COMPONENT_DIRS "${CMAKE_SOURCE_DIR}/tinyshm")

# Define the project name
project(ESP32)
