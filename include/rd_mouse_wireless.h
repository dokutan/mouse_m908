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

#ifndef RD_MOUSE_WIRELESS
#define RD_MOUSE_WIRELESS

#include <array>
#include <string>
#include <map>
#include <vector>

/**
 * This class holds data that is shared between the wireless mice.
 */
class rd_mouse_wireless{

	protected:
		
		/// Values/keycodes of mouse buttons and special button functions
		static std::map< std::string, std::array<uint8_t, 4> > _c_keycodes;

};

#endif
