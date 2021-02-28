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

const std::string mouse_m913::_c_name = "913";

// usb device vars
const uint16_t mouse_m913::_c_mouse_vid = 0x25a7;
std::set< uint16_t > mouse_m913::_c_all_pids = {
	0xfa07, // wireless connection
	0xfa08  // wired connection
};

// Names of the physical buttons
std::map< int, std::string > mouse_m913::_c_button_names = {
	{ 0, "button_left" },
	{ 1, "button_right" },
	{ 2, "button_middle" },
	{ 3, "button_fire" },
	//{ 4, "button_dpi_up" }, // not known if remappable
	//{ 5, "button_dpi_down" }, // not known if remappable
	{ 6, "button_1" },
	{ 7, "button_2" },
	{ 8, "button_3" },
	{ 9, "button_4" },
	{ 10, "button_5" },
	{ 11, "button_6" },
	{ 12, "button_7" },
	{ 13, "button_8" },
	{ 14, "button_9" },
	{ 15, "button_10" },
	{ 16, "button_11" },
	{ 17, "button_12" },
	{ 18, "scroll_up" },
	{ 19, "scroll_down" } };

//usb data packets