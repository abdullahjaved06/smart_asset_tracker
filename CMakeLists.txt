# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

target_sources(app PRIVATE src/main.c)

# Add the component DISPLAY
target_sources(app PRIVATE
    components/ILI9341_display/ili9341_display.c)
target_include_directories(app
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/components/ILI9341_display
)

# Add the component LIS2DH
target_sources(app PRIVATE
    components/lis2dh/lis2dh.c)
target_include_directories(app
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/components/lis2dh
)

# Add the component LIS2DH
target_sources(app PRIVATE
    components/sht4x/sht4x.c)
target_include_directories(app
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/components/sht4x
)