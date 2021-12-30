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



int mouse_m686::write_profile(){
	// missing data
	throw std::string( "Changing profiles is not support for the M686, use the 'mode switch' button on the mouse instead." );
	return 0;
}

int mouse_m686::write_data(uint8_t data[][17], size_t rows){
	int ret = 0;
	uint8_t buffer_in[17];

	for( size_t i = 0; i < rows; i++ ){
		ret += libusb_control_transfer( _i_handle, 0x21, 0x09, 0x0308, 0x0001, data[i], 17, 1000 );
		ret += libusb_interrupt_transfer( _i_handle, 0x82, buffer_in, 17, NULL, 1000 );
	}

	return ret;
}

int mouse_m686::write_button_mapping( m686_profile profile ){
	int ret = 0;

	// part 1 (unknown function)
	size_t rows_1 = sizeof(_c_data_unknown_1) / sizeof(_c_data_unknown_1[0]);
	uint8_t buffer_1[rows_1][17];
	for( size_t i = 0; i < rows_1; i++ ){
		std::copy(std::begin(_c_data_unknown_1[i]), std::end(_c_data_unknown_1[i]), std::begin(buffer_1[i]));
	}
	ret += write_data(buffer_1, rows_1);

	// part 2 (button mapping)
	size_t rows_2 = sizeof(_c_data_button_mapping) / sizeof(_c_data_button_mapping[0]);
	uint8_t buffer_2[rows_2][17];
	for( size_t i = 0; i < rows_2; i++ ){
		std::copy(std::begin(_c_data_button_mapping[i]), std::end(_c_data_button_mapping[i]), std::begin(buffer_2[i]));
	}

	// two buttons per packet
	for( int i=0; i<12; i+=2 ){
		int j = i/2;

		buffer_2[j][6] = _s_keymap_data[profile][i][0];
		buffer_2[j][7] = _s_keymap_data[profile][i][1];
		buffer_2[j][8] = _s_keymap_data[profile][i][2];
		buffer_2[j][9] = _s_keymap_data[profile][i][3];
		
		buffer_2[j][10] = _s_keymap_data[profile][i+1][0];
		buffer_2[j][11] = _s_keymap_data[profile][i+1][1];
		buffer_2[j][12] = _s_keymap_data[profile][i+1][2];
		buffer_2[j][13] = _s_keymap_data[profile][i+1][3];
	}

	ret += write_data(buffer_2, rows_2);

	return ret;
}

int mouse_m686::write_dpi_settings( m686_profile profile ){
	int ret = 0;

	// part 1 (DPI)
	size_t rows_1 = sizeof(_c_data_dpi) / sizeof(_c_data_dpi[0]);
	uint8_t buffer_1[rows_1][17];
	for( size_t i = 0; i < rows_1; i++ ){
		std::copy(std::begin(_c_data_dpi[i]), std::end(_c_data_dpi[i]), std::begin(buffer_1[i]));
	}

	// DPI level 1
	buffer_1[0][6] = _s_dpi_levels[profile][0][0];
	buffer_1[0][7] = _s_dpi_levels[profile][0][1];
	buffer_1[0][9] = _s_dpi_levels[profile][0][2];
	// DPI level 2
	buffer_1[0][10] = _s_dpi_levels[profile][1][0];
	buffer_1[0][11] = _s_dpi_levels[profile][1][1];
	buffer_1[0][13] = _s_dpi_levels[profile][1][2];
	// DPI level 3
	buffer_1[1][6] = _s_dpi_levels[profile][2][0];
	buffer_1[1][7] = _s_dpi_levels[profile][2][1];
	buffer_1[1][9] = _s_dpi_levels[profile][2][2];
	// DPI level 4
	buffer_1[1][10] = _s_dpi_levels[profile][3][0];
	buffer_1[1][11] = _s_dpi_levels[profile][3][1];
	buffer_1[1][13] = _s_dpi_levels[profile][3][2];
	// DPI level 5
	buffer_1[2][6] = _s_dpi_levels[profile][4][0];
	buffer_1[2][7] = _s_dpi_levels[profile][4][1];
	buffer_1[2][9] = _s_dpi_levels[profile][4][2];

	// enabled DPI levels
	uint8_t enabled_dpi_levels_1 = 0x05;
	uint8_t enabled_dpi_levels_2 = 0x50;
	if(!_s_dpi_enabled.at(profile).at(4)){
		enabled_dpi_levels_1 = 0x04;
		enabled_dpi_levels_2 = 0x51;
	}
	if(!_s_dpi_enabled.at(profile).at(3)){
		enabled_dpi_levels_1 = 0x03;
		enabled_dpi_levels_2 = 0x52;
	}
	if(!_s_dpi_enabled.at(profile).at(2)){
		enabled_dpi_levels_1 = 0x02;
		enabled_dpi_levels_2 = 0x53;
	}
	if(!_s_dpi_enabled.at(profile).at(1)){
		enabled_dpi_levels_1 = 0x01;
		enabled_dpi_levels_2 = 0x54;
	}
	buffer_1[3][6] = enabled_dpi_levels_1;
	buffer_1[3][7] = enabled_dpi_levels_2;


	ret += write_data(buffer_1, rows_1);

	// part 2 (unknown function)
	size_t rows_2 = sizeof(_c_data_unknown_2) / sizeof(_c_data_unknown_2[0]);
	uint8_t buffer_2[rows_2][17];
	for( size_t i = 0; i < rows_2; i++ ){
		std::copy(std::begin(_c_data_unknown_2[i]), std::end(_c_data_unknown_2[i]), std::begin(buffer_2[i]));
	}
	ret += write_data(buffer_2, rows_2);

	return ret;
}

