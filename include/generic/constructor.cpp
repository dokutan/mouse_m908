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

#include "mouse_generic.h"

// Constructor, set the default settings
mouse_generic::mouse_generic(){
	
	//default settings
	_s_profile = profile_1;
	_s_scrollspeeds.fill( 0x01 );
	_s_lightmodes.fill( lightmode_static );
	_s_colors.fill( {0xff, 0xff, 0xff} );
	_s_brightness_levels.fill( 0x03 );
	_s_speed_levels.fill( 0x08 );
	
	// dpi
	_s_dpi_enabled.fill( {true, true, true, true, true} );
	_s_dpi_levels.fill( {{ {0x04, 0x00}, {0x16, 0x00}, {0x2d, 0x00}, {0x43, 0x00}, {0x8c, 0x00} }} );
	
	// button mapping
	for( int i = 0; i < 5; i++ ){
		for( int j = 0; j < 8; j++ ){
			_s_keymap_data[i][j][0] = _c_data_settings_3[35+(8*i)+j][8];
			_s_keymap_data[i][j][1] = _c_data_settings_3[35+(8*i)+j][9];
			_s_keymap_data[i][j][2] = _c_data_settings_3[35+(8*i)+j][10];
			_s_keymap_data[i][j][3] = _c_data_settings_3[35+(8*i)+j][11];
		}
	}
	_s_report_rates.fill( r_125Hz );
	int count = 0;
	for( auto &i : _s_macro_data ){
		std::copy(std::begin(_c_data_macros_2), std::end(_c_data_macros_2), std::begin(i));
		i[2] = _c_data_macros_codes[count][0];
		i[3] = _c_data_macros_codes[count][1];
		count++;
	}
	
}
