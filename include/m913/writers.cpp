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
	// DPI level 1
	buffer[19][6] = _s_dpi_levels[profile_1][0][0];
	buffer[19][7] = _s_dpi_levels[profile_1][0][1];
	buffer[19][9] = _s_dpi_levels[profile_1][0][2];
	// DPI level 2
	buffer[19][10] = _s_dpi_levels[profile_1][1][0];
	buffer[19][11] = _s_dpi_levels[profile_1][1][1];
	buffer[19][13] = _s_dpi_levels[profile_1][1][2];
	// DPI level 3
	buffer[20][6] = _s_dpi_levels[profile_1][2][0];
	buffer[20][7] = _s_dpi_levels[profile_1][2][1];
	buffer[20][9] = _s_dpi_levels[profile_1][2][2];
	// DPI level 4
	buffer[20][10] = _s_dpi_levels[profile_1][3][0];
	buffer[20][11] = _s_dpi_levels[profile_1][3][1];
	buffer[20][12] = _s_dpi_levels[profile_1][3][2];
	// DPI level 5
	buffer[21][6] = _s_dpi_levels[profile_1][4][0];
	buffer[21][7] = _s_dpi_levels[profile_1][4][1];
	buffer[21][9] = _s_dpi_levels[profile_1][4][2];

	// button mapping, two buttons per packet
	for( int i=0; i<12; i+=2 ){
		int j = 11+(i/2);
		
		buffer[j][6] = _s_keymap_data[profile_1][i][0];
		buffer[j][7] = _s_keymap_data[profile_1][i][1];
		buffer[j][8] = _s_keymap_data[profile_1][i][2];
		buffer[j][9] = _s_keymap_data[profile_1][i][3];
		
		buffer[j][10] = _s_keymap_data[profile_1][i+1][0];
		buffer[j][11] = _s_keymap_data[profile_1][i+1][1];
		buffer[j][12] = _s_keymap_data[profile_1][i+1][2];
		buffer[j][13] = _s_keymap_data[profile_1][i+1][3];
	}

	// TODO! remove, print hexdump of buffer
	for( int i = 0; i < rows; i++ ){
		std::cout << i << "\t: ";
		for( int j=0; j < 17; j++ ){
			std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[i][j] << " ";
		}
		std::cout << "\n";
	}

	
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
