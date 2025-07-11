# Install script for directory: /home/abdullah/ncs/v2.9.0/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "MinSizeRel")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/abdullah/ncs/toolchains/b77d8c1312/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/suit-processor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/cmake/reports/cmake_install.cmake")
endif()

