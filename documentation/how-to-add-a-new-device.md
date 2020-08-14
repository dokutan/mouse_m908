# How to add support for a new device
This document contains a list of thing that need to be changed or added when adding a new device.

- New class for the device (mouse_m*) inherited form rd_mouse, copy an existing include/m* directory to get started
- main program (mouse_m908.cpp):
	- new model
- include/rd_mouse.h
	- #include new header file
- include/rd_mouse.cpp
	- rd_mouse::detect()
- makefile
	- Add new m* target
- udev rules
- documentation:
	- README (supported models)
	- manpage (supported models)
	- help message (supported models)
	- Haiku/.PackageInfo (supported models)
	- create new config in examples/
