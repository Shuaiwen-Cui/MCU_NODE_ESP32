# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/shuaiwencui/esp/v5.3/esp-idf/components/bootloader/subproject"
  "/Volumes/Shaun-MSSD/Github_Repo/MCU_NODE_ESP32/ESP_IDF/ESP32-S3-DevKitC-1/myproject/build/bootloader"
  "/Volumes/Shaun-MSSD/Github_Repo/MCU_NODE_ESP32/ESP_IDF/ESP32-S3-DevKitC-1/myproject/build/bootloader-prefix"
  "/Volumes/Shaun-MSSD/Github_Repo/MCU_NODE_ESP32/ESP_IDF/ESP32-S3-DevKitC-1/myproject/build/bootloader-prefix/tmp"
  "/Volumes/Shaun-MSSD/Github_Repo/MCU_NODE_ESP32/ESP_IDF/ESP32-S3-DevKitC-1/myproject/build/bootloader-prefix/src/bootloader-stamp"
  "/Volumes/Shaun-MSSD/Github_Repo/MCU_NODE_ESP32/ESP_IDF/ESP32-S3-DevKitC-1/myproject/build/bootloader-prefix/src"
  "/Volumes/Shaun-MSSD/Github_Repo/MCU_NODE_ESP32/ESP_IDF/ESP32-S3-DevKitC-1/myproject/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Volumes/Shaun-MSSD/Github_Repo/MCU_NODE_ESP32/ESP_IDF/ESP32-S3-DevKitC-1/myproject/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Volumes/Shaun-MSSD/Github_Repo/MCU_NODE_ESP32/ESP_IDF/ESP32-S3-DevKitC-1/myproject/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
