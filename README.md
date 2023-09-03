# mouse_m908
Control Redragon gaming mice from Linux, BSD and Haiku

**Disclaimer: This software is not supported by the manufacturer of the hardware in any way, and relies completely on information from reverse-engineering. There is no warranty, especially in case of damage to the hardware.**

**This software can make your mouse unusable, read the [safety](#safety) section before using this software.**

- [Status](#status)
	- [Supported mice](#supported-mice)
	- [Generic support](#generic-support)
	- [Safety](#safety)
- [Installing](#installing)
	- [Linux](#linux)
	- [Arch Linux](#arch-linux)
	- [Fedora/RHEL](#fedorarhel)
	- [OpenBSD and FreeBSD](#openbsd-and-freebsd)
	- [Haiku](#haiku)
	- [Other platforms](#other-platforms)
	- [CMake](#cmake)
- [Usage](#usage)
	- [Macros](#macros)
		- [Macro file](#macro-file)
	- [--bus and --device options](#--bus-and---device-options)
	- [--kernel-driver option](#--kernel-driver-option)
- [License](#license)

## Status
All known settings from the official software are implemented for the M908 and M719. The other mice have varying levels of support.

### Supported mice
If you have a mouse with VID 0x04d9 that is not listed below, there is a good chance that it is easy to add support. You can help to improve the support for your mouse by reporting what works and what doesn't, or by capturing the usb communication with the official software. Please open an issue.

The various levels of support mean the following:
- **unsupported :** these mice are not compatible, support could be implemented but this will require more information about the protocol
- **generic :** no code specific to the mouse is written, this exists primarily to test whether the mouse uses a compatible protocol
- **experimental :** a backend specific to the mouse exists, but is untested or has major problems
- **partial :** some features work, others might not or are untested, and there are no known problems making the software unusable
- **complete :** all known features are implemented

Name | Support | VID:PID | Additional notes
---|---|---|---
Redragon M908 Impact<br>Pusat V8 | complete | 0x04d9:0xfc4d | 
Redragon M719 Invader | complete | 0x04d9:0xfc4f | 
Redragon M607 Griffin | partial | 0x04d9:0xfc38 | At least reading the  settings is not working correctly
Redragon M711 Cobra | partial | 0x04d9:0xfc30 | See [this issue](https://github.com/dokutan/mouse_m908/issues/2)
Redragon M711 Cobra FPS | partial | 0x04d9:0xfc30 | DPI values above 10000 are not supported
Redragon M913<br>UtechSmart Venus Pro RGB | partial | 0x25a7:0xfa07<br>0x25a7:0xfa08 | See [this issue](https://github.com/dokutan/mouse_m908/issues/15)<br>- Uses a different and unique protocol<br>- Not all features are implemented
Redragon M686 | experimental | 0x25a7:0xfa34<br>0x25a7:0xfa35 | See [this issue](https://github.com/dokutan/mouse_m908/issues/29)
Redragon M709 Tiger | experimental | 0x04d9:0xfc2a | See [this issue](https://github.com/dokutan/mouse_m908/issues/1)<br>- Changing the profile works<br>- Changing the settings is untested<br>- Macros are untested<br>- Reading the settings is not properly implemented due to a lack of data
Redragon M715 Dagger | experimental | 0x04d9:0xfc39 | Nothing is tested<br>- The device specific code is copied from the M711 and mostly unmodified
Redragon M721-Pro Lonewolf2 | experimental | 0x04d9:0xfc5c | See [this issue](https://github.com/dokutan/mouse_m908/issues/22)<br>Nothing is tested
Redragon M990 Legend | experimental | 0x04d9:0xfc0f | See [this issue](https://github.com/dokutan/mouse_m908/issues/5)<br>This mouse uses a different data format, keycodes, etc.
Redragon M990 Legend (RGB/Chroma) | experimental | 0x04d9:0xfc41 | - Changing the profile works<br>- Reading the settings works partially
Redragon M909 Emperor | generic | 0x04d9:0xfc42 | [please read this](#generic-support)
Redragon M802 Titanoboa 2 | generic | 0x04d9:0xfc42 | [please read this](#generic-support)
Redragon 2858 (?) | generic | 0x04d9:0xfc5e | [please read this](#generic-support)
Redragon 2805 (?) | generic | 0x04d9:0xfc58 | [please read this](#generic-support)
Redragon M612-RGB Predator | generic | 0x04d9:0xfc61 | [please read this](#generic-support)
Redragon M901 Perdition | generic | 0x04d9:0xfc02 | [please read this](#generic-support)
Redragon M901 Perdition (3) | generic | 0x04d9:0xfc40 | [please read this](#generic-support)
Redragon M801 Mammoth (RGB?) | generic | 0x04d9:0xfc56 | [please read this](#generic-support)
Redragon M910 Ranger | generic | 0x04d9:0xfc49 | [please read this](#generic-support)
Redragon M998-RGB<br>Redragon M808-RGB | generic | 0x04d9:0xfc5f | [please read this](#generic-support)
Redragon (?) | generic | 0x04d9:0xfc3f | [please read this](#generic-support)
Redragon M702 Phoenix | unsupported | 0x04d9:0xfc15 | See [this issue](https://github.com/dokutan/mouse_m908/issues/21)<br>Uses a different protocol
Redragon M801 Mammoth | unsupported | 0x04d9:0xfa56 | See [this issue](https://github.com/dokutan/mouse_m908/issues/10)<br>Uses a different protocol


If you have a mouse with experimental support, your help is needed to improve this software. Please report your results (working and non-working software).

### Generic support
If your mouse is listed as having generic support:
- Nothing is known about this mouse, no specific code has been written
- Please expect nothing beyond changing the active profile (other features might work if you are lucky)
- There will be bugs, potentially preventing the mouse from working correctly
- **Please open an issue to add complete support**

### Safety
This software can make your mouse unusable. While this is very unlikely in the case of mice with complete support, all other mice are at a higher risk.
This section lists known problems and ways to fix them.
- **M602A-RGB, M910-K**
  - Issue: changing the the settings on the prevents moving the mouse in the vertical direction
  - Potential solution: use the official software to restore the settings
- **Old versions of this software (fixed in newer versions)**
  - Issue: disabling all DPI levels makes the mouse completely unresponsive
  - Solution: use the official software to restore the settings and use a recent version of this software to prevent this from happening
- **Mice with generic or untested experimental support**
  - Issue: Changing the settings has an increased risk of similar problems as described above
  - Potential solution: have a second mouse and the official software available to restore the settings in case of an issue


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

### Arch Linux
An [AUR package](https://aur.archlinux.org/packages/mouse_m908/) is available for the latest release.

### Fedora/RHEL

RPM Package support was added so you can install `mouse_m908` via your package manager.

- Clone this repo
- Install build dependencies: `dnf builddep mouse_m908.spec` and `dnf install -y rpkg`
- run:
```
make
make rpm
```
- Install the resulting package by running:
```
sudo dnf install ./mouse_m908*.rpm
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

### CMake

You can also use cmake to build mouse_m908 with the following commands:
```
cmake -Bbuild
cmake --build build
cmake --install build
```
Please note that this is currently experimental and only tested on Linux, however the plan is to eventually transition to cmake for all platforms.

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
