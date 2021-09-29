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

//setter functions

int mouse_m913::set_profile( rd_profile profile ){
	_s_profile = profile;
	return 0;
}

int mouse_m913::set_scrollspeed( rd_profile profile, uint8_t speed ){
	
	//check if bounds exceeded
	if( speed < _c_scrollspeed_min || speed > _c_scrollspeed_max ){
		return 1;
	}
	
	_s_scrollspeeds[rd_profile_to_m913_profile(profile)] = speed;
	
	return 0;
}

int mouse_m913::set_lightmode( rd_profile profile, rd_lightmode lightmode ){
	_s_lightmodes[rd_profile_to_m913_profile(profile)] = lightmode;
	return 0;
}

int mouse_m913::set_color( rd_profile profile, std::array<uint8_t, 3> color ){
	_s_colors[rd_profile_to_m913_profile(profile)] = color;
	return 0;
}

int mouse_m913::set_brightness( rd_profile profile, uint8_t brightness ){
	
	//check bounds
	if( brightness < _c_brightness_min || brightness > _c_brightness_max ){
		return 1;
	}
	
	_s_brightness_levels[rd_profile_to_m913_profile(profile)] = brightness;
	return 0;
}

int mouse_m913::set_speed( rd_profile profile, uint8_t speed ){
	
	//check bounds
	if( speed < _c_speed_min || speed > _c_speed_max ){
		return 1;
	}
	
	_s_speed_levels[rd_profile_to_m913_profile(profile)] = speed;
	return 0;
}

int mouse_m913::set_dpi_enable( rd_profile profile, int level, bool enabled ){
	
	//check bounds
	if( level < _c_level_min || level > _c_level_max ){
		return 1;
	}
	
	_s_dpi_enabled[rd_profile_to_m913_profile(profile)][level] = enabled;
	
	// check if at least one level enabled
	int sum = 0;
	for( int i = _c_level_min; i <= _c_level_max; i++ ){
		if( _s_dpi_enabled[rd_profile_to_m913_profile(profile)][i] ){
			sum++;
		}
	}
	
	// if no level enabled: reenable specified level
	if( sum == 0 ){
		_s_dpi_enabled[rd_profile_to_m913_profile(profile)][level] = true;
		return 1;
	}
	
	return 0;
}

int mouse_m913::set_dpi( rd_profile profile, int level, std::string dpi ){
	
	// check DPI level bounds
	if( level < _c_level_min || level > _c_level_max )
		return 1;
	
	// current assumption: only one profile
	profile = rd_mouse::rd_profile::profile_1;
	
	// check format: 0xABCD (raw bytes), TODO! enable or remove
	/*
	if( std::regex_match( dpi, std::regex("0x[[:xdigit:]]{4}") ) ){

		uint8_t b0 = (uint8_t)stoi( dpi.substr(2,2), 0, 16 );
		uint8_t b1 = (uint8_t)stoi( dpi.substr(4,2), 0, 16 );

		//check bounds, bounds currently unknown TODO!
		//if( b0 < _c_dpi_min || b0 > _c_dpi_max || b1 < _c_dpi_2_min || b1 > _c_dpi_2_max )
		//	return 1;

		_s_dpi_levels[profile][level][0] = b0;
		_s_dpi_levels[profile][level][1] = b1;
		
		return 0;
		
	}
	*/

	// check format: 1234 (real DPI)
	if( std::regex_match( dpi, std::regex("[[:digit:]]+") ) ){
		
		if( _c_dpi_codes.find( std::stoi(dpi) ) != _c_dpi_codes.end() ){

			_s_dpi_levels[rd_profile_to_m913_profile(profile)][level] = _c_dpi_codes.at( std::stoi(dpi) );
			return 0;
		}
	}
	
	return 1;
}

int mouse_m913::set_dpi( rd_profile profile, int level, std::array<uint8_t, 3> dpi ){
	
	// check DPI level bounds
	if( level < _c_level_min || level > _c_level_max )
		return 1;
	
	// current assumption: only one profile
	profile = rd_mouse::rd_profile::profile_1;

	_s_dpi_levels[rd_profile_to_m913_profile(profile)][level] = dpi;
	return 0;
}

int mouse_m913::set_key_mapping( rd_profile profile, int key, std::array<uint8_t, 4> mapping ){
	_s_keymap_data[rd_profile_to_m913_profile(profile)][key][0] = mapping[0];
	_s_keymap_data[rd_profile_to_m913_profile(profile)][key][1] = mapping[1];
	_s_keymap_data[rd_profile_to_m913_profile(profile)][key][2] = mapping[2];
	_s_keymap_data[rd_profile_to_m913_profile(profile)][key][3] = mapping[3];
	return 0;
}

int mouse_m913::set_key_mapping( rd_profile profile, int key, std::string mapping ){
	
	// valid key ?
	if( _c_button_names[key] == "" )
		return 1;
	
	// current assumption: only one profile
	profile = rd_mouse::rd_profile::profile_1;

	// the M913 uses different keycodes, therefore the decoding is done here
	if( _c_keycodes.find(mapping) != _c_keycodes.end() ){
		_s_keymap_data[rd_profile_to_m913_profile(profile)][key] = _c_keycodes[mapping];
	}
	
	return 0;
}

int mouse_m913::set_report_rate( rd_profile profile, rd_report_rate report_rate ){
	_s_report_rates[rd_profile_to_m913_profile(profile)] = report_rate;
	return 0;
}

int mouse_m913::set_macro( int macro_number, std::string file ){
	
	//check if macro_number is valid
	if( macro_number < 1 || macro_number > 15 ){
		return 1;
	}
	
	//open file
	std::ifstream config_in( file );
	if( !config_in.is_open() ){
		return 1;
	}
	
	std::array< uint8_t, 256 > macro_bytes;
	_i_encode_macro( macro_bytes, config_in, 8 );
	std::copy( macro_bytes.begin()+8, macro_bytes.end(), _s_macro_data[macro_number-1].begin()+8 );
	
	config_in.close();
	return 0;
}

int mouse_m913::set_all_macros( std::string file ){
	
	//open file
	std::ifstream config_in( file );
	if( !config_in.is_open() ){
		return 1;
	}
	
	int macro_number = 0; // initially invalid
	std::array< std::stringstream, 15 > macro_streams;
	
	// get all macros from file
	for( std::string line; std::getline(config_in, line); ){
		
		// empty line → skip
		if( line.length() == 0 )
			continue;
		
		// macro header → set macro_number
		if( std::regex_match( line, std::regex(";## macro[0-9]*") ) ){
			macro_number = stoi( std::regex_replace( line, std::regex(";## macro"), "" ), 0, 10 );
		}
		
		// macro action
		if( std::regex_match( line, std::regex(";# .*") ) ){
			
			// valid macronumber ?
			if( macro_number < 1 || macro_number > 15 )
				continue;
			
			macro_streams.at( macro_number-1 ) << std::regex_replace( line, std::regex(";# "), "" ) << "\n";
		}
		
	}
	
	// encode and store all macros
	for( int i = 0; i < 15; i++ ){
		
		std::array< uint8_t, 256 > macro_bytes;
		_i_encode_macro( macro_bytes, macro_streams.at(i), 8 );
		std::copy( macro_bytes.begin()+8, macro_bytes.end(), _s_macro_data.at(i).begin()+8 );
		
	}
	
	return 0;
}
