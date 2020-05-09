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

#include "mouse_m908.h"

//reader functions (get settings from mouse)

int mouse_m908::dump_settings(){
	
	//prepare data 1
	int rows1 = sizeof(_data_read_1) / sizeof(_data_read_1[0]);
	uint8_t buffer1[rows1][16];
	for( int i = 0; i < rows1; i++ ){
		std::copy(std::begin(_data_read_1[i]), std::end(_data_read_1[i]), std::begin(buffer1[i]));
	}
	
	//prepare data 2
	int rows2 = sizeof(_data_read_2) / sizeof(_data_read_2[0]);
	uint8_t buffer2[rows2][64];
	for( int i = 0; i < rows2; i++ ){
		std::copy(std::begin(_data_read_2[i]), std::end(_data_read_2[i]), std::begin(buffer2[i]));
	}
	
	//prepare data 3
	int rows3 = sizeof(_data_read_3) / sizeof(_data_read_3[0]);
	uint8_t buffer3[rows3][16];
	for( int i = 0; i < rows3; i++ ){
		std::copy(std::begin(_data_read_3[i]), std::end(_data_read_3[i]), std::begin(buffer3[i]));
	}
	
	
	//send data 1
	uint8_t buffer_in1[16];
	int num_bytes_in;
	libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[0], 16, 1000 );
	for( int i = 1; i < rows1; i++ ){
		// control out
		libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[i], 16, 1000 );
		
		// control in
		num_bytes_in = libusb_control_transfer( _handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in1, 16, 1000 );
		
		// hexdump
		if ( num_bytes_in > 0 ){
			std::cout << std::hex;
			for( int j = 0; j < num_bytes_in;  j++ ){
				std::cout << (int)buffer_in1[j] << " ";
			}
			std::cout << "\n\n" << std::dec;
		}
	}
	
	//send data 2
	uint8_t buffer_in2[64];
	for( int i = 0; i < rows2; i++ ){
		// control out
		libusb_control_transfer( _handle, 0x21, 0x09, 0x0303, 0x0002, buffer2[i], 64, 1000 );
		
		// control in
		num_bytes_in = libusb_control_transfer( _handle, 0xa1, 0x01, 0x0303, 0x0002, buffer_in2, 64, 1000 );
		
		// hexdump
		if ( num_bytes_in > 0 ){
			std::cout << std::hex;
			for( int j = 0; j < num_bytes_in;  j++ ){
				std::cout << (int)buffer_in2[j] << " ";
			}
			std::cout << "\n\n" << std::dec;
		}
	}
	
	//send data 3
	uint8_t buffer_in3[16];
	for( int i = 0; i < rows3-1; i++ ){
		// control out
		libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[i], 16, 1000 );
		
		// control in
		num_bytes_in = libusb_control_transfer( _handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in3, 16, 1000 );
		
		// hexdump
		if ( num_bytes_in > 0 ){
			std::cout << std::hex;
			for( int j = 0; j < num_bytes_in;  j++ ){
				std::cout << (int)buffer_in3[j] << " ";
			}
			std::cout << "\n\n" << std::dec;
		}
	}
	libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[100], 16, 1000 );
	
	return 0;
}

int mouse_m908::read_settings(){
	
	//prepare data 1
	int rows1 = sizeof(_data_read_1) / sizeof(_data_read_1[0]);
	uint8_t buffer1[rows1][16];
	for( int i = 0; i < rows1; i++ ){
		std::copy(std::begin(_data_read_1[i]), std::end(_data_read_1[i]), std::begin(buffer1[i]));
	}
	
	//prepare data 2
	int rows2 = sizeof(_data_read_2) / sizeof(_data_read_2[0]);
	uint8_t buffer2[rows2][64];
	for( int i = 0; i < rows2; i++ ){
		std::copy(std::begin(_data_read_2[i]), std::end(_data_read_2[i]), std::begin(buffer2[i]));
	}
	
	//prepare data 3
	int rows3 = sizeof(_data_read_3) / sizeof(_data_read_3[0]);
	uint8_t buffer3[rows3][16];
	for( int i = 0; i < rows3; i++ ){
		std::copy(std::begin(_data_read_3[i]), std::end(_data_read_3[i]), std::begin(buffer3[i]));
	}
	
	
	//send data 1
	uint8_t buffer_in1[8][16] = {0};
	libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[0], 16, 1000 );
	for( int i = 1; i < rows1; i++ ){
		// control out
		libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[i], 16, 1000 );
		
		// control in
		libusb_control_transfer( _handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in1[i-1], 16, 1000 );
		
	}
	
	//send data 2
	uint8_t buffer_in2[85][64] = {0};
	for( int i = 0; i < rows2; i++ ){
		// control out
		libusb_control_transfer( _handle, 0x21, 0x09, 0x0303, 0x0002, buffer2[i], 64, 1000 );
		
		// control in
		libusb_control_transfer( _handle, 0xa1, 0x01, 0x0303, 0x0002, buffer_in2[i], 64, 1000 );
		
	}
	
	//send data 3
	uint8_t buffer_in3[100][16] = {0};
	for( int i = 0; i < rows3-1; i++ ){
		// control out
		libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[i], 16, 1000 );
		
		// control in
		libusb_control_transfer( _handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in3[i], 16, 1000 );
		
	}
	libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[100], 16, 1000 );
	
	
	// print configuration
	std::cout << "# Configuration created with mouse_m908 -R.\n";
	std::cout << "# This function is experimental, not all settings are read.\n";
	std::cout << "# Currently active profile: " << (int)buffer_in1[0][8]+1 << "\n";
	
	for( int i = 1; i < 6; i++ ){
		
		// section header
		std::cout << "\n[profile" << i << "]\n";
		
		// color
		std::cout << "color=";
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)buffer_in1[i][8];
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)buffer_in1[i][9];
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)buffer_in1[i][10];
		std::cout << std::setfill(' ') << std::setw(0) << std::dec << "\n";
		
		// brightness
		std::cout << "brightness=" << (int)buffer_in1[i][14] << "\n";
		
		// speed
		std::cout << "speed=" << (int)buffer_in1[i][13] << "\n";
		
		// lightmode
		std::cout << "lightmode=";
		if( buffer_in1[i][11] == 0x00 && buffer_in1[i][13] == 0x00 )
			std::cout << "off\n";
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x04 )
			std::cout << "breathing\n";
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x08 )
			std::cout << "rainbow\n";
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x02 )
			std::cout << "static\n";
		else if( buffer_in1[i][11] == 0x02 && buffer_in1[i][13] == 0x00 )
			std::cout << "wave\n";
		else if( buffer_in1[i][11] == 0x06 && buffer_in1[i][13] == 0x00 )
			std::cout << "alternating\n";
		else if( buffer_in1[i][11] == 0x07 && buffer_in1[i][13] == 0x00 )
			std::cout << "reactive\n";
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x10 )
			std::cout << "flashing\n";
		else
			std::cout << "unknown\n";
		
		
	}
	
	return 0;
}
