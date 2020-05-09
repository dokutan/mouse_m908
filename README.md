# mouse_m908
Control the Redragon M908 Impact gaming mouse from Linux, BSD and Haiku

**Disclaimer: This software is not supported by the manufacturer of the hardware in any way, and relies completely on information from reverse-engineering. There is no warranty, especially in case of damage to the hardware.**

## Status
All settings from the official software are implemented, except repeating macros, which seems to be broken in the official software and is therefore currently disabled in this program.
As a result there will be no changes to this program, unless I overlooked some features or find a bug.

The mouse has a VID of 0x04d9 and PID of 0xfc4d, if you have a compatible device sold under a different name, or with a different VID or PID, please let me know so the readme can be updated.

## Installing

### Linux
- Install the dependencies:
  - libusb
- Clone this repo or download a release and run
```
make
sudo make install
```
- Restart to get userspace access to the mouse via the installed udev rule
- Uninstall with
```
sudo make uninstall
```

### OpenBSD

- Install dependencies: libusb1
- Clone this repo and compile with
```
make CC=clang++
```
- Run with ``./mouse_m908`` or optionally copy the files to the correct places (take a look at ``make install``)
- The --kernel-driver option is required

### Haiku

- Install dependencies: libusb and libusb_devel
- Clone this repo and compile with
```
make
```
- Run with ``./mouse_m908``
- The --kernel-driver option is required

### Other platforms

Other platforms are not tested, however as long as the dependencies are available there is no special reason they should not be compatible.

## Usage
The settings are stored in a file and applied all at once (except macros, see below). See example.ini and keymap.md

- Apply the example configuration:
``
mouse_m908 -c example.ini
``
- Read the configuration from the mouse and store it in config.ini:
``
mouse_m908 -R > config.ini
``
- Set active profile to number 3:
``
mouse_m908 -p 3
``
- Get usage info:
``
mouse_m908 -h
``
- Send macro example.macro to slot 1:
``
mouse_m908 -m example.macro -n 1
``

### Macros

There is space for 15 macros on the mouse, these are shared over all profiles. Each macro can hold up to 34 actions. To set a macro to a specific button:
1. Create a file containing the macro actions
2. Add macro⟨N⟩ to the button mapping configuration to set a button to the ⟨N⟩th macro
3. Apply the configuration: mouse_m908 -c ⟨config.ini⟩
4. Apply the specific macro: mouse_m908 -m ⟨macrofile⟩ -n ⟨N⟩
#### Macro file
Each line contains an action and a parameter separated by a tab. Supported actions are:
- down	⟨key⟩
- up	⟨key⟩
- delay ⟨1-255⟩

example.macro for an example, keymap.md section Keyboard keys/Keys for a list of recognized Keys. Supported mousebuttons (up and down):
- mouse_left
- mouse_right
- mouse_middle

### --bus and --device options

With these options the USB bus id and device number can be specified. This is useful if there are multiple devices with the same vendor and product id, or if the particular device has a different vendor or product id that is not expected by this software.

### --kernel-driver option

On some systems libusb might not be able to detect or detach kernel drivers, this results in a failure because the mouse can not be opened. This options skips this step.

## License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
