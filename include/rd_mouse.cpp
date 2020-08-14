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
