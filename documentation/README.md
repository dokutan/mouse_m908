# Documentation

## Source documentation
Doxygen is used in places for source code documentation. To build the documentation install doxygen and run
```
doxygen Doxyfile
```
A directory named doxygen will be created, containing html and latex files.

## USB Protocol description
This directory contains captured usb data (when sending the default settings). For further details look at the write functions in the source code.

default.txt and default-annotated.pdf contain the extracted usb data when sending the default settings. This was obtained by exporting packet dissections as plain text from wireshark (select only bytes) and running ``grep "00[4-9]0"`` on the exported files.


### Button mapping
The function of each button is described by 4 bytes. In case of the fire button all 4 bytes are used, in all other cases the last byte is 0x00. Look at ``set_key_mapping()`` (setters.cpp) and constructor.cpp for the meaning of these bytes.
