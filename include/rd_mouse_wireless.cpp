/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include "rd_mouse_wireless.h"

std::map< std::string, std::array<uint8_t, 4> > rd_mouse_wireless::_c_keycodes = {
	{ "left", { 0x01, 0x01, 0x00, 0x53 } },
	{ "right", { 0x01, 0x02, 0x00, 0x52 } },
	{ "middle", { 0x01, 0x04, 0x00, 0x50 } },
	{ "backward", { 0x01, 0x08, 0x00, 0x4c } },
	{ "forward", { 0x01, 0x10, 0x00, 0x44 } },
	{ "led_toggle", { 0x08, 0x00, 0x00, 0x4d } },
	{ "report_rate", { 0x07, 0x00, 0x00, 0x4e } },
	{ "dpi-", { 0x02, 0x03, 0x00, 0x50 } },
	{ "dpi+", { 0x02, 0x02, 0x00, 0x51 } },
	{ "dpi-cycle", { 0x02, 0x01, 0x00, 0x52 } },
	{ "default", { 0x05, 0x00, 0x00, 0x50 } },
	{ "none", { 0x00, 0x00, 0x00, 0x55 } },
	{ "profile_switch", { 0x09, 0x00, 0x00, 0x4c } },
};

uint8_t rd_mouse_wireless::_i_keyboard_key_checksum(uint8_t scancode){
	return (uint8_t)(0x91 - (uint8_t)(2 * scancode));
}

std::array<uint8_t, 17> rd_mouse_wireless::_c_data_button_as_keyboard_key = {
	0x08, 0x07, 0x00, 0x01, 0x60, 0x08, 0x02, 0x81, 0x21, 0x00, 0x41, 0x21, 0x00, 0x4f, 0x00, 0x00, 0x88
};
