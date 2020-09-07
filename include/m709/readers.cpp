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

#include "mouse_m709.h"

//reader functions (get settings from mouse)

int mouse_m709::dump_settings( std::ostream& output ){
	
	//prepare data 1
	int rows1 = sizeof(_c_data_read_1) / sizeof(_c_data_read_1[0]);
	uint8_t buffer1[rows1][16];
	for( int i = 0; i < rows1; i++ ){
		std::copy(std::begin(_c_data_read_1[i]), std::end(_c_data_read_1[i]), std::begin(buffer1[i]));
	}
	
	//prepare data 2
	int rows2 = sizeof(_c_data_read_2) / sizeof(_c_data_read_2[0]);
	uint8_t buffer2[rows2][64];
	for( int i = 0; i < rows2; i++ ){
		std::copy(std::begin(_c_data_read_2[i]), std::end(_c_data_read_2[i]), std::begin(buffer2[i]));
	}
	
	//prepare data 3
	int rows3 = sizeof(_c_data_read_3) / sizeof(_c_data_read_3[0]);
	uint8_t buffer3[rows3][16];
	for( int i = 0; i < rows3; i++ ){
		std::copy(std::begin(_c_data_read_3[i]), std::end(_c_data_read_3[i]), std::begin(buffer3[i]));
	}
	
	output << "Part 1:\n\n";
	
	//send data 1
	uint8_t buffer_in1[16];
	int num_bytes_in;
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[0], 16, 1000 );
	for( int i = 1; i < rows1; i++ ){
		// control out
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[i], 16, 1000 );
		
		// control in
		num_bytes_in = libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in1, 16, 1000 );
		
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
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0303, 0x0002, buffer2[i], 64, 1000 );
		
		// control in
		num_bytes_in = libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0303, 0x0002, buffer_in2, 64, 1000 );
		
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
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[i], 16, 1000 );
		
		// control in
		num_bytes_in = libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in3, 16, 1000 );
		
		// hexdump
		if ( num_bytes_in > 0 ){
			output << std::hex;
			for( int j = 0; j < num_bytes_in;  j++ ){
				output << std::setfill('0') << std::setw(2) << (int)buffer_in3[j] << " ";
			}
			output << "\n\n" << std::dec << std::setw(0) << std::setfill(' ');
		}
	}
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[100], 16, 1000 );
	
	return 0;
}

