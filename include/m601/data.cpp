/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

/*
 * This file contains internal constants and lookup tables
 */

#include "../rd_mouse.h"

const std::string mouse_m601::_c_name = "601";

// usb device vars
const uint16_t mouse_m601::_c_mouse_vid = 0x258a;
const uint16_t mouse_m601::_c_mouse_pid = 0x1007;

// Names of the physical buttons, TODO!
std::map< int, std::string > mouse_m601::_c_button_names = {
	{ 0, "button_left" },
	{ 1, "button_right" },
	{ 2, "button_middle" },
	{ 3, "button_forward" },
	{ 4, "button_backward" },
	{ 5, "button_dpi" },
	{ 6, "button_lightmode" },
	{ 7, "scroll_up" },
	{ 8, "scroll_down" } };

// Mapping of real DPI values to bytecode
std::map< unsigned int, std::array<uint8_t, 2> > mouse_m601::_c_dpi_codes = {
	{ 100, {0x02, 0x00} },
	{ 200, {0x04, 0x00} },
	{ 300, {0x06, 0x00} },
	{ 400, {0x08, 0x00} },
	{ 500, {0x0b, 0x00} },
	{ 600, {0x0d, 0x00} },
	{ 700, {0x0f, 0x00} },
	{ 800, {0x12, 0x00} },
	{ 900, {0x14, 0x00} },
	{ 1000, {0x16, 0x00} },
	{ 1100, {0x19, 0x00} },
	{ 1200, {0x1b, 0x00} },
	{ 1300, {0x1d, 0x00} },
	{ 1400, {0x20, 0x00} },
	{ 1500, {0x22, 0x00} },
	{ 1600, {0x24, 0x00} },
	{ 1700, {0x27, 0x00} },
	{ 1800, {0x29, 0x00} },
	{ 1900, {0x2b, 0x00} },
	{ 2000, {0x2e, 0x00} },
	{ 2100, {0x30, 0x00} },
	{ 2200, {0x32, 0x00} },
	{ 2300, {0x34, 0x00} },
	{ 2400, {0x37, 0x00} },
	{ 2500, {0x39, 0x00} },
	{ 2600, {0x3b, 0x00} },
	{ 2700, {0x3e, 0x00} },
	{ 2800, {0x40, 0x00} },
	{ 2900, {0x42, 0x00} },
	{ 3000, {0x45, 0x00} },
	{ 3100, {0x47, 0x00} },
	{ 3200, {0x49, 0x00} },
	{ 3300, {0x4c, 0x00} },
	{ 3400, {0x4e, 0x00} },
	{ 3500, {0x50, 0x00} },
	{ 3600, {0x53, 0x00} },
	{ 3700, {0x55, 0x00} },
	{ 3800, {0x57, 0x00} },
	{ 3900, {0x5a, 0x00} },
	{ 4000, {0x5c, 0x00} },
	{ 4100, {0x5e, 0x00} },
	{ 4200, {0x61, 0x00} },
	{ 4300, {0x63, 0x00} },
	{ 4400, {0x65, 0x00} },
	{ 4500, {0x68, 0x00} },
	{ 4600, {0x6a, 0x00} },
	{ 4700, {0x6c, 0x00} },
	{ 4800, {0x6f, 0x00} },
	{ 4900, {0x71, 0x00} },
	{ 5000, {0x73, 0x00} },
	{ 5200, {0x3b, 0x01} },
	{ 5400, {0x3e, 0x01} },
	{ 5600, {0x40, 0x01} },
	{ 5800, {0x42, 0x01} },
	{ 6000, {0x45, 0x01} },
	{ 6200, {0x47, 0x01} },
	{ 6400, {0x49, 0x01} },
	{ 6600, {0x4c, 0x01} },
	{ 6800, {0x4e, 0x01} },
	{ 7000, {0x50, 0x01} },
	{ 7200, {0x53, 0x01} }
};

//usb data packets
