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

//reader functions (get settings from mouse)

int mouse_m913::dump_settings( std::ostream& output ){
	int ret = 0;

	size_t rows = sizeof(_c_data_read) / sizeof(_c_data_read[0]);
	uint8_t buffer_in[17];
	for( size_t i = 0; i < rows; i++ ){
		ret += libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0308, 0x0001, _c_data_read[i], 17, 1000 );
		ret += libusb_interrupt_transfer( _i_handle, 0x82, buffer_in, 17, NULL, 1000 );

		for( size_t j = 0; j < 17; j++ )
			output << std::hex << std::setw(2) << std::setfill('0') << (int)buffer_in[j] << " ";
		output << "\n";
	}

	output << std::dec << std::setw(0) << std::setfill(' ');

	return ret;
}

int mouse_m913::read_and_print_settings( std::ostream& output ){
	int ret = 0;

	// read settings
	size_t rows = sizeof(_c_data_read) / sizeof(_c_data_read[0]);
	uint8_t buffer_in[rows][17];
	for( size_t i = 0; i < rows; i++ ){
		ret += libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0308, 0x0001, _c_data_read[i], 17, 1000 );
		ret += libusb_interrupt_transfer( _i_handle, 0x82, buffer_in[i], 17, NULL, 1000 );
	}

	// decode and print the settings
	output
		<< "# Configuration created with mouse_m908 -R.\n"
		<< "# This configuration can be send to the mouse with mouse_m908 -c.\n"
		<< "# Note: this feature is incomplete for the M913.\n\n";
	
	output << "# Currently active DPI level: " << (int)(buffer_in[2][6] + 1) << "\n";


	return ret;
}

int mouse_m913::read_settings(){
	// missing data
	return 0;
}
