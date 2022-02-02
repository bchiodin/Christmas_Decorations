add_executable(christmas
        christmas.cpp
        )
        
target_link_libraries(christmas pico_stdlib pico_neopixel)
        pico_enable_stdio_usb(christmas 1)
        pico_enable_stdio_uart(christmas 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(christmas)
