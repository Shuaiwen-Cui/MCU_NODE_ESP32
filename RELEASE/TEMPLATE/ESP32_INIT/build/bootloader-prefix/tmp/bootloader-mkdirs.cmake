# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ESP-IDF/v5.3.1/esp-idf/components/bootloader/subproject"
  "E:/DEV/MCU_NODE_ESP32/NODE_DEV/INIT/ESP32_INIT/build/bootloader"
  "E:/DEV/MCU_NODE_ESP32/NODE_DEV/INIT/ESP32_INIT/build/bootloader-prefix"
  "E:/DEV/MCU_NODE_ESP32/NODE_DEV/INIT/ESP32_INIT/build/bootloader-prefix/tmp"
  "E:/DEV/MCU_NODE_ESP32/NODE_DEV/INIT/ESP32_INIT/build/bootloader-prefix/src/bootloader-stamp"
  "E:/DEV/MCU_NODE_ESP32/NODE_DEV/INIT/ESP32_INIT/build/bootloader-prefix/src"
  "E:/DEV/MCU_NODE_ESP32/NODE_DEV/INIT/ESP32_INIT/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/DEV/MCU_NODE_ESP32/NODE_DEV/INIT/ESP32_INIT/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/DEV/MCU_NODE_ESP32/NODE_DEV/INIT/ESP32_INIT/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
