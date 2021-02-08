# How to add support for a new device
This document contains a list of thing that need to be changed or added when adding a new device.

- New class for the device (mouse\_m\*) inherited from rd\_mouse, copy an existing include/m\* directory to get started
- include/rd\_mouse.h
	- class declaration (at the top)
	- mouse\_variant typedef
	- #include new header file (at the bottom)
- include/rd\_mouse.cpp
	- rd\_mouse::detect() only needs changing for mice that have more than 1 PID (e.g. generic)
- makefile
	- Add new m\* target
- documentation:
	- README (supported models)
	- create new config in examples/
