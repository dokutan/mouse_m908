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

//init libusb and open mouse
int mouse_m601::open_mouse(){

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
	}
	
	//claim interface 0
	res += libusb_claim_interface( _i_handle, 0 );
	if( res != 0 ){
		return res;
	}
	
	return res;
}

// init libusb and open mouse by bus and device
int mouse_m601::open_mouse_bus_device( uint8_t bus, uint8_t device ){

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
	}

	//claim interface 0
	res += libusb_claim_interface( _i_handle, 0 );
	if( res != 0 ){
		return res;
	}

	return res;
}

//close mouse
int mouse_m601::close_mouse(){
	
	//release interface 0
	libusb_release_interface( _i_handle, 0 );
	
	//attach kernel driver for interface 0
	if( _i_detached_driver_0 ){
		libusb_attach_kernel_driver( _i_handle, 0 );
	}

	//exit libusb
	libusb_exit( NULL );
	
	return 0;
}

// print current configuration
int mouse_m601::print_settings( std::ostream& output ){
	// print configuration, TODO
	output << "# mouse_m601::print_settings() is not implemented.\n";
	return 0;
}

// Load the settings from a config file, TODO implement
int mouse_m601::load_settings( std::string& config_path ){
	return 0;
}

int mouse_m601::_i_decode_dpi( std::array<uint8_t, 2>& dpi_bytes, std::string& dpi_string ){
	
	// is dpi value known?
	for( auto dpi_value : _c_dpi_codes ){
		
		if( dpi_value.second[0] == dpi_bytes[0] && dpi_value.second[1] == dpi_bytes[1] ){
			dpi_string = std::to_string( dpi_value.first );
			return 0;
		}
		
	}
	
	// unknown dpi value
	std::stringstream conversion_stream;
	
	conversion_stream << std::setfill('0') << std::hex;
	conversion_stream << "0x";
	conversion_stream << std::setw(2) << (int)dpi_bytes[0] << std::setw(2) << (int)dpi_bytes[1];
	conversion_stream << std::setfill(' ') << std::setw(0) << std::dec;
	
	dpi_string = conversion_stream.str();
	
	return 0;
}