int mouse_m709::read_and_print_settings( std::ostream& output ){
	
	//prepare data 1
	int rows1 = sizeof(_c_data_read_1) / sizeof(_c_data_read_1[0]);
	uint8_t buffer1[rows1][16];
	for( int i = 0; i < rows1; i++ ){
		std::copy(std::begin(_c_data_read_1[i]), std::end(_c_data_read_1[i]), std::begin(buffer1[i]));
	}
	
	//prepare data 2
	int rows2 = sizeof(_c_data_read_2) / sizeof(_c_data_read_2[0]);
	uint8_t buffer2[rows2][64];
	for( int i = 0; i < rows2; i++ ){
		std::copy(std::begin(_c_data_read_2[i]), std::end(_c_data_read_2[i]), std::begin(buffer2[i]));
	}
	
	//prepare data 3
	int rows3 = sizeof(_c_data_read_3) / sizeof(_c_data_read_3[0]);
	uint8_t buffer3[rows3][16];
	for( int i = 0; i < rows3; i++ ){
		std::copy(std::begin(_c_data_read_3[i]), std::end(_c_data_read_3[i]), std::begin(buffer3[i]));
	}
	
	
	//send data 1
	uint8_t buffer_in1[8][16] = {{0}};
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[0], 16, 1000 );
	for( int i = 1; i < rows1; i++ ){
		// control out
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[i], 16, 1000 );
		
		// control in
		libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in1[i-1], 16, 1000 );
		
	}
	
	//send data 2
	uint8_t buffer_in2[85][64] = {{0}};
	for( int i = 0; i < rows2; i++ ){
		// control out
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0303, 0x0002, buffer2[i], 64, 1000 );
		
		// control in
		libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0303, 0x0002, buffer_in2[i], 64, 1000 );
		
	}
	
	//send data 3
	uint8_t buffer_in3[100][16] = {{0}};
	for( int i = 0; i < rows3-1; i++ ){
		// control out
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[i], 16, 1000 );
		
		// control in
		libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in3[i], 16, 1000 );
		
	}
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[100], 16, 1000 );
	
	
	// print configuration
	output << "# Configuration created with mouse_m908 -R.\n";
	output << "# This configuration can be send to the mouse with mouse_m908 -c.\n";
	output << "# This feature is currently untested, please report your results.\n";
	output << "# Note: reading the scrollspeed is not supported by the mouse.\n";
	output << "\n# Currently active profile: " << (int)buffer_in1[0][8]+1 << "\n";
	
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
		
		for( int j = 0; j < 8; j++ ){
			
			uint8_t b1 = buffer_in3[j+(8*(i-1))][8];
			uint8_t b2 = buffer_in3[j+(8*(i-1))][9];
			uint8_t b3 = buffer_in3[j+(8*(i-1))][10];
			uint8_t b4 = buffer_in3[j+(8*(i-1))][11];
			bool found_name = false;
			
			output << _c_button_names[j] << "=";
			
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
					
					// iterate over _c_keyboard_key_values
					for( auto keycode : _c_keyboard_key_values ){
						
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
				
				// iterate over _c_keyboard_key_values
				for( auto keycode : _c_keyboard_key_values ){
					
					if( keycode.second == b3 ){
						
						output << keycode.first << "\n";
						found_name = true;
						break;
						
					}
					
				}
				
			// modifiers + keyboard key
			} else if( b1 == 0x8f ){
				
				// iterate over _c_keyboard_modifier_values
				for( auto modifier : _c_keyboard_modifier_values ){
					
					if( modifier.second & b2 ){
						output << modifier.first;
					}
					
				}
				
				// iterate over _c_keyboard_key_values
				for( auto keycode : _c_keyboard_key_values ){
					
					if( keycode.second == b3 ){
						
						output << keycode.first << "\n";
						found_name = true;
						break;
						
					}
					
				}
				
			} else{ // mousebutton or special function ?
				
				// iterate over _c_keycodes
				for( auto keycode : _c_keycodes ){
					
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
	int macronumber = 1;
	int counter = 0;
	
	// iterate over buffer_in2
	for( int i = 5; i < 85; i++ ){
		
		// valid macronumber?
		if( macronumber >= 1 && macronumber <= 15 ){
			
			// extract bytes
			for( int j = 8; j < 58; j++ ){
				macro_bytes[macronumber-1].push_back( buffer_in2[i][j] );
			}
			
		}
		
		// increment counter and macronumber
		counter++;
		if( counter == 4 ){
			counter = 0;
			macronumber++;
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
				
				if( macro_bytes[i][j+1] == 0x01 )
					output << ";# down\tmouse_left\n";
				else if( macro_bytes[i][j+1] == 0x02 )
					output << ";# down\tmouse_right\n";
				else if( macro_bytes[i][j+1] == 0x04 )
					output << ";# down\tmouse_middle\n";
				else{
					output << ";# unknown, please report as bug: ";
					output << std::hex << (int)macro_bytes[i][j] << " ";
					output << std::hex << (int)macro_bytes[i][j+1] << " ";
					output << std::hex << (int)macro_bytes[i][j+2];
					output << std::dec << "\n";
				}
				
			} else if( macro_bytes[i][j] == 0x01 ){ // mouse button up
				
				if( macro_bytes[i][j+1] == 0x01 )
					output << ";# up\tmouse_left\n";
				else if( macro_bytes[i][j+1] == 0x02 )
					output << ";# up\tmouse_right\n";
				else if( macro_bytes[i][j+1] == 0x04 )
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
				
				// iterate over _c_keyboard_key_values
				for( auto keycode : _c_keyboard_key_values ){
					
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
				
				// iterate over _c_keyboard_key_values
				for( auto keycode : _c_keyboard_key_values ){
					
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

int mouse_m709::read_settings(){
	
	//prepare data 1
	int rows1 = sizeof(_c_data_read_1) / sizeof(_c_data_read_1[0]);
	uint8_t buffer1[rows1][16];
	for( int i = 0; i < rows1; i++ ){
		std::copy(std::begin(_c_data_read_1[i]), std::end(_c_data_read_1[i]), std::begin(buffer1[i]));
	}
	
	//prepare data 2
	int rows2 = sizeof(_c_data_read_2) / sizeof(_c_data_read_2[0]);
	uint8_t buffer2[rows2][64];
	for( int i = 0; i < rows2; i++ ){
		std::copy(std::begin(_c_data_read_2[i]), std::end(_c_data_read_2[i]), std::begin(buffer2[i]));
	}
	
	//prepare data 3
	int rows3 = sizeof(_c_data_read_3) / sizeof(_c_data_read_3[0]);
	uint8_t buffer3[rows3][16];
	for( int i = 0; i < rows3; i++ ){
		std::copy(std::begin(_c_data_read_3[i]), std::end(_c_data_read_3[i]), std::begin(buffer3[i]));
	}
	
	
	//send data 1
	uint8_t buffer_in1[8][16] = {{0}};
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[0], 16, 1000 );
	for( int i = 1; i < rows1; i++ ){
		// control out
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[i], 16, 1000 );
		
		// control in
		libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in1[i-1], 16, 1000 );
		
	}
	
	//send data 2
	uint8_t buffer_in2[85][64] = {{0}};
	for( int i = 0; i < rows2; i++ ){
		// control out
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0303, 0x0002, buffer2[i], 64, 1000 );
		
		// control in
		libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0303, 0x0002, buffer_in2[i], 64, 1000 );
		
	}
	
	//send data 3
	uint8_t buffer_in3[100][16] = {{0}};
	for( int i = 0; i < rows3-1; i++ ){
		// control out
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[i], 16, 1000 );
		
		// control in
		libusb_control_transfer( _i_handle, 0xa1, 0x01, 0x0302, 0x0002, buffer_in3[i], 16, 1000 );
		
	}
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[100], 16, 1000 );
	
	// parse received data
	
	if( buffer_in1[0][8]+1 == 1 )
		_s_profile = profile_1;
	if( buffer_in1[0][8]+1 == 2 )
		_s_profile = profile_2;
	if( buffer_in1[0][8]+1 == 3 )
		_s_profile = profile_3;
	if( buffer_in1[0][8]+1 == 4 )
		_s_profile = profile_4;
	if( buffer_in1[0][8]+1 == 5 )
		_s_profile = profile_5;
	
	for( int i = 1; i < 6; i++ ){
		
		// color
		_s_colors[i-1][0] = buffer_in1[i][8];
		_s_colors[i-1][1] = buffer_in1[i][9];
		_s_colors[i-1][2] = buffer_in1[i][10];
		
		// brightness
		_s_brightness_levels[i-1] = buffer_in1[i][14];
		
		// speed
		_s_speed_levels[i-1] = buffer_in1[i][13];
		
		// lightmode
		if( buffer_in1[i][11] == 0x00 && buffer_in1[i][13] == 0x00 )
			_s_lightmodes[i-1] = lightmode_off;
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x04 )
			_s_lightmodes[i-1] = lightmode_breathing;
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x08 )
			_s_lightmodes[i-1] = lightmode_rainbow;
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x02 )
			_s_lightmodes[i-1] = lightmode_static;
		else if( buffer_in1[i][11] == 0x02 && buffer_in1[i][13] == 0x00 )
			_s_lightmodes[i-1] = lightmode_wave;
		else if( buffer_in1[i][11] == 0x06 && buffer_in1[i][13] == 0x00 )
			_s_lightmodes[i-1] = lightmode_alternating;
		else if( buffer_in1[i][11] == 0x07 && buffer_in1[i][13] == 0x00 )
			_s_lightmodes[i-1] = lightmode_reactive;
		else if( buffer_in1[i][11] == 0x01 && buffer_in1[i][13] == 0x10 )
			_s_lightmodes[i-1] = lightmode_flashing;
		
		// polling rate (report rate)
		if( i < 4 ){
			
			if( buffer_in1[6][6+(2*i)] == 8 )
				_s_report_rates[i-1] = r_125Hz;
			else if( buffer_in1[6][6+(2*i)] == 4 )
				_s_report_rates[i-1] = r_250Hz;
			else if( buffer_in1[6][6+(2*i)] == 2 )
				_s_report_rates[i-1] = r_500Hz;
			else if( buffer_in1[6][6+(2*i)] == 1 )
				_s_report_rates[i-1] = r_1000Hz;
						
		} else{
			
			if( buffer_in1[7][(2*i)] == 8 )
				_s_report_rates[i-1] = r_125Hz;
			else if( buffer_in1[7][(2*i)] == 4 )
				_s_report_rates[i-1] = r_250Hz;
			else if( buffer_in1[7][(2*i)] == 2 )
				_s_report_rates[i-1] = r_500Hz;
			else if( buffer_in1[7][(2*i)] == 1 )
				_s_report_rates[i-1] = r_1000Hz;
			
		}
		
		
		// dpi
		for( int j = 1; j < 6; j++ ){
			
			if( buffer_in2[i-1][4+(6*j)] )
				_s_dpi_enabled[i-1][j-1] = true;
			else
				_s_dpi_enabled[i-1][j-1] = false;
			
			_s_dpi_levels[i-1][j-1] = buffer_in2[i-1][5+(6*j)];
			
		}
		
		// button mapping
		for( int j = 0; j < 8; j++ ){
			
			_s_keymap_data[i-1][j][0] = buffer_in3[j+(8*(i-1))][8];
			_s_keymap_data[i-1][j][1] = buffer_in3[j+(8*(i-1))][9];
			_s_keymap_data[i-1][j][2] = buffer_in3[j+(8*(i-1))][10];
			_s_keymap_data[i-1][j][3] = buffer_in3[j+(8*(i-1))][11];
			
		}
	}
	
	// macros
	
	// macros
	std::array< std::vector< uint8_t >, 15 > macro_bytes;
	int macronumber = 1;
	int counter = 0;
	
	// iterate over buffer_in2
	for( int i = 5; i < 85; i++ ){
		
		// This appears to be wrong
		//int macronumber = buffer_in2[i][3] - 0x63;
		
		// valid macronumber?
		if( macronumber >= 1 && macronumber <= 15 ){
			
			// extract bytes
			for( int j = 8; j < 58; j++ ){ // iterate over individual packet
				macro_bytes[macronumber-1].push_back( buffer_in2[i][j] );
			}
			
		}
		
		// increment counter and macronumber
		counter++;
		if( counter == 4 ){
			counter = 0;
			macronumber++;
		}
		
	}
	
	// store extracted bytes in _s_macro_data
	for( int i = 0; i < 15; i++ ){ // for each macro in macro_bytes
		
		// for each byte in the macro
		for( unsigned int j = 0; j < macro_bytes[i].size(); j++ ){
			
			// failsafe
			if( j >= (_s_macro_data[i].size()+8) )
				break;
			
			_s_macro_data[i][j+8] = macro_bytes[i][j];
			
		}
		
	}
	
	return 0;
}
