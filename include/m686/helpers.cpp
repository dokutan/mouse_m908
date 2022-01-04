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

#include "../rd_mouse.h"

//helper functions

// Maps rd_profile to m686_profile
mouse_m686::m686_profile mouse_m686::rd_profile_to_m686_profile( rd_profile profile ){
	return profile == rd_mouse::rd_profile::profile_1 ? mouse_m686::m686_profile::profile_1 : mouse_m686::m686_profile::profile_2;
}

//init libusb and open mouse
int mouse_m686::open_mouse(){
	
	//vars
	int res = 0;
	
	//libusb init
	res = libusb_init( NULL );
	if( res < 0 ){
		return res;
	}
	
	//open device
	_i_handle = libusb_open_device_with_vid_pid( NULL, _c_mouse_vid, _c_mouse_pid );
	if( !_i_handle ){
		return 1;
	}
	
	if( _i_detach_kernel_driver ){
		//detach kernel driver on interface 0 if active 
		if( libusb_kernel_driver_active( _i_handle, 0 ) ){
			res += libusb_detach_kernel_driver( _i_handle, 0 );
			if( res == 0 ){
				_i_detached_driver_0 = true;
			} else{
				return res;
			}
		}
		
		//detach kernel driver on interface 1 if active 
		if( libusb_kernel_driver_active( _i_handle, 1 ) ){
			res += libusb_detach_kernel_driver( _i_handle, 1 );
			if( res == 0 ){
				_i_detached_driver_1 = true;
			} else{
				return res;
			}
		}
	}
	
	//claim interface 0
	res += libusb_claim_interface( _i_handle, 0 );
	if( res != 0 ){
		return res;
	}
	
	//claim interface 1
	res += libusb_claim_interface( _i_handle, 1 );
	if( res != 0 ){
		return res;
	}
	
	return res;
}

// init libusb and open mouse by bus and device
int mouse_m686::open_mouse_bus_device( uint8_t bus, uint8_t device ){

	//vars
	int res = 0;
	
	//libusb init
	res = libusb_init( NULL );
	if( res < 0 ){
		return res;
	}
	
	//open device (_i_handle)
	libusb_device **dev_list; // device list
	ssize_t num_devs = libusb_get_device_list(NULL, &dev_list); //get device list
	
	if( num_devs < 0 )
		return 1;
	
	for( ssize_t i = 0; i < num_devs; i++ ){
		
		// check if correct bus and device
		if( bus == libusb_get_bus_number( dev_list[i] ) &&
			device == libusb_get_device_address( dev_list[i] ) ){
			
			// open device
			if( libusb_open( dev_list[i], &_i_handle ) != 0 ){
				return 1;
			} else{
				break;
			}
			
		}
		
	}
	
	//free device list, unreference devices
	libusb_free_device_list( dev_list, 1 );
	
	
	if( _i_detach_kernel_driver ){
		//detach kernel driver on interface 0 if active 
		if( libusb_kernel_driver_active( _i_handle, 0 ) ){
			res += libusb_detach_kernel_driver( _i_handle, 0 );
			if( res == 0 ){
				_i_detached_driver_0 = true;
			} else{
				return res;
			}
		}
		
		//detach kernel driver on interface 1 if active 
		if( libusb_kernel_driver_active( _i_handle, 1 ) ){
			res += libusb_detach_kernel_driver( _i_handle, 1 );
			if( res == 0 ){
				_i_detached_driver_1 = true;
			} else{
				return res;
			}
		}
		
	}
		
	//claim interface 0
	res += libusb_claim_interface( _i_handle, 0 );
	if( res != 0 ){
		return res;
	}
	
	//claim interface 1
	res += libusb_claim_interface( _i_handle, 1 );
	if( res != 0 ){
		return res;
	}
	
	return res;
}

// close mouse
int mouse_m686::close_mouse(){

	// release interfaces 0 and 1
	libusb_release_interface( _i_handle, 0 );
	libusb_release_interface( _i_handle, 1 );
	
	// attach kernel driver for interface 0
	if( _i_detached_driver_0 ){
		libusb_attach_kernel_driver( _i_handle, 0 );
	}
	
	// attach kernel driver for interface 1
	if( _i_detached_driver_1 ){
		libusb_attach_kernel_driver( _i_handle, 1 );
	}
	
	// exit libusb
	libusb_exit( NULL );
	
	return 0;
}

// print current configuration
int mouse_m686::print_settings( std::ostream& output ){
	
	// print configuration
	output << "# Configuration created by mouse_m686::print_settings().\n";
	output << "# Currently active profile: " << _s_profile << "\n";
	
	for( int i = 1; i < 3; i++ ){
		
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
			std::array<uint8_t, 3> dpi_bytes = {_s_dpi_levels[i-1][j-1][0], _s_dpi_levels[i-1][j-1][1], _s_dpi_levels[i-1][j-1][2]};
			std::string dpi_string = "";
			
			if( _i_decode_dpi( dpi_bytes, dpi_string ) == 0 )
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

// decode the button mapping
int mouse_m686::_i_decode_button_mapping( const std::array<uint8_t, 4>& bytes, std::string& mapping ){
	int ret = 1;
	std::stringstream mapping_stream;

	// known keycode ?
	for( auto keycode : rd_mouse_wireless::_c_keycodes ){
		if(
			bytes.at(0) == keycode.second.at(0) &&
			bytes.at(1) == keycode.second.at(1) &&
			bytes.at(2) == keycode.second.at(2) &&
			bytes.at(3) == keycode.second.at(3)
		){
			ret = 0;
			mapping_stream << keycode.first;
		}
	}

	// unknown keycode
	if( ret != 0 ){
		mapping_stream
			<< "unknown, please report as bug: "
			<< " " << std::hex << (int)bytes.at(0) << " "
			<< " " << std::hex << (int)bytes.at(1) << " "
			<< " " << std::hex << (int)bytes.at(2) << " "
			<< " " << std::hex << (int)bytes.at(3)
			<< std::dec;
	}

	mapping = mapping_stream.str();
	return ret;
}

int mouse_m686::_i_decode_dpi( const std::array<uint8_t, 3>& dpi_bytes, std::string& dpi_string ){
	
	// is dpi value known?
	for( auto dpi_value : _c_dpi_codes ){
		
		if( dpi_value.second[0] == dpi_bytes[0] && dpi_value.second[1] == dpi_bytes[1] && dpi_value.second[2] == dpi_bytes[2] ){
			dpi_string = std::to_string( dpi_value.first );
			return 0;
		}
		
	}
	
	// unknown dpi value
	std::stringstream conversion_stream;
	
	conversion_stream << std::setfill('0') << std::hex;
	conversion_stream << "0x";
	conversion_stream << std::setw(2) << (int)dpi_bytes[0] << std::setw(2) << (int)dpi_bytes[1] << std::setw(2) << (int)dpi_bytes[2];
	conversion_stream << std::setfill(' ') << std::setw(0) << std::dec;
	
	dpi_string = conversion_stream.str();
	
	return 0;
}