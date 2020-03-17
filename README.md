# mouse_m908
Control the Redragon M908 Impact gaming mouse from Linux and BSD

## Status
All settings from the official software are implemented, except repeating macros, which seems to be broken in the official software and is therefore currently disabled in this program.
As a result there will be no changes to this program, unless I overlooked some features or find a bug.

## Installing

### Linux
- Install the dependencies:
  - libusb
- Clone this repo or download a release and run
``
make
sudo make install
``
- Restart to get userspace access to the mouse via the installed udev rule
- Upgrade an existing installation with
``
make
sudo make upgrade
``
- Uninstall with
``
sudo make uninstall
``

### OpenBSD

- Install dependencies: libusb1
- Clone this repo and compile with
```
c++ mouse_m908.cpp -o mouse_m908 -Wall -O2 -I/usr/local/include/libusb-1.0 -L/usr/local/lib -lusb-1.0
```
- The --kernel-driver option is required

### Other platforms

Other platforms are not tested, however as long as the dependencies are available there is no special reason they should not be compatible.

## Usage
The settings are stored in a file and applied all at once (except macros, see below). See example.ini and keymap.md

- Apply the example configuration:
``
mouse_m908 -c example.ini
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
