# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


# add_compile_options(-Wall
# -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
# -Wno-unused-function # we have some for the docs that aren't called
# -Wno-maybe-uninitialized
# )

add_subdirectory(arducam_hm01b0)
add_subdirectory(LCD_st7735)

##########################################################

add_executable(example-display-camera
    example-display-camera.c
)

# pull in common dependencies
target_link_libraries(
  example-display-camera
  hardware_pwm
  hardware_pio
  hardware_spi
  hardware_i2c
  pico_stdlib
# add the arducam camera's CMakeLists.txt library
  arducam_hm01b0
# add the arducam display's CMakeLists.txt library
  LCD_st7735

  hardware_dma
  hardware_timer
  hardware_watchdog
  hardware_clocks
)


pico_set_program_name(example-display-camera "example-display-camera")
pico_set_program_version(example-display-camera "0.1")

pico_enable_stdio_uart(example-display-camera 0)
pico_enable_stdio_usb(example-display-camera 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(example-display-camera)

##########################################################

# add_executable(rpico-inversion 
#     rpico-inversion.c
# )

# # pull in common dependencies
# target_link_libraries(
#   rpico-inversion
#   hardware_pwm
#   hardware_pio
#   hardware_spi
#   hardware_i2c
#   pico_stdlib
# # add the arducam camera's CMakeLists.txt library
#   arducam_hm01b0
# # add the arducam display's CMakeLists.txt library
#   LCD_st7735

#   hardware_dma
#   hardware_timer
#   hardware_watchdog
#   hardware_clocks
# )


# pico_set_program_name(rpico-inversion "rpico-inversion")
# pico_set_program_version(rpico-inversion "0.1")

# pico_enable_stdio_uart(rpico-inversion 0)
# pico_enable_stdio_usb(rpico-inversion 1)

# # create map/bin/hex file etc.
# pico_add_extra_outputs(rpico-inversion)