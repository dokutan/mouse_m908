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

int mouse_m908::dump_settings( std::ostream& output ){
	
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
	
	output << "Part 1:\n\n";
	
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
			output << std::hex;
			for( int j = 0; j < num_bytes_in;  j++ ){
				output << std::setfill('0') << std::setw(2) << (int)buffer_in1[j] << " ";
			}
			output << "\n\n" << std::dec << std::setw(0) << std::setfill(' ');
		}
	}
	
	output << "Part 2:\n\n";
	
	//send data 2
	uint8_t buffer_in2[64];
	for( int i = 0; i < rows2; i++ ){
		// control out
		libusb_control_transfer( _handle, 0x21, 0x09, 0x0303, 0x0002, buffer2[i], 64, 1000 );
		
		// control in
		num_bytes_in = libusb_control_transfer( _handle, 0xa1, 0x01, 0x0303, 0x0002, buffer_in2, 64, 1000 );
		
		// hexdump
		if ( num_bytes_in > 0 ){
			output << std::hex;
			for( int j = 0; j < num_bytes_in;  j++ ){
				output << std::setfill('0') << std::setw(2) << (int)buffer_in2[j] << " ";
			}
			output << "\n\n" << std::dec << std::setw(0) << std::setfill(' ');
		}
	}
	
	output << "Part 3:\n\n";
	
	//send data 3
	uint8_t buffer_in3[16];
	for( int i = 0; i < rows3-1; i++ ){
		// control out
		libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[i], 16, 1000 );
		
		// control in
		num_bytes_in = libusb_control_transfer( _handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in3, 16, 1000 );
		
		// hexdump
		if ( num_bytes_in > 0 ){
			output << std::hex;
			for( int j = 0; j < num_bytes_in;  j++ ){
				output << std::setfill('0') << std::setw(2) << (int)buffer_in3[j] << " ";
			}
			output << "\n\n" << std::dec << std::setw(0) << std::setfill(' ');
		}
	}
	libusb_control_transfer( _handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[100], 16, 1000 );
	
	return 0;
}

