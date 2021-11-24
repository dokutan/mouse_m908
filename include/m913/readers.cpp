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
	
	// battery level
	output << "# Battery level: ";
	if(buffer_in[68][6] <= 10)
		output << (int)(buffer_in[68][6] * 10) << " %\n\n";
	else
		output << "unkown, please report as a bug (" << (int)buffer_in[68][6] << ")\n\n";

	output
		<< "# The M913 has two profiles that can be switched using the 'mode switch' button on the bottom of the mouse.\n"
	 	<< "# Reading the settings can only be done for the active profile, therefore only profile1 is used in this config.\n"
		<< "[profile1]\n\n";

	output << "report_rate=";
	switch(buffer_in[4][6]){
		case 0x1: output << "1000\n"; break;
		case 0x2: output << "500\n"; break;
		case 0x4: output << "250\n"; break;
		case 0x8: output << "125\n"; break;
		default: output << "unknown\n"; break;
	}

	// DPI
	output << "\n# DPI settings\n";
	output << "# Currently active DPI level: " << (int)(buffer_in[2][6] + 1) << "\n";
	std::string dpi = "";
	_i_decode_dpi({buffer_in[5][8], buffer_in[5][9], buffer_in[5][11]}, dpi);
	output << "dpi1=" << dpi << "\n";
	_i_decode_dpi({buffer_in[5][12], buffer_in[5][13], buffer_in[5][15]}, dpi);
	output << "dpi2=" << dpi << "\n";
	_i_decode_dpi({buffer_in[6][6], buffer_in[6][7], buffer_in[6][9]}, dpi);
	output << "dpi3=" << dpi << "\n";
	_i_decode_dpi({buffer_in[6][10], buffer_in[6][11], buffer_in[6][13]}, dpi);
	output << "dpi4=" << dpi << "\n";
	_i_decode_dpi({buffer_in[6][14], buffer_in[6][15], buffer_in[7][7]}, dpi);
	output << "dpi5=" << dpi << "\n";

	// button mapping
	output << "\n# Button mapping\n";
	std::string mapping = "";

	_i_decode_button_mapping({buffer_in[16][10], buffer_in[16][11], buffer_in[16][12], buffer_in[16][13]}, mapping);
	output << "button_left=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[16][6], buffer_in[16][7], buffer_in[16][8], buffer_in[16][9]}, mapping);
	output << "button_right=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[17][12], buffer_in[17][13], buffer_in[17][14], buffer_in[17][15]}, mapping);
	output << "button_middle=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[18][6], buffer_in[18][7], buffer_in[18][8], buffer_in[18][9]}, mapping);
	output << "button_fire=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[13][12], buffer_in[13][13], buffer_in[13][14], buffer_in[13][15]}, mapping);
	output << "button_1=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[14][6], buffer_in[14][7], buffer_in[14][8], buffer_in[14][9]}, mapping);
	output << "button_2=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[14][10], buffer_in[14][11], buffer_in[14][12], buffer_in[14][13]}, mapping);
	output << "button_3=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[14][14], buffer_in[14][15], buffer_in[15][6], buffer_in[15][7]}, mapping);
	output << "button_4=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[15][8], buffer_in[15][9], buffer_in[15][10], buffer_in[15][11]}, mapping);
	output << "button_5=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[15][12], buffer_in[15][13], buffer_in[15][14], buffer_in[15][15]}, mapping);
	output << "button_6=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[16][14], buffer_in[16][15], buffer_in[17][6], buffer_in[17][7]}, mapping);
	output << "button_7=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[17][8], buffer_in[17][9], buffer_in[17][10], buffer_in[17][11]}, mapping);
	output << "button_8=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[18][10], buffer_in[18][11], buffer_in[18][12], buffer_in[18][13]}, mapping);
	output << "button_9=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[18][14], buffer_in[18][15], buffer_in[19][6], buffer_in[19][7]}, mapping);
	output << "button_10=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[19][8], buffer_in[19][9], buffer_in[19][10], buffer_in[19][11]}, mapping);
	output << "button_11=" << mapping << "\n";
	_i_decode_button_mapping({buffer_in[19][12], buffer_in[19][13], buffer_in[19][14], buffer_in[19][15]}, mapping);
	output << "button_12=" << mapping << "\n";

	return ret;
}

int mouse_m913::read_settings(){
	// currently not implemented
	return 1;
}
