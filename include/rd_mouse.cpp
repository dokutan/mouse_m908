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
