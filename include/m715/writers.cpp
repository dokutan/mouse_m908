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

#include "mouse_m715.h"

//writer functions (apply changes to mouse)

int mouse_m715::write_profile(){
	
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

int mouse_m715::write_settings(){
	
	//prepare data 1
	int rows1 = sizeof(_c_data_settings_1) / sizeof(_c_data_settings_1[0]);
	uint8_t buffer1[rows1][16];
	for( int i = 0; i < rows1; i++ ){
		std::copy(std::begin(_c_data_settings_1[i]), std::end(_c_data_settings_1[i]), std::begin(buffer1[i]));
	}
	
	/* Currently no data capture available
	 * 
	//prepare data 2
	uint8_t buffer2[64];
	std::copy(std::begin(_c_data_settings_2), std::end(_c_data_settings_2), std::begin(buffer2));
	
	//prepare data 3
	int rows3 = sizeof(_c_data_settings_3) / sizeof(_c_data_settings_3[0]);
	uint8_t buffer3[rows3][16];
	for( int i = 0; i < rows3; i++ ){
		std::copy(std::begin(_c_data_settings_3[i]), std::end(_c_data_settings_3[i]), std::begin(buffer3[i]));
	}
	* 
	*/
	
	//modify buffers to include settings
	
	/* Currently no data capture available
	 * 
	//scrollspeed
	for( int i = 0; i < 5; i++ ){
		buffer2[8+(2*i)] = _s_scrollspeeds[i];
	}
	* 
	*/
	
	//lightmode
	for( int i = 0; i < 5; i++ ){
		switch( _s_lightmodes[i] ){
			case lightmode_breathing:
				buffer1[1+(2*i)][11] = 0x01;
				buffer1[1+(2*i)][13] = 0x04;
				break;
			case lightmode_rainbow:
				buffer1[1+(2*i)][11] = 0x01;
				buffer1[1+(2*i)][13] = 0x08;
				break;
			case lightmode_static:
			default:
				buffer1[1+(2*i)][11] = 0x01;
				buffer1[1+(2*i)][13] = 0x02;
				break;
			case lightmode_wave:
				buffer1[1+(2*i)][11] = 0x02;
				buffer1[1+(2*i)][13] = 0x00;
				break;
			case lightmode_alternating:
				buffer1[1+(2*i)][11] = 0x06;
				buffer1[1+(2*i)][13] = 0x00;
				break;
			case lightmode_reactive:
				buffer1[1+(2*i)][11] = 0x07;
				buffer1[1+(2*i)][13] = 0x00;
				break;
			case lightmode_flashing:
				buffer1[1+(2*i)][11] = 0x01;
				buffer1[1+(2*i)][13] = 0x10;
				break;
			case lightmode_off:
				buffer1[1+(2*i)][11] = 0x00;
				buffer1[1+(2*i)][13] = 0x00;
				break;
		}
	}
	//color
	for( int i = 0; i < 5; i++ ){
		buffer1[1+(2*i)][8] = _s_colors[i].at(0);
		buffer1[1+(2*i)][9] = _s_colors[i].at(1);
		buffer1[1+(2*i)][10] = _s_colors[i].at(2);
	}
	//brightness
	for( int i = 0; i < 5; i++ ){
		buffer1[2+(2*i)][8] = _s_brightness_levels[i];
	}
	//speed
	for( int i = 0; i < 5; i++ ){
		buffer1[1+(2*i)][12] = _s_speed_levels[i];
	}
	
	/* Currently no data capture available
	 * 
	//dpi
	for( int i = 0; i < 5; i++ ){
		for( int j = 0; j < 5; j++ ){
			buffer3[7+(5*i)+j][8] = _s_dpi_enabled[j][i];
			buffer3[7+(5*i)+j][9] = _s_dpi_levels[j][i][0];
			buffer3[7+(5*i)+j][10] = _s_dpi_levels[j][i][1];
		}
	}
	
	//key mapping
	for( int i = 0; i < 5; i++ ){
		for( int j = 0; j < 8; j++ ){
			buffer3[35+(8*i)+j][8] = _s_keymap_data[i][j][0];
			buffer3[35+(8*i)+j][9] = _s_keymap_data[i][j][1];
			buffer3[35+(8*i)+j][10] = _s_keymap_data[i][j][2];
			buffer3[35+(8*i)+j][11] = _s_keymap_data[i][j][3];
			//std::cout << (int)_s_keymap_data[i][j][0] << " " << (int)_s_keymap_data[i][j][1] << " " << (int)_s_keymap_data[i][j][2] << " " << (int)_s_keymap_data[i][j][3] << "\n";
		}
	}
	* 
	*/
	
	/* Currently no data capture available
	 * 
	//usb report rate
	for( int i = 0; i < 3; i++ ){
		switch( _s_report_rates[i] ){
			default:
			case r_125Hz:
				buffer1[13][8+(2*i)] = 0x08; break;
			case r_250Hz:
				buffer1[13][8+(2*i)] = 0x04; break;
			case r_500Hz:
				buffer1[13][8+(2*i)] = 0x02; break;
			case r_1000Hz:
				buffer1[13][8+(2*i)] = 0x01; break;
		}
	}
	for( int i = 3; i < 5; i++ ){
		switch( _s_report_rates[i] ){
			default:
			case r_125Hz:
				buffer1[14][2+(2*i)] = 0x08; break;
			case r_250Hz:
				buffer1[14][2+(2*i)] = 0x04; break;
			case r_500Hz:
				buffer1[14][2+(2*i)] = 0x02; break;
			case r_1000Hz:
				buffer1[14][2+(2*i)] = 0x01; break;
		}
	}
	*
	*/
	
	//send data 1
	for( int i = 0; i < rows1; i++ ){
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer1[i], 16, 1000 );
	}
	
	/* Currently no data capture available
	 * 
	//send data 2
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer2, 64, 1000 );
	
	//send data 3
	for( int i = 0; i < rows3; i++ ){
		libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer3[i], 16, 1000 );
	}
	* 
	*/
	
	return 0;
}

int mouse_m715::write_macro( int macro_number ){
	
	//check if macro_number is valid
	if( macro_number < 1 || macro_number > 15 ){
		return 1;
	}
	
	//prepare data 1
	uint8_t buffer1[16];
	std::copy(std::begin(_c_data_macros_1), std::end(_c_data_macros_1), std::begin(buffer1));
	
	//prepare data 2
	uint8_t buffer2[265];
	std::copy(std::begin(_s_macro_data[macro_number-1]), std::end(_s_macro_data[macro_number-1]), std::begin(buffer2));
	
	//prepare data 3
	uint8_t buffer3[16];
	std::copy(std::begin(_c_data_macros_3), std::end(_c_data_macros_3), std::begin(buffer3));
	
	//send data 1
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer1, 16, 1000 );
	
	//send data 2
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer2, 256, 1000 );
	
	//send data 3
	libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0302, 0x0002, buffer3, 16, 1000 );
	
	return 0;
}
