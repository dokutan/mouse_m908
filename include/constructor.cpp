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

// Constructor, set the default settings
mouse_m908::mouse_m908(){
	
	//default settings
	_profile = profile_1;
	_scrollspeeds.fill( 0x01 );
	_lightmodes.fill( lightmode_static );
	_colors.fill( {0xff, 0xff, 0xff} );
	_brightness_levels.fill( 0x03 );
	_speed_levels.fill( 0x08 );
	_dpi_enabled.fill( {true, true, true, true, true} );
	_dpi_levels.fill( {0x04, 0x16, 0x2d, 0x43, 0x8c} );
	for( int i = 0; i < 5; i++ ){
		for( int j = 0; j < 20; j++ ){
			_keymap_data[i][j][0] = _data_settings_3[35+(20*i)+j][8];
			_keymap_data[i][j][1] = _data_settings_3[35+(20*i)+j][9];
			_keymap_data[i][j][2] = _data_settings_3[35+(20*i)+j][10];
			_keymap_data[i][j][3] = _data_settings_3[35+(20*i)+j][11];
		}
	}
	_report_rates.fill( r_125Hz );
	int count = 0;
	for( auto &i : _macro_data ){
		std::copy(std::begin(_data_macros_2), std::end(_data_macros_2), std::begin(i));
		i[2] = _data_macros_codes[count][0];
		i[3] = _data_macros_codes[count][1];
		count++;
	}
	_macro_repeat.fill( 0x01 );
	
}
