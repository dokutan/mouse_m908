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

//writer functions (apply changes to mouse)

int mouse_m913::write_profile(){
	// missing data
	return 0;
}

int mouse_m913::write_settings(){

	// return value
	int ret = 0;

	// prepare data
	int rows = sizeof(_c_data_settings) / sizeof(_c_data_settings[0]);
	uint8_t buffer[rows][17];
	for( int i = 0; i < rows; i++ ){
		std::copy(std::begin(_c_data_settings[i]), std::end(_c_data_settings[i]), std::begin(buffer[i]));
	}

	// TODO! modify buffer to include the actual settings
	
	// send data
	uint8_t buffer_in[17]; // holds the received data
	int received; // how many bytes were actually received
	for( int i = 0; i < rows; i++ ){
		ret += libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0308, 0x0001, buffer[i], 17, 1000 );
		ret += libusb_interrupt_transfer( _i_handle, 0x82, buffer_in, 17, &received, 1000 );
	}

	return ret;
}

int mouse_m913::write_macro( int macro_number ){
	// missing data
	(void)macro_number;
	return 0;
}
