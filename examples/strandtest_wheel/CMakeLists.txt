add_executable(strandtest_wheel
        strandtest_wheel.cpp
        )
        
target_link_libraries(strandtest_wheel pico_stdlib pico_neopixel)
        pico_enable_stdio_usb(strandtest_wheel 1)
        pico_enable_stdio_uart(strandtest_wheel 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(strandtest_wheel)
