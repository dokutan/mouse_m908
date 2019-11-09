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

//setter functions

int mouse_m908::set_profile( m908_profile profile ){
	_profile = profile;
	return 0;
}

int mouse_m908::set_scrollspeed( m908_profile profile, uint8_t speed ){
	
	//check if bounds exceeded
	if( speed < _scrollspeed_min || speed > _scrollspeed_max ){
		return 1;
	}
	
	_scrollspeeds[profile] = speed;
	
	return 0;
}

int mouse_m908::set_lightmode( m908_profile profile, m908_lightmode lightmode ){
	_lightmodes[profile] = lightmode;
	return 0;
}

int mouse_m908::set_color( m908_profile profile, std::array<uint8_t, 3> color ){
	_colors[profile] = color;
	return 0;
}

int mouse_m908::set_brightness( m908_profile profile, uint8_t brightness ){
	
	//check bounds
	if( brightness < _brightness_min || brightness > _brightness_max ){
		return 1;
	}
	
	_brightness_levels[profile] = brightness;
	return 0;
}

int mouse_m908::set_speed( m908_profile profile, uint8_t speed ){
	
	//check bounds
	if( speed < _speed_min || speed > _speed_max ){
		return 1;
	}
	
	_speed_levels[profile] = speed;
	return 0;
}

int mouse_m908::set_dpi_enable( m908_profile profile, int level, bool enabled ){
	
	//check bounds
	if( level < _level_min || level > _level_max ){
		return 1;
	}
	
	_dpi_enabled[profile][level] = enabled;
	return 0;
}

int mouse_m908::set_dpi( m908_profile profile, int level, uint8_t dpi ){
	
	//check bounds
	if( dpi < _dpi_min || dpi > _dpi_max ){
		return 1;
	}
	
	_dpi_levels[profile][level] = dpi;
	return 0;
}

int mouse_m908::set_key_mapping( m908_profile profile, int key, std::array<uint8_t, 3> mapping ){
	_keymap_data[profile][key][0] = mapping[0];
	_keymap_data[profile][key][1] = mapping[1];
	_keymap_data[profile][key][2] = mapping[2];
	return 0;
}

int mouse_m908::set_key_mapping( m908_profile profile, int key, std::string mapping ){
	
	try{
		_keymap_data[profile][key][0] = _keycodes[mapping][0];
		_keymap_data[profile][key][1] = _keycodes[mapping][1];
		_keymap_data[profile][key][2] = _keycodes[mapping][2];
	} catch( std::exception& e ){
		return 1;
	}
	return 0;
}
