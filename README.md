# Adafruit NeoPixel Library for Pi PICO C/C++ SDK

Port of the Adafruit Library to PI PICO in a C/C++ SDK environment.
Build according to SDK standards as an INTERFACE library

Friendly usage of pio statemachine implementations: Any neopixels object seizes sm and pio program space in a friendly cooperative way 

The library can be found at pico-neopixels subdirectory. In your project you should include that subdirector, and adapt your project Makefile by using the commands "add_subdirectory" and by adding pico_neopixels to the libraries of your project (see the examples "simple" and "strandtest_wheel" for examples. 

## Installation

do <code>git clone "https://github.com/martinkooij/pi-pico-adafruit-neopixels"</code>

If the PICO SDK is installed according to the guidelines on the raspberry pi pico site the following should work:

````
cd pi-pico-adafruit-nexopixels/example
mkdir build && cd build
cmake ..
make
````
or on windows
````
cd pi-adafruit-neopixels/example
mkdir build && cd build
cmake .. -G "NMake Makefiles"
nmake
````

## Library documentation

See the Adafruit Neopixel library documentation on the various resources. Note that the <code>begin()</code> method is only kept for compatibility reasons but has no effect. On the pico a dedicated pio statemachine is seized and started at the very first <code>show()</code> command of the object. 

The examples that work are "simple", "strandtest_wheels" and .... for the owner of the Maker Pi PICO board of Cytron the xample e"onboard_cytron" that gives a nice colorful show on the built in neopixel (a strand of length 1 on PIN 28). 

## Resources (specific to the pico port)
Each object seizes a pio/sm pair at the moment of the first call to the "show" method. It uses the SDK calls <code>pio_claim_unused_sm</code>, <code>pio_can_add_program</code> to find unused statemachines and unused instruction space on the pio's. 

In the destructor the library releases the claimed resources (the sm, and if no other statemachine are using it anymore also removes the program instruction space on the designated pio by using <code>pio_remove_program</code>, if there are no other sm serving neopixel objects on that pio). 

The destructor is called if called explicitlky when the object was constructed with "new" or implicitly when it goes out of scope in a function. These are all quite special cases. When defined before main it will not go out of scope in the programming lifetime. This would be the normal use case. 

There is a maximum of 8 neopixel strands, if pio and sm's are not used for any other purposes in your project. Strands can be assigned to any GPIO pin of the pico. 

## Releases
V0.9.0 Pre-release. Examples simple & strandtest_wheels are compiling and confirmed working. Some documentation work needed to promote to a proper release. 
