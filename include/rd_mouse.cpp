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

#include "rd_mouse.h"

std::string rd_mouse::detect(){
	
	std::string model = "";
	
	// libusb init
	if( libusb_init( NULL ) < 0 )
		return model;
	
	// get device list
	libusb_device **dev_list; // device list
	ssize_t num_devs = libusb_get_device_list(NULL, &dev_list);
	
	if( num_devs < 0 )
		return model;
	
	for( ssize_t i = 0; i < num_devs; i++ ){
		
		// get device descriptor
		libusb_device_descriptor descriptor;
		libusb_get_device_descriptor( dev_list[i], &descriptor );
		
		// get vendor and product id from descriptor
		uint16_t vid = descriptor.idVendor;
		uint16_t pid = descriptor.idProduct;
		
		// compare vendor and product id against known ids
		if( vid == mouse_m908::get_vid() && pid == mouse_m908::get_pid() ){
			model = "908";
			break;
		}else if( vid == mouse_m709::get_vid() && pid == mouse_m709::get_pid() ){
			model = "709";
			break;
		}else if( vid == mouse_m711::get_vid() && pid == mouse_m711::get_pid() ){
			model = "711";
			break;
		}else if( vid == mouse_m715::get_vid() && pid == mouse_m715::get_pid() ){
			model = "715";
			break;
		}
		
	}
	
	// free device list, unreference devices
	libusb_free_device_list( dev_list, 1 );
	
	// exit libusb
	libusb_exit( NULL );
		
	return model;
}

//init libusb and open mouse
int rd_mouse::_i_open_mouse( const uint16_t vid, const uint16_t pid ){
	
	//vars
	int res = 0;
	
	//libusb init
	res = libusb_init( NULL );
	if( res < 0 ){
		return res;
	}
	
	//open device
	_i_handle = libusb_open_device_with_vid_pid( NULL, vid,	pid );
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
		
		//detach kernel driver on interface 2 if active 
		if( libusb_kernel_driver_active( _i_handle, 2 ) ){
			res += libusb_detach_kernel_driver( _i_handle, 2 );
			if( res == 0 ){
				_i_detached_driver_2 = true;
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
	
	//claim interface 2
	res += libusb_claim_interface( _i_handle, 2 );
	if( res != 0 ){
		return res;
	}
	
	return res;
}

// init libusb and open mouse by bus and device
int rd_mouse::_i_open_mouse_bus_device( const uint8_t bus, const uint8_t device ){
	
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
		
		//detach kernel driver on interface 2 if active 
		if( libusb_kernel_driver_active( _i_handle, 2 ) ){
			res += libusb_detach_kernel_driver( _i_handle, 2 );
			if( res == 0 ){
				_i_detached_driver_2 = true;
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
	
	//claim interface 2
	res += libusb_claim_interface( _i_handle, 2 );
	if( res != 0 ){
		return res;
	}
	
	return res;
}

//close mouse
int rd_mouse::_i_close_mouse(){
	
	//release interfaces 0, 1 and 2
	libusb_release_interface( _i_handle, 0 );
	libusb_release_interface( _i_handle, 1 );
	libusb_release_interface( _i_handle, 2 );
	
	//attach kernel driver for interface 0
	if( _i_detached_driver_0 ){
		libusb_attach_kernel_driver( _i_handle, 0 );
	}
	
	//attach kernel driver for interface 1
	if( _i_detached_driver_1 ){
		libusb_attach_kernel_driver( _i_handle, 1 );
	}
	
	
	//attach kernel driver for interface 2
	if( _i_detached_driver_2 ){
		libusb_attach_kernel_driver( _i_handle, 2);
	}
	
	//exit libusb
	libusb_exit( NULL );
	
	return 0;
}

//decode macro bytecode
int rd_mouse::_i_decode_macro( std::vector< uint8_t >& macro_bytes, std::ostream& output, std::string prefix, size_t offset ){
	
	// valid offset ?
	if( offset >= macro_bytes.size() )
		offset = 0;
	
	for( size_t i = offset; i < macro_bytes.size(); ){
		
		bool unknown_code = false;
		
		// failsafe
		if( i >= macro_bytes.size() )
			break;
		
		// mouse buttons ( 0x81 = down, 0x01 = up )
		if( macro_bytes[i] == 0x81 && macro_bytes[i+1] == 0x01 )
			output << prefix << "down\tmouse_left\n";
		else if( macro_bytes[i] == 0x81 && macro_bytes[i+1] == 0x02 )
			output << prefix << "down\tmouse_right\n";
		else if( macro_bytes[i] == 0x81 && macro_bytes[i+1] == 0x04 )
			output << prefix << "down\tmouse_middle\n";
		else if( macro_bytes[i] == 0x01 && macro_bytes[i+1] == 0x01 )
			output << prefix << "up\tmouse_left\n";
		else if( macro_bytes[i] == 0x01 && macro_bytes[i+1] == 0x02 )
			output << prefix << "up\tmouse_right\n";
		else if( macro_bytes[i] == 0x01 && macro_bytes[i+1] == 0x04 )
			output << prefix << "up\tmouse_middle\n";
		else if( macro_bytes[i] == 0x81 || macro_bytes[i] == 0x01 )
			unknown_code = true; // unknown code
		
		// keyboard key ( 0x84 = down, 0x04 = up )
		else if( macro_bytes[i] == 0x84 || macro_bytes[i] == 0x04 ){
			
			bool found_name = false;
			std::string key = "";
			
			// iterate over _c_keyboard_key_values
			for( auto keycode : _c_keyboard_key_values ){
				
				if( keycode.second == macro_bytes[i+1] ){
					key = keycode.first;
					found_name = true;
					break;
				}
				
			}
			
			// if key found, print key action
			if( found_name ){
				
				if( macro_bytes[i] == 0x84 ) // keyboard key down
					output << prefix << "down\t" << key << "\n";
				else if( macro_bytes[i] == 0x04 ) // keyboard key up
					output << prefix << "up\t" << key << "\n";
				else // failsafe
					unknown_code = true;
				
			} else{ // unknown key
				unknown_code = true;
			}
			
		}
		// delay
		else if( macro_bytes[i] == 0x06 ){
			output << prefix << "delay\t" << (int)macro_bytes[i+1] << "\n";
		}
		// padding (increment by one until a code appears)
		else if( macro_bytes[i] == 0x00 ){
			i++;
		}
		// unknown code
		else{
			unknown_code = true;
		}
		
		// if unknown code, print message + code
		if( unknown_code ){
			output << prefix << "unknown, please report as bug: ";
			output << std::hex << (int)macro_bytes[i] << " ";
			output << std::hex << (int)macro_bytes[i+1] << " ";
			output << std::hex << (int)macro_bytes[i+2];
			output << std::dec << "\n";
		}
		
		// increment (each code is 3 bytes long)
		i+=3;
		
	}
	
	return 0;
}
