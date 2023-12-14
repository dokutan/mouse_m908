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
#ifndef MOUSE_M601
#define MOUSE_M601

#include <libusb.h>
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
 * The main class representing the M601 mouse.
 * This class has member functions to open, close and apply settings to the mouse.
 * 
 * There are 4 main types of functions:
 * - set_*: setters, for the M601 the majority of setters is replaced by load_settings()
 * - get_*: getters
 * - write_*: write the settings to the mouse
 * - read_*: read the sttings from the mouse
 * 
 * Therefore the general procedure when changing settings on the mouse is as follows:
 * 1. open_mouse() or open_mouse_bus_device()
 * 2. load_settings() (or set_*, this step only changes the internal state of the class)
 * 3. write_* (this step sends the internal state of the class to the mouse)
 * 4. close_mouse()
 * 
 * Private member variables are named as follows:
 * - \_i\_* for internal variables that determine how the mouse is opened, etc.
 * - \_s\_* for variables that describe the settings on the mouse
 * - \_c\_* for constants like keycodes, USB data, minimum and maximum values, etc. (these are not neccessarily defined as const)
 */
class mouse_m601 : public rd_mouse{
	
	public:
		
		/// The default constructor. Sets the default settings.
		mouse_m601();

		//setter functions
		/// Set the currently active profile
		int set_profile( rd_profile profile );

		// These setters do nothing and exist only for compatibility. Use load_settings() instead.
		int set_scrollspeed( rd_profile profile, uint8_t speed );
		int set_lightmode( rd_profile profile, rd_lightmode lightmode );
		int set_color( rd_profile profile, std::array<uint8_t, 3> color );
		int set_brightness( rd_profile profile, uint8_t brightness );
		int set_speed( rd_profile profile, uint8_t speed );
		int set_dpi_enable( rd_profile profile, int level, bool enabled );
		int set_dpi( rd_profile profile, int level, std::string dpi );
		int set_dpi( rd_profile profile, int level, std::array<uint8_t, 2> dpi );
		int set_key_mapping( rd_profile profile, int key, std::array<uint8_t, 4> mapping );
		int set_key_mapping( rd_profile profile, int key, std::string mapping );
		int set_report_rate( rd_profile profile, rd_report_rate report_rate );
		int set_macro( int macro_number, std::string file );
		int set_all_macros( std::string file );
		
		/// Does nothing, exists only for compatibility
		void set_vid( uint16_t vid ){ (void)vid; }
		/// Does nothing, exists only for compatibility
		void set_pid( uint16_t pid ){ (void)pid; }
		
		/// Checks if the mouse has the given vendor and product id
		static bool has_vid_pid( uint16_t vid, uint16_t pid ){
			return vid == _c_mouse_vid && pid == _c_mouse_pid;
		}
		
		/// Get mouse name
		static std::string get_name(){
			return _c_name;
		}
		
		//writer functions (apply settings to mouse)
		/** \brief Write the currently active profile to the mouse
		 * \return 0 if successful
		 */
		int write_profile();
		
		/** \brief Write the settings (leds, button mapping, dpi, etc.) to the mouse
		 * \return 0 if successful
		 */
		int write_settings();
		
		/** \brief Write a macro to the mouse
		 * \return 0 if successful
		 */
		int write_macro( int macro_number );
		
		/** \brief Write the number of repeats for a macro to the mouse
		 * \return 0 if successful
		 */
		int write_macro_repeat( int macro_number );
		
		
		
		//helper functions
		/** \brief Init libusb and open the mouse by its USB VID and PID
		 * \return 0 if successful
		 */
		int open_mouse();
		
		/** \brief Init libusb and open the mouse by the USB bus and device adress
		 * \return 0 if successful
		 */
		int open_mouse_bus_device( uint8_t bus, uint8_t device );
		
		/** \brief Close the mouse and libusb
		 * \return 0 if successful (always at the moment)
		 */
		int close_mouse();
		
		/// Print the current configuration in .ini format to output
		int print_settings( std::ostream& output );

		/// Load the settings from a config file, TODO implement
		int load_settings( std::string& config_path );
		
		
		
		//reader functions (get settings from the mouse)
		/// Read the settings and print the raw data to output
		int dump_settings( std::ostream& output );
		/**
		 * \brief Read the settings and print the configuration in .ini format to output.
		 * This does not alter the internal settings of the mouse_m601 class.
		 */
		int read_and_print_settings( std::ostream& output );
		/**
		 * \brief Read the settings and print the configuration in .ini format to output.
		 * This updates the internal settings of the mouse_m601 class.
		 */
		int read_settings();
		
		
		
		/// Returns a reference to _c_button_names (physical button names)
		std::map< int, std::string >& button_names(){ return _c_button_names; }
		
	private:
		
		/// Names of the physical buttons
		static std::map< int, std::string > _c_button_names;

		/// Mapping of real DPI values to bytecode
		static std::map< unsigned int, std::array<uint8_t, 2> > _c_dpi_codes;

		/// The model name
		static const std::string _c_name;

		//usb device vars
		/// USB vendor id
		static const uint16_t _c_mouse_vid;
		/// USB product id
		static const uint16_t _c_mouse_pid;
		
		//setting vars
		rd_profile _s_profile;
		std::array<uint8_t, 5> _s_scrollspeeds;
		std::array<rd_lightmode, 5> _s_lightmodes;
		std::array<std::array<uint8_t, 3>, 5> _s_colors;
		std::array<uint8_t, 5> _s_brightness_levels;
		std::array<uint8_t, 5> _s_speed_levels;
		std::array<std::array<bool, 5>, 5> _s_dpi_enabled;
		std::array<std::array<std::array<uint8_t, 2>, 5>, 5> _s_dpi_levels;
		std::array<std::array<std::array<uint8_t, 4>, 10>, 5> _s_keymap_data;
		std::array<rd_report_rate, 5> _s_report_rates;
		std::array<std::array<uint8_t, 256>, 15> _s_macro_data;
		std::array<uint8_t, 15> _s_macro_repeat;
		
		//usb data packets, TODO

		/** Convert raw dpi bytes to a string representation (doesn't validate dpi value)
		 * This function overloads the implementation from rd_mouse and supports actual DPI values.
		 * \return 0 if no error
		 */
		static int _i_decode_dpi( std::array<uint8_t, 2>& dpi_bytes, std::string& dpi_string );
};

#endif
