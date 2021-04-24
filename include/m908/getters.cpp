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

mouse_m908::rd_profile mouse_m908::get_profile(){
	return _s_profile;
}

uint8_t mouse_m908::get_scrollspeed( rd_profile profile ){
	return _s_scrollspeeds[profile];
}

mouse_m908::rd_lightmode mouse_m908::get_lightmode( rd_profile profile ){
	return _s_lightmodes[profile];
}

void mouse_m908::get_color( rd_profile profile, std::array<uint8_t, 3> &color ){
	color = _s_colors[profile];
}

uint8_t mouse_m908::get_brightness( rd_profile profile ){
	return _s_brightness_levels[profile];
}

uint8_t mouse_m908::get_speed( rd_profile profile ){
	return _s_speed_levels[profile];
}

bool mouse_m908::get_dpi_enable( rd_profile profile, int level ){
	
	// check DPI level bounds
	if( level < _c_level_min || level > _c_level_max )
		return false;
	
	return _s_dpi_enabled[profile][level];
}

int mouse_m908::get_dpi( rd_profile profile, int level, std::array<uint8_t, 2>& dpi ){
	
	// check DPI level bounds
	if( level < _c_level_min || level > _c_level_max )
		return 1;
	
	dpi[0] = _s_dpi_levels[profile][level][0];
	dpi[1] = _s_dpi_levels[profile][level][1];
	return 0;
}

mouse_m908::rd_report_rate mouse_m908::get_report_rate( rd_profile profile ){
	return _s_report_rates[profile];
}

int mouse_m908::get_key_mapping_raw( mouse_m908::rd_profile profile, int key, std::array<uint8_t, 4>& mapping ){
	
	// valid key ?
	if( _c_button_names[key] == "" )
		return 1;
	
	mapping[0] = _s_keymap_data[profile][key][0];
	mapping[1] = _s_keymap_data[profile][key][1];
	mapping[2] = _s_keymap_data[profile][key][2];
	mapping[3] = _s_keymap_data[profile][key][3];
	
	return 0;
}

int mouse_m908::get_key_mapping( mouse_m908::rd_profile profile, int key, std::string& mapping ){
	
	// valid key ?
	if( _c_button_names[key] == "" )
		return 1;
	
	std::array< uint8_t, 4 > bytes = {
		_s_keymap_data[profile][key][0],
		_s_keymap_data[profile][key][1],
		_s_keymap_data[profile][key][2],
		_s_keymap_data[profile][key][3]
	};
	
	_i_decode_button_mapping( bytes, mapping );
	return 0;
}

int mouse_m908::get_macro_raw( int number, std::array<uint8_t, 256>& macro ){
	
	//check if macro_number is valid
	if( number < 1 || number > 15 )
		return 1;
	
	std::copy( _s_macro_data[number-1].begin(), _s_macro_data[number-1].end(), macro.begin() );
	
	return 0;
}

int mouse_m908::get_macro( int number, std::string& macro ){
	
	std::stringstream output;
	
	// macro undefined?
	if( _s_macro_data[number-1][8] == 0 && _s_macro_data[number-1][9] == 0 && _s_macro_data[number-1][10] == 0 )
		return 0;
	
	std::vector< uint8_t > macro_bytes;
	std::copy( _s_macro_data[number-1].begin(), _s_macro_data[number-1].end(), std::back_inserter(macro_bytes) );
	
	_i_decode_macro( macro_bytes, output, "", 8 );
	macro = output.str();
	return 0;
}
