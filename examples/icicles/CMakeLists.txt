add_executable(icicles
        icicles.cpp
        )
        
target_link_libraries(icicles pico_stdlib pico_neopixel)
        pico_enable_stdio_usb(icicles 1)
        pico_enable_stdio_uart(icicles 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(icicles)
