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

//setter functions

int mouse_m908::set_profile( rd_profile profile ){
	_s_profile = profile;
	return 0;
}

int mouse_m908::set_scrollspeed( rd_profile profile, uint8_t speed ){
	
	//check if bounds exceeded
	if( speed < _c_scrollspeed_min || speed > _c_scrollspeed_max ){
		return 1;
	}
	
	_s_scrollspeeds[profile] = speed;
	
	return 0;
}

int mouse_m908::set_lightmode( rd_profile profile, rd_lightmode lightmode ){
	_s_lightmodes[profile] = lightmode;
	return 0;
}

int mouse_m908::set_color( rd_profile profile, std::array<uint8_t, 3> color ){
	_s_colors[profile] = color;
	return 0;
}

int mouse_m908::set_brightness( rd_profile profile, uint8_t brightness ){
	
	//check bounds
	if( brightness < _c_brightness_min || brightness > _c_brightness_max ){
		return 1;
	}
	
	_s_brightness_levels[profile] = brightness;
	return 0;
}

int mouse_m908::set_speed( rd_profile profile, uint8_t speed ){
	
	//check bounds
	if( speed < _c_speed_min || speed > _c_speed_max ){
		return 1;
	}
	
	_s_speed_levels[profile] = speed;
	return 0;
}

int mouse_m908::set_dpi_enable( rd_profile profile, int level, bool enabled ){
	
	//check bounds
	if( level < _c_level_min || level > _c_level_max ){
		return 1;
	}
	
	_s_dpi_enabled[profile][level] = enabled;
	
	// check if at least one level enabled
	int sum = 0;
	for( int i = _c_level_min; i <= _c_level_max; i++ ){
		if( _s_dpi_enabled[profile][i] ){
			sum++;
		}
	}
	
	// if no level enabled: reenable specified level
	if( sum == 0 ){
		_s_dpi_enabled[profile][level] = true;
		return 1;
	}
	
	return 0;
}

int mouse_m908::set_dpi( rd_profile profile, int level, uint8_t dpi ){
	
	//check bounds
	if( dpi < _c_dpi_min || dpi > _c_dpi_max ){
		return 1;
	}
	
	_s_dpi_levels[profile][level] = dpi;
	return 0;
}

int mouse_m908::set_key_mapping( rd_profile profile, int key, std::array<uint8_t, 4> mapping ){
	_s_keymap_data[profile][key][0] = mapping[0];
	_s_keymap_data[profile][key][1] = mapping[1];
	_s_keymap_data[profile][key][2] = mapping[2];
	_s_keymap_data[profile][key][3] = mapping[3];
	return 0;
}

int mouse_m908::set_key_mapping( rd_profile profile, int key, std::string mapping ){
	
	// is string in _c_keycodes? mousebuttons/special functions and media controls
	if( _c_keycodes.find(mapping) != _c_keycodes.end() ){
		_s_keymap_data[profile][key][0] = _c_keycodes[mapping][0];
		_s_keymap_data[profile][key][1] = _c_keycodes[mapping][1];
		_s_keymap_data[profile][key][2] = _c_keycodes[mapping][2];
		_s_keymap_data[profile][key][3] = 0x00;
	} else if( mapping.find("fire") == 0 ){
		// fire button (multiple keypresses)
		
		std::stringstream mapping_stream(mapping);
		std::string value1 = "", value2 = "", value3 = "";
		uint8_t keycode, repeats = 1, delay = 0;
		
		// the repeated value1 line is not a mistake, it skips the "fire:"
		std::getline( mapping_stream, value1, ':' );
		std::getline( mapping_stream, value1, ':' );
		std::getline( mapping_stream, value2, ':' );
		std::getline( mapping_stream, value3, ':' );
		
		if( value1 == "mouse_left" ){
			keycode = 0x81;
		} else if( value1 == "mouse_right" ){
			keycode = 0x82;
		} else if( value1 == "mouse_middle" ){
			keycode = 0x84;
		} else if( _c_keyboard_key_values.find(value1) != _c_keyboard_key_values.end() ){
			keycode = _c_keyboard_key_values[value1];
		} else{
			return 1;
		}
		
		repeats = (uint8_t)stoi(value2);
		delay = (uint8_t)stoi(value3);
		
		// store values
		_s_keymap_data[profile][key][0] = 0x99;
		_s_keymap_data[profile][key][1] = keycode;
		_s_keymap_data[profile][key][2] = repeats;
		_s_keymap_data[profile][key][3] = delay;
		
	} else{
		// string is not a key in _c_keycodes: keyboard key?
		
		// search for modifiers and change values accordingly: ctrl, shift ...
		uint8_t first_value = 0x90;
		uint8_t modifier_value = 0x00;
		for( auto i : _c_keyboard_modifier_values ){
			if( mapping.find( i.first ) != std::string::npos ){
				modifier_value += i.second;
				first_value = 0x8f;
			}
		}
		
		// get key value and store everything
		try{
			std::regex modifier_regex ("[a-z_]*\\+");
			// store values
			_s_keymap_data[profile][key][0] = first_value;
			_s_keymap_data[profile][key][1] = modifier_value;
			_s_keymap_data[profile][key][2] = _c_keyboard_key_values[std::regex_replace( mapping, modifier_regex, "" )];
			_s_keymap_data[profile][key][3] = 0x00;
			//std::cout << std::regex_replace( mapping, modifier_regex, "" ) << "\n";
		} catch( std::exception& f ){
			return 1;
		}
	}
	
	return 0;
}

