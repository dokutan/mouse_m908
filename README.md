# mouse_m908
Control the Redragon M908 Impact gaming mouse from Linux, BSD and Haiku

**Disclaimer: This software is not supported by the manufacturer of the hardware in any way, and relies completely on information from reverse-engineering. There is no warranty, especially in case of damage to the hardware.**

## Status
For the M908: All settings from the official software are implemented, except repeating macros, which seems to be broken in the official software and is therefore currently disabled in this program.

### Supported mice
Name | Support | VID:PID
---|---|---
M908 | complete | 0x04d9:0xfc4d
M709 | experimental | 0x04d9:0xfc2a

If you have a compatible device sold under a different name, or with a different VID or PID, please let me know so the readme can be updated.

## Installing

### Linux
- Install the dependencies:
  - libusb (On some distributions (e.g. Ubuntu) a dev package is required)
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

### OpenBSD and FreeBSD

- Install dependencies:
	- OpenBSD: libusb1
	- FreeBSD: pkgconf
- Clone this repo and compile with
```
make CC=clang++
```
- Install with: (run as root)
```
make install-bsd
```
- OpenBSD: The --kernel-driver option is required
- FreeBSD: Running as root is required, however if you know how to fix this please let me know
- Uninstall with:
```
make uninstall
```

### Haiku

- Install dependencies: libusb and libusb_devel (from the HaikuPorts repo)
- Clone this repo and compile with
```
make
```
- Run with ``./mouse_m908`` or build a .hpkg package for installation with
```
make hpkg
```
- This should create a file named mouse_m908.hpkg in the Haiku directory. The .hpkg package can be installed with HaikuDepot.
- The --kernel-driver option is required

### Other platforms

Other platforms are not tested, however as long as the dependencies are available there is no special reason they should not be compatible. If you (tried) to compile on a platform that is not listed above, please report your results so this file can be updated (and potential bugs can be fixed).

## Usage
The settings are stored in a file and applied all at once (except macros, see below). See examples/example_m*.ini and keymap.md

- Apply the example configuration:
``
mouse_m908 -c examples/example_m908.ini
``
- For any model ecept the M908, use the ``--model`` option, e.g. for the M709
``
mouse_m908 -c examples/example_m709.ini -M 709
``
- Read the configuration from the mouse and store it in config.ini:
``
mouse_m908 -R config.ini
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
mouse_m908 -m examples/example.macro -n 1
``
- Send all macros from example_m908.ini:
``
mouse_m908 -m examples/example_m908.ini
``

### Macros

There is space for 15 macros on the mouse, these are shared over all profiles. Each macro can hold up to 67 actions, any further actions get ignored.

There are two file formats in which macros can be specified, one macro per file (the older type) and multiple macros as comments in the config.ini file (as produced by ``mouse_m908 --read``).

To set a macro to a specific button:
1. Create a file containing the macro actions
2. Add macro⟨N⟩ to the button mapping configuration to set a button to the ⟨N⟩th macro
3. Apply the configuration: ``mouse_m908 -c ⟨config.ini⟩``
4. Depending on the file format:
	- older type: Apply the specific macro: ``mouse_m908 -m ⟨macrofile⟩ -n ⟨N⟩``
	- newer type: Apply all macros: ``mouse_m908 -m ⟨config.ini⟩``

#### Macro file
Each line contains an action and a parameter separated by a tab. Supported actions are:
- down	⟨key⟩
- up	⟨key⟩
- delay ⟨1-255⟩

examples/example.macro for an example of the older file format, examples/example_m*.ini for an example of the newer format, keymap.md section Keyboard keys/Keys for a list of recognized Keys. Supported mousebuttons (up and down):
- mouse_left
- mouse_right
- mouse_middle

### --bus and --device options

With these options the USB bus id and device number can be specified. This is useful if there are multiple devices with the same vendor and product id, or if the particular device has a different vendor or product id that is not expected by this software.

### --kernel-driver option

On some systems libusb might not be able to detect or detach kernel drivers, this results in a failure because the mouse can not be opened. This options skips this step.

## License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
