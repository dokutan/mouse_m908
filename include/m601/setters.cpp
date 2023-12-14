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

int mouse_m601::set_profile( rd_profile profile ){
	if( profile == profile_1 || profile == profile_2 ){
		_s_profile = profile;
		return 0;
	}else{
		// The M601 has only two profiles
		return 1;
	}
}

// These setters do nothing and exist only for compatibility. Use load_settings() instead.
int mouse_m601::set_scrollspeed( rd_profile profile, uint8_t speed ){
	(void)profile;
	(void)speed;
	return 1;
}
int mouse_m601::set_lightmode( rd_profile profile, rd_lightmode lightmode ){
	(void)profile;
	(void)lightmode;
	return 1;
}
int mouse_m601::set_color( rd_profile profile, std::array<uint8_t, 3> color ){
	(void)profile;
	(void)color;
	return 1;
}
int mouse_m601::set_brightness( rd_profile profile, uint8_t brightness ){
	(void)profile;
	(void)brightness;
	return 1;
}
int mouse_m601::set_speed( rd_profile profile, uint8_t speed ){
	(void)profile;
	(void)speed;
	return 1;
}
int mouse_m601::set_dpi_enable( rd_profile profile, int level, bool enabled ){
	(void)profile;
	(void)level;
	(void)enabled;
	return 1;
}
int mouse_m601::set_dpi( rd_profile profile, int level, std::string dpi ){
	(void)profile;
	(void)level;
	(void)dpi;
	return 1;
}
int mouse_m601::set_dpi( rd_profile profile, int level, std::array<uint8_t, 2> dpi ){
	(void)profile;
	(void)level;
	(void)dpi;
	return 1;
}
int mouse_m601::set_key_mapping( rd_profile profile, int key, std::array<uint8_t, 4> mapping ){
	(void)profile;
	(void)key;
	(void)mapping;
	return 1;
}
int mouse_m601::set_key_mapping( rd_profile profile, int key, std::string mapping ){
	(void)profile;
	(void)key;
	(void)mapping;
	return 1;
}
int mouse_m601::set_report_rate( rd_profile profile, rd_report_rate report_rate ){
	(void)profile;
	(void)report_rate;
	return 1;
}

int mouse_m601::set_macro( int macro_number, std::string file ){
	// TODO implement macros
	(void)macro_number;
	(void)file;
	throw std::string( "Macros are currently not supported on the M601." );
	return 1;
}

int mouse_m601::set_all_macros( std::string file ){
	// TODO implement macros
	(void)file;
	throw std::string( "Macros are currently not supported on the M601." );
	return 1;
}
