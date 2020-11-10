# mouse_m908
Control Redragon gaming mice from Linux, BSD and Haiku

**Disclaimer: This software is not supported by the manufacturer of the hardware in any way, and relies completely on information from reverse-engineering. There is no warranty, especially in case of damage to the hardware.**

- [Status](#status)
	- [Supported mice](#supported-mice)
	- [Generic support](#generic-support)
- [Installing](#installing)
	- [Linux](#linux)
	- [OpenBSD and FreeBSD](#openbsd-and-freebsd)
	- [Haiku](#haiku)
	- [Other platforms](#other-platforms)
- [Usage](#usage)
	- [Macros](#macros)
		- [Macro file](#macro-file)
	- [--bus and --device options](#--bus-and---device-options)
	- [--kernel-driver option](#--kernel-driver-option)
- [License](#license)

## Status
All known settings from the official software are implemented for the M908. The other mice have varying levels of support.

### Supported mice
If you have a mouse with VID 0x04d9 that is not listed below, there is a good chance that it is easy to add support. Please open an issue for that.

Name | Support | VID:PID | Additional notes
---|---|---|---
Redragon M908 Impact | complete | 0x04d9:0xfc4d | 
Redragon M709 Tiger | experimental | 0x04d9:0xfc2a | See [this issue](https://github.com/dokutan/mouse_m908/issues/1)<br>- Changing the profile works<br>- Changing the settings is untested<br>- Macros are untested<br>- Reading the settings is not properly implemented due to a lack of data
Redragon M711 Cobra (FPS) | experimental | 0x04d9:0xfc30 | See [this issue](https://github.com/dokutan/mouse_m908/issues/2)<br>- Nothing is tested<br>- Implemented: led color, mode, brightness and speed, changing profiles, macros, reading settings<br>- No usb capture available, therefore missing: button mapping, dpi, scrollspeed, usb poll rate
Redragon M715 Dagger | experimental | 0x04d9:0xfc39 | Nothing is tested<br>- The device specific code is copied from the M711 and mostly unmodified
Redragon M990 Legend | generic | 0x04d9:0xfc41 | [please read this](#generic-support)
Redragon M719 Invader | generic | 0x04d9:0xfc4f | [please read this](#generic-support)
Redragon M802 Titanoboa 2 | generic | 0x04d9:0xfc42 | [please read this](#generic-support)
Redragon 2858 (?) | generic | 0x04d9:0xfc5e | [please read this](#generic-support)
Redragon 2805 (?) | generic | 0x04d9:0xfc58 | [please read this](#generic-support)
Redragon 2850 (?) | generic | 0x04d9:0xfc61 | [please read this](#generic-support)
Redragon M901 Perdition (3) | generic | 0x04d9:0xfc40 | [please read this](#generic-support)
Redragon M801 Mammoth | generic | 0x04d9:0xfc56 | [please read this](#generic-support)
Redragon M910 Ranger | generic | 0x04d9:0xfc49 | [please read this](#generic-support)
Redragon M998-RGB<br>Redragon M808-RGB | generic | 0x04d9:0xfc5f | [please read this](#generic-support)
Redragon M607 Griffin | generic | 0x04d9:0xfc38 | [please read this](#generic-support)
Redragon (?) | generic | 0x04d9:0xfc3f | [please read this](#generic-support)

If you have a mouse with experimental support, your help is needed to improve this software. Please report your results (working and non-working software).

### Generic support
If your mouse is listed as having generic support:
- Nothing is known about this mouse, no specific code has been written
- Please expect nothing beyond changing the active profile (other features might work if you are lucky)
- **Please open an issue to add complete support**

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
- To explicitly state which mouse to open, use the ``--model`` option, e.g. for the M709
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
- move_left	⟨1-120⟩
- move_right	⟨1-120⟩
- move_up	⟨1-120⟩
- move_down	⟨1-120⟩

examples/example.macro for an example of the older file format, examples/example_m*.ini for an example of the newer format, keymap.md section Keyboard keys/Keys for a list of recognized Keys. Supported mousebuttons (up and down):
- mouse_left
- mouse_right
- mouse_middle
- mouse_forward
- mouse_backward

### --bus and --device options

With these options the USB bus id and device number can be specified. This is useful if there are multiple devices with the same vendor and product id, or if the particular device has a different vendor or product id that is not expected by this software.

### --kernel-driver option

On some systems libusb might not be able to detect or detach kernel drivers, this results in a failure because the mouse can not be opened. This options skips this step.

## License
This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.
