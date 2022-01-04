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
#ifndef MOUSE_M913
#define MOUSE_M913

#include "../rd_mouse_wireless.h"

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
 * The main class representing the M913 mouse.
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
class mouse_m913 : public rd_mouse, protected rd_mouse_wireless {
	
	public:
		
		/// The default constructor. Sets the default settings.
		mouse_m913();
		
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
		 * \return 0 if successful, 1 if out of bounds or invalid dpi
		 */
		int set_dpi( rd_profile profile, int level, std::string dpi );
		int set_dpi( rd_profile profile, int level, std::array<uint8_t, 3> dpi );
		
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
		
		/// Set USB vendor id, does nothing
		void set_vid( uint16_t vid ){
			(void)vid;
		}
		/// Set USB product id
		void set_pid( uint16_t pid ){
			_c_mouse_pid = pid;
		}
		
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
		int get_dpi( rd_profile profile, int level, std::array<uint8_t, 2>& dpi );
		/// Get USB poll rate of specified profile
		rd_report_rate get_report_rate( rd_profile profile );
		/// Get button mapping as a string
		int get_key_mapping( rd_profile profile, int key, std::string& mapping );
		/// Get button mapping as a 4-byte value
		int get_key_mapping_raw( rd_profile profile, int key, std::array<uint8_t, 4>& mapping );
		/// Get macro as a string
		int get_macro( int number, std::string& macro );
		/// Get raw macro bytecode
		int get_macro_raw( int number, std::array<uint8_t, 256>& macro );
		
		/// Checks if the mouse has the given vendor and product id
		static bool has_vid_pid( uint16_t vid, uint16_t pid ){
			return vid == _c_mouse_vid && _c_all_pids.find(pid) != _c_all_pids.end();
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
		 * This does not alter the internal settings of the mouse_m913 class.
		 */
		int read_and_print_settings( std::ostream& output );
		/**
		 * \brief Read the settings and print the configuration in .ini format to output.
		 * This updates the internal settings of the mouse_m913 class.
		 */
		int read_settings();
		
		
		
		/// Returns a reference to _c_button_names (physical button names)
		std::map< int, std::string >& button_names(){ return _c_button_names; }
		
	private:
		/// The M913 has only two profiles.
		enum m913_profile{
			profile_1 = 0,
			profile_2 = 1,
		};

		/// The M913 has different light modes from the other mice
		enum m913_lightmode{
			lightmode_off,
			lightmode_static,
			lightmode_breathing,
			lightmode_rainbow
		};

		uint8_t _c_brightness_min = 0x00;
		uint8_t _c_brightness_max = 0xff;

		/// Maps rd_profile to m913_profile
		m913_profile rd_profile_to_m913_profile( rd_profile profile );

		/// Write raw data
		int write_data(uint8_t data[][17], size_t rows);

		/// Write the button mapping to the mouse
		int write_button_mapping( m913_profile profile );

		/// Write the DPI settings to the mouse
		int write_dpi_settings( m913_profile profile );

		/// Write the LED settings to the mouse
		int write_led_settings( m913_profile profile );

		/** \brief Decodes the bytes describing a button mapping
		 * \arg bytes the 4 bytes descriping the mapping
		 * \arg mapping string to hold the result
		 * \return 0 if valid button mapping
		 * \see _i_encode_button_mapping
		 */
		static int _i_decode_button_mapping( const std::array<uint8_t, 4>& bytes, std::string& mapping );

		/** Convert raw dpi bytes to a string representation (doesn't validate dpi value)
		 * This function overloads the implementation from rd_mouse and supports actual DPI values.
		 * \return 0 if no error
		 */
		static int _i_decode_dpi( const std::array<uint8_t, 3>& dpi_bytes, std::string& dpi_string );
		
		/// Names of the physical buttons
		static std::map< int, std::string > _c_button_names;
		
		/// The model name
		static const std::string _c_name;

		//usb device vars
		static std::set< uint16_t > _c_all_pids;
		/// USB vendor id
		static const uint16_t _c_mouse_vid;
		/// USB product id, needs to be explicitly set
		uint16_t _c_mouse_pid = 0;

		/// DPI → bytecode
		static std::map< int, std::array<uint8_t,3> > _c_dpi_codes;
		/// Used to identify buttons when mapping buttons to keyboard keys
		static std::map< int, std::array<uint8_t, 3> > _c_keyboard_key_buttons;

		//setting vars
		rd_profile _s_profile;
		std::array<uint8_t, 2> _s_scrollspeeds;
		std::array<m913_lightmode, 2> _s_lightmodes;
		std::array<std::array<uint8_t, 3>, 2> _s_colors;
		std::array<uint8_t, 2> _s_brightness_levels;
		std::array<uint8_t, 2> _s_speed_levels;
		std::array<std::array<bool, 5>, 2> _s_dpi_enabled;
		std::array<std::array<std::array<uint8_t, 3>, 5>, 2> _s_dpi_levels;
		std::array<std::array<std::array<uint8_t, 4>, 16>, 2> _s_keymap_data;
		std::array<rd_report_rate, 2> _s_report_rates;
		std::array<std::array<uint8_t, 256>, 15> _s_macro_data;
		std::vector<std::array<uint8_t, 17>> _s_keyboard_key_packets;
		
		//usb data packets
		/// button mapping
		static uint8_t _c_data_button_mapping[8][17];
		/// DPI values
		static uint8_t _c_data_dpi[4][17];
		/// Unknown function
		static uint8_t _c_data_unknown_2[3][17];
		/// LED settings
		static uint8_t _c_data_led_static[3][17];
		/// LED settings
		static uint8_t _c_data_led_breathing[3][17];
		/// LED settings
		static uint8_t _c_data_led_off[2][17];
		/// LED settings
		static uint8_t _c_data_led_rainbow[3][17];
		/// Unknown function
		static uint8_t _c_data_unknown_3[1][17];
		/// Used to read the settigs from the mouse
		static uint8_t _c_data_read[69][17];

};

#endif
