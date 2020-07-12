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

//main class
#ifndef RD_MOUSE
#define RD_MOUSE

//#include <libusb.h>
#include <map>
#include <array>
#include <string>
#include <algorithm>
#include <exception>
#include <regex>
#include <fstream>
#include <sstream>
#include <utility>
#include <iostream>
#include <iomanip>

/**
 * This class is used as a base for the different models
 * 
 * Global constants (e.g. keyboard keycodes) and universal functions
 * should be placed in this class.
 * 
 */
class rd_mouse{
	
	public:
		
		// enums
		/// The available profiles
		enum rd_profile{
			profile_1 = 0,
			profile_2 = 1,
			profile_3 = 2,
			profile_4 = 3,
			profile_5 = 4,
		};
		
		/// The available led modes
		enum rd_lightmode{
			lightmode_breathing,
			lightmode_rainbow,
			lightmode_static,
			lightmode_wave,
			lightmode_alternating,
			lightmode_reactive,
			lightmode_flashing,
			lightmode_off,
		};
		
		/// The available USB report rates (polling rates)
		enum rd_report_rate{
			r_125Hz,
			r_250Hz,
			r_500Hz,
			r_1000Hz
		};
		
	protected:
		
		//setting min and max values
		static const uint8_t _c_scrollspeed_min, _c_scrollspeed_max;
		static const uint8_t _c_brightness_min, _c_brightness_max;
		static const uint8_t _c_speed_min, _c_speed_max;
		static const uint8_t _c_level_min, _c_level_max;
		static const uint8_t _c_dpi_min, _c_dpi_max;
		
		//mapping of button names to values
		/// Values/keycodes of mouse buttons and special button functions
		static std::map< std::string, std::array<uint8_t, 3> > _c_keycodes;
		/// Values of keyboard modifiers
		static const std::map< std::string, uint8_t > _c_keyboard_modifier_values;
		/// Values/keycodes of keyboard keys
		static std::map< std::string, uint8_t > _c_keyboard_key_values;
		
};

// include header files for the individual models TODO!
#include "m908/mouse_m908.h"

#endif
