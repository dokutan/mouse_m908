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

int mouse_m601::write_profile(){
	
	//prepare data
	uint8_t buffer[6][16];
	for( int i = 0; i < 6; i++ ){
		std::copy(std::begin(_c_data_s_profile[i]), std::end(_c_data_s_profile[i]), std::begin(buffer[i]));
	}
	
	//modify buffer from default to include specified profile
	buffer[0][8] = _s_profile;
	
	//send data
	for( int i = 0; i < 6; i++ ){
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer[i], 16, 1000 );
	}
	
	return 0;
}

int mouse_m601::write_settings(){
	
	return 0;
}

int mouse_m601::write_macro( int macro_number ){
	// TODO implement macros
	(void)macro_number;
	throw std::string( "Macros are currently not supported on the M601." );
	return 1;
}
