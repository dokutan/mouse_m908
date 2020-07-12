# Documentation

## Source documentation
Doxygen is used in places for source code documentation. To build the documentation install doxygen and run
```
doxygen Doxyfile
```
A directory named doxygen will be created, containing html and latex files.

## USB Protocol description
This directory contains captured usb data (when sending the default settings). For further details look at the write functions in the source code.

default.txt and default-annotated_m908.pdf contain the extracted usb data when sending the default settings. This was obtained by exporting packet dissections as plain text from wireshark (select only bytes) and running ``grep "00[4-9]0"`` on the exported files.


### Button mapping
The function of each button is described by 4 bytes. In case of the fire button all 4 bytes are used, in all other cases the last byte is 0x00. Look at ``set_key_mapping()`` (include/setters.cpp) and include/data.cpp for the full meaning of these bytes.

A few are listed below:
- Keyboard key:
	0. = 0x90 if without modifiers, = 0x8f if with modifiers
	1. modifier value (sum of individual modifer values)
	2. keycode
	3. = 0x00
- Media keys:
	0. = 0x8e
	1. = 0x01
	2. keycode
	3. = 0x00
- Fire button:
	0. = 0x99
	1. keycode
	2. repeats
	3. delay
- Macro:
	0. = 0x91
	1. macro number (0x0-0xe)
	2. 0x01
	3. 0x00
- No function (none)
	all bytes = 0x00
