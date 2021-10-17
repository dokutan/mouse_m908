# How to add support for a new device
This document contains a list of thing that need to be changed or added when adding a new device.

- New class for the device (mouse\_m\*) inherited from rd\_mouse, copy an existing include/m\* directory to get started
- include/rd\_mouse.h
	- class declaration (at the top)
	- mouse\_variant typedef
	- #include new header file (at the bottom)
- makefile
	- Add new m\* target
- CMakeLists.txt
	- Add new files to target_sources
- documentation:
	- README (supported models)
	- create new config in examples/