int mouse_m908::read_and_print_settings( std::ostream& output ){
	
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
	output << "# Configuration created with mouse_m908 -R.\n";
	output << "# This function is experimental, not all settings are read.\n";
	output << "# Currently active profile: " << (int)buffer_in1[0][8]+1 << "\n";
	
	for( int i = 1; i < 6; i++ ){
		
		// section header
		output << "\n[profile" << i << "]\n";
		
		output << "\n# LED settings\n";
		
		// color
		output << "color=";
		output << std::setfill('0') << std::setw(2) << std::hex << (int)buffer_in1[i][8];
		output << std::setfill('0') << std::setw(2) << std::hex << (int)buffer_in1[i][9];
		output << std::setfill('0') << std::setw(2) << std::hex << (int)buffer_in1[i][10];
		output << std::setfill(' ') << std::setw(0) << std::dec << "\n";
		
		// brightness
		output << "brightness=" << (int)buffer_in1[i][14] << "\n";
		
		// speed
		output << "speed=" << (int)buffer_in1[i][13] << "\n";
		
		// lightmode
		output << "lightmode=";
		if( buffer_in1[i][11] == 0x00 && buffer_in1[i][13] == 0x00 )
			output << "off\n";
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x04 )
			output << "breathing\n";
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x08 )
			output << "rainbow\n";
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x02 )
			output << "static\n";
		else if( buffer_in1[i][11] == 0x02 && buffer_in1[i][13] == 0x00 )
			output << "wave\n";
		else if( buffer_in1[i][11] == 0x06 && buffer_in1[i][13] == 0x00 )
			output << "alternating\n";
		else if( buffer_in1[i][11] == 0x07 && buffer_in1[i][13] == 0x00 )
			output << "reactive\n";
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x10 )
			output << "flashing\n";
		else{
			output << "unknown, please report as bug: ";
			output << std::hex << buffer_in1[i][11] << " ";
			output << std::hex << buffer_in1[i][13] << std::dec << "\n";
		}
		
		// polling rate (report rate)
		if( i < 4 ){
			
			output << "\n";
			
			if( buffer_in1[6][6+(2*i)] == 8 )
				output << "report_rate=125\n";
			else if( buffer_in1[6][6+(2*i)] == 4 )
				output << "report_rate=250\n";
			else if( buffer_in1[6][6+(2*i)] == 2 )
				output << "report_rate=500\n";
			else if( buffer_in1[6][6+(2*i)] == 1 )
				output << "report_rate=1000\n";
			else{
				output << "# report rate unknown, please report as bug: "
					<< (int)buffer_in1[6][6+(2*i)] << "\n";
			}
			
		} else{
			
			output << "\n";
			
			if( buffer_in1[7][(2*i)] == 8 )
				output << "report_rate=125\n";
			else if( buffer_in1[7][(2*i)] == 4 )
				output << "report_rate=250\n";
			else if( buffer_in1[7][(2*i)] == 2 )
				output << "report_rate=500\n";
			else if( buffer_in1[7][(2*i)] == 1 )
				output << "report_rate=1000\n";
			else{
				output << "# report rate unknown, please report as bug: "
					<< (int)buffer_in1[7][(2*i)] << "\n";
			}
			
		}
		
		
		// dpi
		output << "\n# DPI settings\n";
		output << "# Active dpi level for this profile: " << (int)buffer_in2[i-1][8]+1 << "\n";
		for( int j = 1; j < 6; j++ ){
			output << "dpi" << j << "_enable=" << (int)buffer_in2[i-1][4+(6*j)] << "\n";
			output << std::setfill('0') << std::setw(2) << std::hex;
			output << "dpi" << j << "=" << (int)buffer_in2[i-1][5+(6*j)] << "\n";
			output << std::setfill(' ') << std::setw(0) << std::dec;
		}
		
		// button mapping
		output << "\n# Button mapping\n";
		std::map< int, std::string > button_names = {
			{ 0, "button_left" },
			{ 1, "button_right" },
			{ 2, "button_middle" },
			{ 3, "button_fire" },
			{ 4, "button_dpi_up" },
			{ 5, "button_dpi_down" },
			{ 6, "button_1" },
			{ 7, "button_2" },
			{ 8, "button_3" },
			{ 9, "button_4" },
			{ 10, "button_5" },
			{ 11, "button_6" },
			{ 12, "button_7" },
			{ 13, "button_8" },
			{ 14, "button_9" },
			{ 15, "button_10" },
			{ 16, "button_11" },
			{ 17, "button_12" },
			{ 18, "scroll_up" },
			{ 19, "scroll_down" } };
		
		for( int j = 0; j < 20; j++ ){
			
			uint8_t b1 = buffer_in3[j+(20*(i-1))][8];
			uint8_t b2 = buffer_in3[j+(20*(i-1))][9];
			uint8_t b3 = buffer_in3[j+(20*(i-1))][10];
			uint8_t b4 = buffer_in3[j+(20*(i-1))][11];
			bool found_name = false;
			
			output << button_names[j] << "=";
			
			// fire button
			if( b1 == 0x99 ){
				
				output << "fire:";
				
				// button
				if( b2 == 0x81 )
					output << "mouse_left:";
				else if( b2 == 0x82 )
					output << "mouse_right:";
				else if( b2 == 0x84 )
					output << "mouse_middle:";
				else{
					
					// iterate over _keyboard_key_values
					for( auto keycode : _keyboard_key_values ){
						
						if( keycode.second == b2 ){
							
							output << keycode.first;
							break;
							
						}
						
					}
					output << ":";
				}
				
				// repeats
				output << (int)b3 << ":";
				
				// delay
				output << (int)b4 << "\n";
				
				found_name = true;
				
			// keyboard key
			} else if( b1 == 0x90 ){
				
				// iterate over _keyboard_key_values
				for( auto keycode : _keyboard_key_values ){
					
					if( keycode.second == b3 ){
						
						output << keycode.first << "\n";
						found_name = true;
						break;
						
					}
					
				}
				
			// modifiers + keyboard key
			} else if( b1 == 0x8f ){
				
				// iterate over _keyboard_modifier_values
				for( auto modifier : _keyboard_modifier_values ){
					
					if( modifier.second & b2 ){
						output << modifier.first;
					}
					
				}
				
				// iterate over _keyboard_key_values
				for( auto keycode : _keyboard_key_values ){
					
					if( keycode.second == b3 ){
						
						output << keycode.first << "\n";
						found_name = true;
						break;
						
					}
					
				}
				
			} else{ // mousebutton or special function ?
				
				// iterate over _keycodes
				for( auto keycode : _keycodes ){
					
					if( keycode.second[0] == b1 &&
						keycode.second[1] == b2 && 
						keycode.second[2] == b3 ){
						
						output << keycode.first << "\n";
						found_name = true;
						break;
						
					}
					
				}
				
			}
			
			if( !found_name ){
				output << "unknown, please report as bug: ";
				output << " " << std::hex << (int)b1 << " ";
				output << " " << std::hex << (int)b2 << " ";
				output << " " << std::hex << (int)b3 << " ";
				output << " " << std::hex << (int)b4;
				output << std::dec << "\n";
			}
			
		}
	}
	
	// macros
	std::array< std::vector< uint8_t >, 15 > macro_bytes;
	
	// iterate over buffer_in2
	for( int i = 5; i < 85; i++ ){
		
		int macronumber = buffer_in2[i][3] - 0x63;
		
		// valid macronumber?
		if( macronumber >= 1 && macronumber <= 15 ){
			
			// extract bytes
			for( int j = 8; j < 58; j++ ){
				macro_bytes[macronumber-1].push_back( buffer_in2[i][j] );
			}
			
		}
		
	}
	
	// decode macros
	output << "\n# Macros\n";
	for( int i = 0; i < 15; i++ ){
		
		// macro undefined?
		if( macro_bytes[i][0] == 0 && macro_bytes[i][1] == 0 && macro_bytes[i][2] == 0 )
			continue;
		
		output << "\n;## macro" << i+1 << "\n";
		
		for( long unsigned int j = 0; j < macro_bytes[i].size(); ){
			
			// failsafe
			if( j >= macro_bytes[i].size() )
				break;
			
			if( macro_bytes[i][j] == 0x81 ){ // mouse button down
				
				if( macro_bytes[i][j] == 0x01 )
					output << ";# down\tmouse_left\n";
				else if( macro_bytes[i][j] == 0x02 )
					output << ";# down\tmouse_right\n";
				else if( macro_bytes[i][j] == 0x04 )
					output << ";# down\tmouse_middle\n";
				else{
					output << ";# unknown, please report as bug: ";
					output << std::hex << (int)macro_bytes[i][j] << " ";
					output << std::hex << (int)macro_bytes[i][j+1] << " ";
					output << std::hex << (int)macro_bytes[i][j+2];
					output << std::dec << "\n";
				}
				
			} else if( macro_bytes[i][j] == 0x01 ){ // mouse button up
				
				if( macro_bytes[i][j] == 0x01 )
					output << ";# up\tmouse_left\n";
				else if( macro_bytes[i][j] == 0x02 )
					output << ";# up\tmouse_right\n";
				else if( macro_bytes[i][j] == 0x04 )
					output << ";# up\tmouse_middle\n";
				else{
					output << ";# unknown, please report as bug: ";
					output << std::hex << (int)macro_bytes[i][j] << " ";
					output << std::hex << (int)macro_bytes[i][j+1] << " ";
					output << std::hex << (int)macro_bytes[i][j+2];
					output << std::dec << "\n";
				}
				
			} else if( macro_bytes[i][j] == 0x84 ){ // keyboard key down
				
				bool found_name = false;
				
				// iterate over _keyboard_key_values
				for( auto keycode : _keyboard_key_values ){
					
					if( keycode.second == macro_bytes[i][j+1] ){
						
						output << ";# down\t" << keycode.first << "\n";
						found_name = true;
						break;
						
					}
					
				}
				
				if( !found_name ){
					output << ";# unknown, please report as bug: ";
					output << std::hex << (int)macro_bytes[i][j] << " ";
					output << std::hex << (int)macro_bytes[i][j+1] << " ";
					output << std::hex << (int)macro_bytes[i][j+2];
					output << std::dec << "\n";
				}
				
			} else if( macro_bytes[i][j] == 0x04 ){ // keyboard key up
				
				bool found_name = false;
				
				// iterate over _keyboard_key_values
				for( auto keycode : _keyboard_key_values ){
					
					if( keycode.second == macro_bytes[i][j+1] ){
						
						output << ";# up\t" << keycode.first << "\n";
						found_name = true;
						break;
						
					}
					
				}
				
				if( !found_name ){
					output << ";# unknown, please report as bug: ";
					output << std::hex << (int)macro_bytes[i][j] << " ";
					output << std::hex << (int)macro_bytes[i][j+1] << " ";
					output << std::hex << (int)macro_bytes[i][j+2];
					output << std::dec << "\n";
				}
				
			} else if( macro_bytes[i][j] == 0x06 ){ // delay
				
				output << ";# delay\t" << (int)macro_bytes[i][j+1] << "\n";
				
			} else if( macro_bytes[i][j] == 0x00 ){ // padding
				
				j++;
				
			} else{
				output << ";# unknown, please report as bug: ";
				output << std::hex << (int)macro_bytes[i][j] << " ";
				output << std::hex << (int)macro_bytes[i][j+1] << " ";
				output << std::hex << (int)macro_bytes[i][j+2];
				output << std::dec << "\n";
			}
			
			// increment
			j+=3;
			
		}
		
	}
	
	return 0;
}
