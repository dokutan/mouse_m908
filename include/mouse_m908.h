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
#ifndef MOUSE_M908
#define MOUSE_M908

#include <libusb-1.0/libusb.h>
#include <map>
#include <array>
#include <string>
#include <algorithm>
#include <exception>
#include <regex>
#include <fstream>
#include <utility>

class mouse_m908{
	
	public:
		
		//constructor
		mouse_m908();
		
		//enums
		enum m908_profile{
			profile_1 = 0,
			profile_2 = 1,
			profile_3 = 2,
			profile_4 = 3,
			profile_5 = 4,
		};
		enum m908_lightmode{
			lightmode_breathing,
			lightmode_rainbow,
			lightmode_static,
			lightmode_wave,
			lightmode_alternating,
			lightmode_reactive,
			lightmode_flashing,
			lightmode_off,
		};
		enum m908_report_rate{
			r_125Hz,
			r_250Hz,
			r_500Hz,
			r_1000Hz
		};
		
		//setter functions
		int set_profile( m908_profile profile );
		int set_scrollspeed( m908_profile profile, uint8_t speed );
		int set_lightmode( m908_profile profile, m908_lightmode lightmode );
		int set_color( m908_profile profile, std::array<uint8_t, 3> color );
		int set_brightness( m908_profile profile, uint8_t brightness );
		int set_speed( m908_profile profile, uint8_t speed );
		int set_dpi_enable( m908_profile profile, int level, bool enabled );
		int set_dpi( m908_profile profile, int level, uint8_t dpi );
		int set_key_mapping( m908_profile profile, int key, std::array<uint8_t, 4> mapping );
		int set_key_mapping( m908_profile profile, int key, std::string mapping );
		int set_report_rate( m908_profile profile, m908_report_rate report_rate );
		int set_macro( int macro_number, std::string file );
		int set_macro_repeat( int macro_number, uint8_t repeat );
		
		//getter functions
		m908_profile get_profile();
		uint8_t get_scrollspeed( m908_profile profile );
		m908_lightmode get_lightmode( m908_profile profile );
		void get_color( m908_profile profile, std::array<uint8_t, 3> &color );
		uint8_t get_brightness( m908_profile profile );
		uint8_t get_speed( m908_profile profile );
		bool get_dpi_enable( m908_profile profile, int level );
		uint8_t get_dpi( m908_profile profile, int level );
		m908_report_rate get_report_rate( m908_profile profile );
		uint8_t get_macro_repeat( int macro_number );
		
		//writer functions (apply settings to mouse)
		int write_profile();
		int write_settings();
		int write_macro( int macro_number );
		int write_macro_repeat( int macro_number );
		
		//helper functions
		int open_mouse();
		int open_mouse_bus_device( uint8_t bus, uint8_t device );
		int close_mouse();
		
	private:
		
		//usb device vars
		uint16_t _mouse_vid;
		uint16_t _mouse_pid;
		libusb_device_handle* _handle;
		bool _detached_driver_0 = false;
		bool _detached_driver_1 = false;
		bool _detached_driver_2 = false;
		
		//setting vars
		m908_profile _profile;
		std::array<uint8_t, 5> _scrollspeeds;
		std::array<m908_lightmode, 5> _lightmodes;
		std::array<std::array<uint8_t, 3>, 5> _colors;
		std::array<uint8_t, 5> _brightness_levels;
		std::array<uint8_t, 5> _speed_levels;
		std::array<std::array<bool, 5>, 5> _dpi_enabled;
		std::array<std::array<uint8_t, 5>, 5> _dpi_levels;
		std::array<std::array<std::array<uint8_t, 4>, 20>, 5> _keymap_data;
		std::array<m908_report_rate, 5> _report_rates;
		std::array<std::array<uint8_t, 256>, 15> _macro_data;
		std::array<uint8_t, 15> _macro_repeat;
		
		//setting min and max values
		uint8_t _scrollspeed_min, _scrollspeed_max;
		uint8_t _brightness_min, _brightness_max;
		uint8_t _speed_min, _speed_max;
		uint8_t _level_min, _level_max;
		uint8_t _dpi_min, _dpi_max;
		
		//mapping of button names to values
		std::map< std::string, std::array<uint8_t, 3> > _keycodes;
		std::map< std::string, uint8_t > _keyboard_modifier_values;
		std::map< std::string, uint8_t > _keyboard_key_values;
		
		//usb data packets
		static uint8_t _data_profile[][16];
		static uint8_t _data_settings_1[][16];
		static uint8_t _data_settings_2[64];
		static uint8_t _data_settings_3[][16];
		static uint8_t _data_macros_1[16];
		static uint8_t _data_macros_2[256];
		static uint8_t _data_macros_3[16];
		static uint8_t _data_macros_codes[15][2];
		static uint8_t _data_macros_repeat[16];
};

#include "data.cpp"
#include "constructor.cpp"
#include "helpers.cpp"
#include "getters.cpp"
#include "setters.cpp"
#include "writers.cpp"

#endif
