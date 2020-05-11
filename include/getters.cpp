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

mouse_m908::m908_profile mouse_m908::get_profile(){
	return _profile;
}

uint8_t mouse_m908::get_scrollspeed( m908_profile profile ){
	return _scrollspeeds[profile];
}

mouse_m908::m908_lightmode mouse_m908::get_lightmode( m908_profile profile ){
	return _lightmodes[profile];
}

void mouse_m908::get_color( m908_profile profile, std::array<uint8_t, 3> &color ){
	color = _colors[profile];
}

uint8_t mouse_m908::get_brightness( m908_profile profile ){
	return _brightness_levels[profile];
}

uint8_t mouse_m908::get_speed( m908_profile profile ){
	return _speed_levels[profile];
}

bool mouse_m908::get_dpi_enable( m908_profile profile, int level ){
	return _dpi_enabled[profile][level];
}

uint8_t mouse_m908::get_dpi( m908_profile profile, int level ){
	return _dpi_levels[profile][level];
}

mouse_m908::m908_report_rate mouse_m908::get_report_rate( m908_profile profile ){
	return _report_rates[profile];
}

uint8_t mouse_m908::get_macro_repeat( int macro_number ){
	
	//check if macro_number is valid
	if( macro_number < 1 || macro_number > 15 ){
		return 1;
	}
	
	return _macro_repeat[macro_number];
}

bool mouse_m908::get_detach_kernel_driver(){
	return _detach_kernel_driver;
}

int mouse_m908::get_key_mapping_raw( mouse_m908::m908_profile profile, int key, std::array<uint8_t, 4>& mapping ){
	
	if( key < 0 || key > 19 ) // valid key ?
		return 1;
	
	mapping[0] = _keymap_data[profile][key][0];
	mapping[1] = _keymap_data[profile][key][1];
	mapping[2] = _keymap_data[profile][key][2];
	mapping[3] = _keymap_data[profile][key][3];
	
	return 0;
}

int mouse_m908::get_key_mapping( mouse_m908::m908_profile profile, int key, std::string& mapping ){
	
	if( key < 0 || key > 19 ) // valid key ?
		return 1;
	
	uint8_t b1 = _keymap_data[profile][key][0];
	uint8_t b2 = _keymap_data[profile][key][1];
	uint8_t b3 = _keymap_data[profile][key][2];
	uint8_t b4 = _keymap_data[profile][key][3];
	bool found_name = false;
	
	mapping = "";
	
	// fire button
	if( b1 == 0x99 ){
		
		mapping += "fire:";
		
		// button
		if( b2 == 0x81 )
			mapping += "mouse_left:";
		else if( b2 == 0x82 )
			mapping += "mouse_right:";
		else if( b2 == 0x84 )
			mapping += "mouse_middle:";
		else{
			
			// iterate over _keyboard_key_values
			for( auto keycode : _keyboard_key_values ){
				
				if( keycode.second == b2 ){
					
					mapping += keycode.first;
					break;
					
				}
				
			}
			mapping += ":";
		}
		
		// repeats
		mapping += std::to_string( (int)b3 ) + ":";
		
		// delay
		mapping += std::to_string( (int)b4 );
		
		found_name = true;
		
	// keyboard key
	} else if( b1 == 0x90 ){
		
		// iterate over _keyboard_key_values
		for( auto keycode : _keyboard_key_values ){
			
			if( keycode.second == b3 ){
				
				mapping += keycode.first;
				found_name = true;
				break;
				
			}
			
		}
		
	// modifiers + keyboard key
	} else if( b1 == 0x8f ){
		
		// iterate over _keyboard_modifier_values
		for( auto modifier : _keyboard_modifier_values ){
			
			if( modifier.second & b2 ){
				mapping += modifier.first;
			}
			
		}
		
		// iterate over _keyboard_key_values
		for( auto keycode : _keyboard_key_values ){
			
			if( keycode.second == b3 ){
				
				mapping += keycode.first;
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
				
				mapping += keycode.first;
				found_name = true;
				break;
				
			}
			
		}
		
	}
	
	if( !found_name ){
		mapping += "unknown, please report as bug: ";
		mapping += " " + std::to_string( (int)b1 ) + " ";
		mapping += " " + std::to_string( (int)b2 ) + " ";
		mapping += " " + std::to_string( (int)b3 ) + " ";
		mapping += " " + std::to_string( (int)b4 );
	}
	
	return 0;
}
