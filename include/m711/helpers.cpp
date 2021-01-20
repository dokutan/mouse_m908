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

#include "mouse_m711.h"

//helper functions

//init libusb and open mouse
int mouse_m711::open_mouse(){
	return _i_open_mouse( _c_mouse_vid, _c_mouse_pid );
}

// init libusb and open mouse by bus and device
int mouse_m711::open_mouse_bus_device( uint8_t bus, uint8_t device ){
	return _i_open_mouse_bus_device( bus, device );
}

//close mouse
int mouse_m711::close_mouse(){
	return _i_close_mouse();
}

// print current configuration
int mouse_m711::print_settings( std::ostream& output ){
	
	// print configuration
	output << "# Configuration created by mouse_m711::print_settings().\n";
	output << "# Currently active profile: " << _s_profile << "\n";
	
	for( int i = 1; i < 6; i++ ){
		
		// section header
		output << "\n[profile" << i << "]\n";
		
		output << "\n# LED settings\n";
		
		// color
		output << "color=";
		output << std::setfill('0') << std::setw(2) << std::hex << (int)_s_colors[i-1][0];
		output << std::setfill('0') << std::setw(2) << std::hex << (int)_s_colors[i-1][1];
		output << std::setfill('0') << std::setw(2) << std::hex << (int)_s_colors[i-1][2];
		output << std::setfill(' ') << std::setw(0) << std::dec << "\n";
		
		// brightness
		output << "brightness=" << (int)_s_brightness_levels[i-1] << "\n";
		
		// speed
		output << "speed=" << (int)_s_speed_levels[i-1] << "\n";
		
		// lightmode
		output << "lightmode=";
		if( _s_lightmodes[i-1] == lightmode_off )
			output << "off\n";
		else if( _s_lightmodes[i-1] == lightmode_breathing )
			output << "breathing\n";
		else if( _s_lightmodes[i-1] == lightmode_rainbow )
			output << "rainbow\n";
		else if( _s_lightmodes[i-1] == lightmode_static )
			output << "static\n";
		else if( _s_lightmodes[i-1] == lightmode_wave )
			output << "wave\n";
		else if( _s_lightmodes[i-1] == lightmode_alternating )
			output << "alternating\n";
		else if( _s_lightmodes[i-1] == lightmode_reactive )
			output << "reactive\n";
		else if( _s_lightmodes[i-1] == lightmode_flashing )
			output << "flashing\n";
		else{
			output << "unknown, please report as bug\n";
		}
		
		// polling rate (report rate)
		output << "\n";
		if( _s_report_rates[i-1] == r_125Hz )
			output << "report_rate=125\n";
		else if( _s_report_rates[i-1] == r_250Hz )
			output << "report_rate=250\n";
		else if( _s_report_rates[i-1] == r_500Hz )
			output << "report_rate=500\n";
		else if( _s_report_rates[i-1] == r_1000Hz )
			output << "report_rate=1000\n";
		else{
			output << "# report rate unknown, please report as bug\n";
		}
		
		// scrollspeed
		output << "scrollspeed=" << std::hex << (int)_s_scrollspeeds[i-1] << std::dec << "\n";
		
		// dpi
		output << "\n# DPI settings\n";
		for( int j = 1; j < 6; j++ ){
			
			if( _s_dpi_enabled[i-1][j-1] )
				output << "dpi" << j << "_enable=1\n";
			else
				output << "dpi" << j << "_enable=0\n";
			
			// DPI value
			std::array<uint8_t, 2> dpi_bytes = {_s_dpi_levels[i-1][j-1][0], _s_dpi_levels[i-1][j-1][1]};
			std::string dpi_string = "";
			
			if( dpi_bytes_to_string( dpi_bytes, dpi_string ) == 0 )
				output << "dpi" << j << "=" << dpi_string << "\n";
			else
				output << "\n";
		}
		
		// button mapping
		output << "\n# Button mapping\n";
		
		for( int j = 0; j < 8; j++ ){
			std::array< uint8_t, 4 > bytes = {
				_s_keymap_data[i-1][j][0],
				_s_keymap_data[i-1][j][1],
				_s_keymap_data[i-1][j][2],
				_s_keymap_data[i-1][j][3]
			};
			std::string mapping;
			
			_i_decode_button_mapping( bytes, mapping );
			output << _c_button_names[j] << "=" << mapping << std::endl;
		}
	}
	
	// macros
	output << "\n# Macros\n";
	for( int i = 0; i < 15; i++ ){
		
		// is macro not defined ?
		if( _s_macro_data[i][8] == 0 && _s_macro_data[i][9] == 0 && _s_macro_data[i][10] == 0 )
			continue;
		
		// _i_decode_macros takes a vector as argument, copy array to vector
		std::vector< uint8_t > macro_bytes( _s_macro_data[i].begin(), _s_macro_data[i].end() );
		
		// print macro (macro data starts at byte 8)
		output << "\n;## macro" << i+1 << "\n";
		_i_decode_macro( macro_bytes, output, ";# ", 8 );
		
	}
	
	return 0;
}
