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

#include "../rd_mouse.h"

/**
 * The main class representing the M908 mouse.
 * This class has member functions to open, close and apply settings to the mouse.
 * 
 * There are 4 main types of functions:
 * - set_*: setters
 * - get_*: getters
 * - write_*: write the settings to the mouse
 * - read_*: read the sttings from the mouse
 * 
 * Therefore the general procedure when changing settings on the mouse is as follows:
 * 1. open_mouse() or open_mouse_bus_device()
 * 2. set_* (this step only changes the internal state of the class)
 * 3. write_* (this step sends the internal state of the class to the mouse)
 * 4. close_mouse()
 * 
 * Private member variables are named as follows:
 * - \_i\_* for internal variables that determine how the mouse is opened, etc.
 * - \_s\_* for variables that describe the settings on the mouse
 * - \_c\_* for constants like keycodes, USB data, minimum and maximum values, etc. (these are not neccessarily defined as const)
 */
class mouse_m908 : public rd_mouse{
	
	public:
		
		/// The default constructor. Sets the default settings.
		mouse_m908();
		
		//setter functions
		/// Set the currently active profile
		int set_profile( rd_profile profile );
		
		/** \brief Set the scrollspeed for the specified profile
		 * \see _c_scrollspeed_min
		 * \see _c_scrollspeed_max
		 * \return 0 if successful, 1 if out of bounds
		 */
		int set_scrollspeed( rd_profile profile, uint8_t speed );
		
		/** \brief Set the led mode for the specified profile
		 * \see rd_lightmode
		 * \return 0 if successful
		 */
		int set_lightmode( rd_profile profile, rd_lightmode lightmode );
		
		/** \brief Set the led color for the specified profile
		 * \param color color as {r, g, b}
		 * \return 0 if successful
		 */
		int set_color( rd_profile profile, std::array<uint8_t, 3> color );
		
		/** \brief Set the led brightness for the specified profile
		 * \see _c_brightness_min
		 * \see _c_brightness_max
		 * \return 0 if successful, 1 if out of bounds
		 */
		int set_brightness( rd_profile profile, uint8_t brightness );
		
		/** \brief Set the led animation speed for the specified profile
		 * \see _c_speed_min
		 * \see _c_speed_max
		 * \return 0 if successful, 1 if out of bounds
		 */
		int set_speed( rd_profile profile, uint8_t speed );
		
		/** \brief Enables/Disables a dpi level for the specified profile
		 * \see _c_level_min
		 * \see _c_level_max
		 * \return 0 if successful, 1 if out of bounds
		 */
		int set_dpi_enable( rd_profile profile, int level, bool enabled );
		
		/** \brief Set the value of a dpi level for the specified profile
		 * \see _c_dpi_min
		 * \see _c_dpi_max
		 * \see _c_level_min
		 * \see _c_level_max
		 * \return 0 if successful, 1 if out of bounds
		 */
		int set_dpi( rd_profile profile, int level, uint8_t dpi );
		
		/** \brief Set a mapping for a button for the specified profile
		 * \param mapping 4 bytes for the usb data packets
		 * \return 0 if successful
		 */
		int set_key_mapping( rd_profile profile, int key, std::array<uint8_t, 4> mapping );
		
		/** \brief Set a mapping for a button for the specified profile
		 * \param mapping button name (see keymap.md)
		 * \return 0 if successful, 1 if mapping is invalid
		 */
		int set_key_mapping( rd_profile profile, int key, std::string mapping );
		
		/** \brief Set the USB poll rate for the specified profile
		 * \see rd_report_rate
		 * \return 0 if successful
		 */
		int set_report_rate( rd_profile profile, rd_report_rate report_rate );
		
		/** \brief Load the macro from the specified file into the specified slot
		 * \param macro_number macro slot (1-15)
		 * \return 0 if successful
		 */
		int set_macro( int macro_number, std::string file );
		
		/** \brief Load all macros from the specified .ini file
		 * \return 0 if successful
		 */
		int set_all_macros( std::string file );
		
		/** \brief Set how many times the specified macro should be repeated
		 * \param macro_number macro slot (1-15)
		 * \return 0 if successful
		 */
		int set_macro_repeat( int macro_number, uint8_t repeat );
		
		/** \brief Set whether to try to detach the kernel driver when opening the mouse
		 */
		int set_detach_kernel_driver( bool detach_kernel_driver );
		
		
		