int mouse_m908::set_report_rate( rd_profile profile, rd_report_rate report_rate ){
	_s_report_rates[profile] = report_rate;
	return 0;
}


int mouse_m908::set_macro( int macro_number, std::string file ){
	
	//check if macro_number is valid
	if( macro_number < 1 || macro_number > 15 ){
		return 1;
	}
	
	//open file
	std::ifstream config_in( file );
	if( !config_in.is_open() ){
		return 1;
	}
	
	//process file
	std::string value1 = "";
	std::string value2 = "";
	std::size_t position = 0;
	int data_offset = 8;
	
	for( std::string line; std::getline(config_in, line); ){
		//process individual line
		if( line.length() != 0 ){

			position = 0;
			position = line.find("\t", position);
			value1 = line.substr(0, position);
			value2 = line.substr(position+1);
			
			if( value1 == "down" && _c_keyboard_key_values.find(value2) != _c_keyboard_key_values.end() ){
				// keyboard key down
				//std::cout << "down\n";
				_s_macro_data[macro_number-1][data_offset] = 0x84;
				_s_macro_data[macro_number-1][data_offset+1] = _c_keyboard_key_values[value2];
				data_offset += 3;
			} else if( value1 == "up" && _c_keyboard_key_values.find(value2) != _c_keyboard_key_values.end() ){
				// keyboard key up
				//std::cout << "up\n";
				_s_macro_data[macro_number-1][data_offset] = 0x04;
				_s_macro_data[macro_number-1][data_offset+1] = _c_keyboard_key_values[value2];
				data_offset += 3;
			} else if( value1 == "down" && _c_keyboard_key_values.find(value2) == _c_keyboard_key_values.end() ){
				// mouse button down
				//std::cout << "mouse down\n";
				if( value2 == "mouse_left" ){
					_s_macro_data[macro_number-1][data_offset] = 0x81;
					_s_macro_data[macro_number-1][data_offset+1] = 0x01;
					data_offset += 3;
				} else if( value2 == "mouse_right" ){
					_s_macro_data[macro_number-1][data_offset] = 0x81;
					_s_macro_data[macro_number-1][data_offset+1] = 0x02;
					data_offset += 3;
				} else if( value2 == "mouse_middle" ){
					_s_macro_data[macro_number-1][data_offset] = 0x81;
					_s_macro_data[macro_number-1][data_offset+1] = 0x04;
					data_offset += 3;
				}
			} else if( value1 == "up" && _c_keyboard_key_values.find(value2) == _c_keyboard_key_values.end() ){
				// mouse button up
				//std::cout << "mouse up\n";
				if( value2 == "mouse_left" ){
					_s_macro_data[macro_number-1][data_offset] = 0x01;
					_s_macro_data[macro_number-1][data_offset+1] = 0x01;
					data_offset += 3;
				} else if( value2 == "mouse_right" ){
					_s_macro_data[macro_number-1][data_offset] = 0x01;
					_s_macro_data[macro_number-1][data_offset+1] = 0x02;
					data_offset += 3;
				} else if( value2 == "mouse_middle" ){
					_s_macro_data[macro_number-1][data_offset] = 0x01;
					_s_macro_data[macro_number-1][data_offset+1] = 0x04;
					data_offset += 3;
				}
			} else if( value1 == "delay" ){
				// delay
				//std::cout << "delay\n";
				int duration = (uint8_t)stoi( value2, 0, 10);
				if( duration >= 1 && duration <= 255 ){
					_s_macro_data[macro_number-1][data_offset] = 0x06;
					_s_macro_data[macro_number-1][data_offset+1] = duration;
					data_offset += 3;
				}
			}
			
			if(data_offset > 212){
				return 0;
			}
			
		}
	}
	
	return 0;
}

