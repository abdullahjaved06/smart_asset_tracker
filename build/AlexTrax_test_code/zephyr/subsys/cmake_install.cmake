# Install script for directory: /home/abdullah/ncs/v2.9.0/zephyr/subsys

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
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/canbus/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/debug/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/fb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/fs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/ipc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/logging/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/mem_mgmt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/mgmt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/modbus/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/pm/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/portability/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/random/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/rtio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/sd/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/stats/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/storage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/task_wdt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/testsuite/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/tracing/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/usb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/abdullah/Abdullah/Projects/projects/ili9341_display_project/AlexTrax_test_code/build/AlexTrax_test_code/zephyr/subsys/shell/cmake_install.cmake")
endif()

