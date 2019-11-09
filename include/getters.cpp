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