int mouse_m908::set_macro_repeat( int macro_number, uint8_t repeat ){
	
	//check if macro_number is valid
	if( macro_number < 1 || macro_number > 15 ){
		return 1;
	}
	
	_s_macro_repeat[macro_number] = repeat;
	return 0;
}

int mouse_m908::set_detach_kernel_driver( bool detach_kernel_driver ){
	
	_i_detach_kernel_driver = detach_kernel_driver;
	return 0;
}


int mouse_m908::set_all_macros( std::string file ){
	
	//open file
	std::ifstream config_in( file );
	if( !config_in.is_open() ){
		return 1;
	}
	
	//process file
	std::string value1 = "";
	std::string value2 = "";
	std::size_t position = 0;
	int data_offset = 8;
	int macro_number = 0; // initially invalid
	
	for( std::string line; std::getline(config_in, line); ){
		
		// empty line → skip
		if( line.length() == 0 )
			continue;
		
		// macro header → set macro_number, reset data_offset
		if( std::regex_match( line, std::regex(";## macro[0-9]*") ) ){
			macro_number = stoi( std::regex_replace( line, std::regex(";## macro"), "" ), 0, 10 );
			data_offset = 8;
		}
		
		// macro action
		if( std::regex_match( line, std::regex(";# .*") ) ){
			
			// valid macronumber ?
			if( macro_number < 1 || macro_number > 15 )
				continue;
			
			// maximum size reached
			if(data_offset > 212)
				continue;
			
			// get action string
			std::string action = std::regex_replace( line, std::regex(";# "), "" );
			
			// get value substrings
			position = 0;
			position = action.find("\t", position);
			value1 = action.substr(0, position);
			value2 = action.substr(position+1);
			
			// encode values
			if( value1 == "down" && _c_keyboard_key_values.find(value2) != _c_keyboard_key_values.end() ){
				// keyboard key down
				//std::cout << "down\n";
				_s_macro_data[macro_number-1][data_offset] = 0x84;
				_s_macro_data[macro_number-1][data_offset+1] = _c_keyboard_key_values[value2];
				data_offset += 3;
			} else if( value1 == "up" && _c_keyboard_key_values.find(value2) != _c_keyboard_key_values.end() ){
				// keyboard key up
				//std::cout << "up\n";
				_s_macro_data[macro_number-1][data_offset] = 0x04;
				_s_macro_data[macro_number-1][data_offset+1] = _c_keyboard_key_values[value2];
				data_offset += 3;
			} else if( value1 == "down" && _c_keyboard_key_values.find(value2) == _c_keyboard_key_values.end() ){
				// mouse button down
				//std::cout << "mouse down\n";
				if( value2 == "mouse_left" ){
					_s_macro_data[macro_number-1][data_offset] = 0x81;
					_s_macro_data[macro_number-1][data_offset+1] = 0x01;
					data_offset += 3;
				} else if( value2 == "mouse_right" ){
					_s_macro_data[macro_number-1][data_offset] = 0x81;
					_s_macro_data[macro_number-1][data_offset+1] = 0x02;
					data_offset += 3;
				} else if( value2 == "mouse_middle" ){
					_s_macro_data[macro_number-1][data_offset] = 0x81;
					_s_macro_data[macro_number-1][data_offset+1] = 0x04;
					data_offset += 3;
				}
			} else if( value1 == "up" && _c_keyboard_key_values.find(value2) == _c_keyboard_key_values.end() ){
				// mouse button up
				//std::cout << "mouse up\n";
				if( value2 == "mouse_left" ){
					_s_macro_data[macro_number-1][data_offset] = 0x01;
					_s_macro_data[macro_number-1][data_offset+1] = 0x01;
					data_offset += 3;
				} else if( value2 == "mouse_right" ){
					_s_macro_data[macro_number-1][data_offset] = 0x01;
					_s_macro_data[macro_number-1][data_offset+1] = 0x02;
					data_offset += 3;
				} else if( value2 == "mouse_middle" ){
					_s_macro_data[macro_number-1][data_offset] = 0x01;
					_s_macro_data[macro_number-1][data_offset+1] = 0x04;
					data_offset += 3;
				}
			} else if( value1 == "delay" ){
				// delay
				//std::cout << "delay\n";
				int duration = (uint8_t)stoi( value2, 0, 10);
				if( duration >= 1 && duration <= 255 ){
					_s_macro_data[macro_number-1][data_offset] = 0x06;
					_s_macro_data[macro_number-1][data_offset+1] = duration;
					data_offset += 3;
				}
			}
			
		}
		
	}
	
	return 0;
}