		//getter functions
		/// Get currently active profile
		rd_profile get_profile();
		/// Get scrollspeed of specified profile
		uint8_t get_scrollspeed( rd_profile profile );
		/// Get led mode of specified profile
		rd_lightmode get_lightmode( rd_profile profile );
		/// Get led color of specified profile
		void get_color( rd_profile profile, std::array<uint8_t, 3> &color );
		/// Get led brightness of specified profile
		uint8_t get_brightness( rd_profile profile );
		/// Get led animation speed of specified profile
		uint8_t get_speed( rd_profile profile );
		/// Get dpi level enabled/disabled status of specified profile
		bool get_dpi_enable( rd_profile profile, int level );
		/// Get dpi value of specified level and profile
		uint8_t get_dpi( rd_profile profile, int level );
		/// Get USB poll rate of specified profile
		rd_report_rate get_report_rate( rd_profile profile );
		/// Get macro repeat number of specified profile
		uint8_t get_macro_repeat( int macro_number );
		/// Get _i_detach_kernel_driver
		bool get_detach_kernel_driver();
		/// Get button mapping as a string
		int get_key_mapping( rd_profile profile, int key, std::string& mapping );
		/// Get button mapping as a 4-byte value
		int get_key_mapping_raw( rd_profile profile, int key, std::array<uint8_t, 4>& mapping );
		/// Get macro as a string
		int get_macro( int number, std::string& macro );
		/// Get raw macro bytecode
		int get_macro_raw( int number, std::array<uint8_t, 256>& macro );
		
		
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
		
		
		
		//reader functions (get settings from the mouse)
		/// Read the settings and print the raw data to output
		int dump_settings( std::ostream& output );
		/**
		 * \brief Read the settings and print the configuration in .ini format to output.
		 * This does not alter the internal settings of the mouse_m908 class.
		 */
		int read_and_print_settings( std::ostream& output );
		/**
		 * \brief Read the settings and print the configuration in .ini format to output.
		 * This updates the internal settings of the mouse_m908 class.
		 */
		int read_settings();
		
		/// Names of the physical buttons
		static std::map< int, std::string > _c_button_names;
		
	private:
		
		/// whether to detach kernel driver
		bool _i_detach_kernel_driver = true;
		
		//usb device vars
		/// USB vendor id
		static const uint16_t _c_mouse_vid;
		/// USB product id
		static const uint16_t _c_mouse_pid;
		/// libusb device handle
		libusb_device_handle* _i_handle;
		/// set by open_mouse for close_mouse
		bool _i_detached_driver_0 = false;
		/// set by open_mouse for close_mouse
		bool _i_detached_driver_1 = false;
		/// set by open_mouse for close_mouse
		bool _i_detached_driver_2 = false;
		
		//setting vars
		rd_profile _s_profile;
		std::array<uint8_t, 5> _s_scrollspeeds;
		std::array<rd_lightmode, 5> _s_lightmodes;
		std::array<std::array<uint8_t, 3>, 5> _s_colors;
		std::array<uint8_t, 5> _s_brightness_levels;
		std::array<uint8_t, 5> _s_speed_levels;
		std::array<std::array<bool, 5>, 5> _s_dpi_enabled;
		std::array<std::array<uint8_t, 5>, 5> _s_dpi_levels;
		std::array<std::array<std::array<uint8_t, 4>, 20>, 5> _s_keymap_data;
		std::array<rd_report_rate, 5> _s_report_rates;
		std::array<std::array<uint8_t, 256>, 15> _s_macro_data;
		std::array<uint8_t, 15> _s_macro_repeat;
		
		//usb data packets
		/// Used for changing the active profile
		static uint8_t _c_data_s_profile[6][16];
		/// Used for sending the settings, part 1/3
		static uint8_t _c_data_settings_1[15][16];
		/// Used for sending the settings, part 2/3
		static uint8_t _c_data_settings_2[64];
		/// Used for sending the settings, part 3/3
		static uint8_t _c_data_settings_3[140][16];
		/// Used for sending a macro, part 1/3
		static uint8_t _c_data_macros_1[16];
		/// Used for sending a macro, part 2/3
		static uint8_t _c_data_macros_2[256];
		/// Used for sending a macro, part 3/3
		static uint8_t _c_data_macros_3[16];
		/// Lookup table used when specifying which slot to send a macro to
		static uint8_t _c_data_macros_codes[15][2];
		/// Used to send the number repeats for a macro 
		static uint8_t _c_data_macros_repeat[16];
		/// Used to read the settings, part 1/3 
		static uint8_t _c_data_read_1[9][16];
		/// Used to read the settings, part 2/3 
		static uint8_t _c_data_read_2[85][64];
		/// Used to read the settings, part 3/3 
		static uint8_t _c_data_read_3[101][16];
};

/* the files are now compiled individually
#include "data.cpp"
#include "constructor.cpp"
#include "helpers.cpp"
#include "getters.cpp"
#include "setters.cpp"
#include "writers.cpp"
*/

#endif