int mouse_m686::write_led_settings( m686_profile profile ){
	int ret = 0;

	if(_s_lightmodes.at(profile) == mouse_m686::m686_lightmode::lightmode_off){

		// part 1 (LED settings)
		size_t rows_1 = sizeof(_c_data_led_off) / sizeof(_c_data_led_off[0]);
		uint8_t buffer_1[rows_1][17];
		for( size_t i = 0; i < rows_1; i++ ){
			std::copy(std::begin(_c_data_led_off[i]), std::end(_c_data_led_off[i]), std::begin(buffer_1[i]));
		}

		ret += write_data(buffer_1, rows_1);

	}else if(_s_lightmodes.at(profile) == mouse_m686::m686_lightmode::lightmode_breathing){

		// part 1 (LED settings)
		size_t rows_1 = sizeof(_c_data_led_breathing) / sizeof(_c_data_led_breathing[0]);
		uint8_t buffer_1[rows_1][17];
		for( size_t i = 0; i < rows_1; i++ ){
			std::copy(std::begin(_c_data_led_breathing[i]), std::end(_c_data_led_breathing[i]), std::begin(buffer_1[i]));
		}

		ret += write_data(buffer_1, rows_1);

	}else if(_s_lightmodes.at(profile) == mouse_m686::m686_lightmode::lightmode_rainbow){

		// part 1 (LED settings)
		size_t rows_1 = sizeof(_c_data_led_rainbow) / sizeof(_c_data_led_rainbow[0]);
		uint8_t buffer_1[rows_1][17];
		for( size_t i = 0; i < rows_1; i++ ){
			std::copy(std::begin(_c_data_led_rainbow[i]), std::end(_c_data_led_rainbow[i]), std::begin(buffer_1[i]));
		}

		ret += write_data(buffer_1, rows_1);

	}else{ // lightmode_static

		// part 1 (LED settings)
		size_t rows_1 = sizeof(_c_data_led_static) / sizeof(_c_data_led_static[0]);
		uint8_t buffer_1[rows_1][17];
		for( size_t i = 0; i < rows_1; i++ ){
			std::copy(std::begin(_c_data_led_static[i]), std::end(_c_data_led_static[i]), std::begin(buffer_1[i]));
		}

		// TODO! fix
		buffer_1[0][6] = _s_colors.at(profile).at(0);
		buffer_1[0][7] = _s_colors.at(profile).at(1);
		buffer_1[0][8] = _s_colors.at(profile).at(2);

		buffer_1[0][12] = _s_brightness_levels[profile];

		ret += write_data(buffer_1, rows_1);

	}
/*
	// part 2 (unknown function)
	size_t rows_2 = sizeof(_c_data_unknown_3) / sizeof(_c_data_unknown_3[0]);
	uint8_t buffer_2[rows_2][17];
	for( size_t i = 0; i < rows_2; i++ ){
		std::copy(std::begin(_c_data_unknown_3[i]), std::end(_c_data_unknown_3[i]), std::begin(buffer_2[i]));
	}
	ret += write_data(buffer_2, rows_2);
*/
	return ret;
}

int mouse_m686::write_settings(){

	// return value
	int ret = 0;

	ret += write_button_mapping(mouse_m686::m686_profile::profile_1);
	ret += write_dpi_settings(mouse_m686::m686_profile::profile_1);
	ret += write_led_settings(mouse_m686::m686_profile::profile_1);

	// TODO! profile 2

	return ret;
}

int mouse_m686::write_macro( int macro_number ){
	// missing data
	(void)macro_number;
	throw std::string( "Macros are not supported for the M686." );
	return 0;
}
