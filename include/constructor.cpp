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

//constructor
mouse_m908::mouse_m908(){
	
	_mouse_vid = 0x04d9;
	_mouse_pid = 0xfc4d;
	
	//min and max settings
	_scrollspeed_min = 0x01;
	_scrollspeed_max = 0x3f;
	_brightness_min = 0x01;
	_brightness_max = 0x03;
	_speed_min = 0x01;
	_speed_max = 0x08;
	_level_min = 0;
	_level_max = 4;
	_dpi_min = 0x04;
	_dpi_max = 0x8c;
	
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
		}
	}
	_report_rates.fill( r_125Hz );
	
	//name → keycode
	_keycodes = {
		{ "forward", { 0x85, 0x00, 0x00 } },
		{ "backward", { 0x84, 0x00, 0x00 } },
		{ "dpi+", { 0x8a, 0x00, 0x00 } },
		{ "dpi-", { 0x89, 0x00, 0x00 } },
		{ "dpi-cycle", { 0x88, 0x00, 0x00 } },
		{ "report_rate+", { 0x97, 0x00, 0x00 } },
		{ "report_rate-", { 0x98, 0x00, 0x00 } },
		{ "scroll_up", { 0x8b, 0x00, 0x00 } },
		{ "scroll_down", { 0x8c, 0x00, 0x00 } },
		{ "left", { 0x81, 0x00, 0x00 } },
		{ "right", { 0x82, 0x00, 0x00 } },
		{ "middle", { 0x83, 0x00, 0x00 } },
		{ "profile_switch", { 0x8d, 0x00, 0x00 } },
		{ "none", { 0x00, 0x00, 0x00 } } };
	
}
