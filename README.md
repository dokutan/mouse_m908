# mouse_m908
Control the Redragon M908 Impact gaming mouse from Linux

## Installing
- Install the dependencies:
  - libusb
  - boost
- Clone this repo and run
``
sudo make install
``
- Restart to get userspace access to the mouse via the installed udev rule

## Usage
The settings are stored in a file and applied all at once. See example.ini and keymap.md

- Apply the example confiuration:
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

## TODO
Button remapping is not (yet) fully supported: macros --and keyboard keys-- aren't implemented.
