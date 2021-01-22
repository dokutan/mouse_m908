# How to add support for a new device
This document contains a list of thing that need to be changed or added when adding a new device.

- New class for the device (mouse\_m\*) inherited from rd\_mouse, copy an existing include/m\* directory to get started
- include/rd\_mouse.h
	- class declaration (at the top)
	- mouse\_variant typedef
	- #include new header file
- include/rd\_mouse.cpp
	- rd\_mouse::detect()
- makefile
	- Add new m\* target
- documentation:
	- README (supported models)
	- manpage (supported models)
	- help message (supported models)
	- Haiku/.PackageInfo (supported models)
	- create new config in examples/
