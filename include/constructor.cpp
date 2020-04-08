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
		{ "macro1", { 0x91, 0x00, 0x01 } },
		{ "macro2", { 0x91, 0x01, 0x01 } },
		{ "macro3", { 0x91, 0x02, 0x01 } },
		{ "macro4", { 0x91, 0x03, 0x01 } },
		{ "macro5", { 0x91, 0x04, 0x01 } },
		{ "macro6", { 0x91, 0x05, 0x01 } },
		{ "macro7", { 0x91, 0x06, 0x01 } },
		{ "macro8", { 0x91, 0x07, 0x01 } },
		{ "macro9", { 0x91, 0x08, 0x01 } },
		{ "macro10", { 0x91, 0x09, 0x01 } },
		{ "macro11", { 0x91, 0x0a, 0x01 } },
		{ "macro12", { 0x91, 0x0b, 0x01 } },
		{ "macro13", { 0x91, 0x0c, 0x01 } },
		{ "macro14", { 0x91, 0x0d, 0x01 } },
		{ "macro15", { 0x91, 0x0e, 0x01 } },
		{ "none", { 0x00, 0x00, 0x00 } } };
	
	//modifier name → value
	_keyboard_modifier_values = {
		{ "ctrl_l+", 1 },
		{ "shift_l+", 2 },
		{ "alt_l+", 4 },
		{ "super_l+", 8 },
		{ "ctrl_r+", 16 },
		{ "shift_r+", 32 },
		{ "alt_r+", 64 },
		{ "super_r+", 128 } };
	
	//keyboard key name → value
	//top row
	_keyboard_key_values["Esc"] = 0x29;
	_keyboard_key_values["F1"] = 0x3a;
	_keyboard_key_values["F2"] = 0x3b;
	_keyboard_key_values["F3"] = 0x3c;
	_keyboard_key_values["F4"] = 0x3d;
	_keyboard_key_values["F5"] = 0x3e;
	_keyboard_key_values["F6"] = 0x3f;
	_keyboard_key_values["F7"] = 0x40;
	_keyboard_key_values["F8"] = 0x41;
	_keyboard_key_values["F9"] = 0x42;
	_keyboard_key_values["F10"] = 0x43;
	_keyboard_key_values["F11"] = 0x44;
	_keyboard_key_values["F12"] = 0x45;
	_keyboard_key_values["PrtSc"] = 0x46;
	_keyboard_key_values["ScrLk"] = 0x47;
	_keyboard_key_values["Pause"] = 0x48;
	//alphanumeric
	_keyboard_key_values["a"] = 0x04;
	_keyboard_key_values["b"] = 0x05;
	_keyboard_key_values["c"] = 0x06;
	_keyboard_key_values["d"] = 0x07;
	_keyboard_key_values["e"] = 0x08;
	_keyboard_key_values["f"] = 0x09;
	_keyboard_key_values["g"] = 0x0a;
	_keyboard_key_values["h"] = 0x0b;
	_keyboard_key_values["i"] = 0x0c;
	_keyboard_key_values["j"] = 0x0d;
	_keyboard_key_values["k"] = 0x0e;
	_keyboard_key_values["l"] = 0x0f;
	_keyboard_key_values["m"] = 0x10;
	_keyboard_key_values["n"] = 0x11;
	_keyboard_key_values["o"] = 0x12;
	_keyboard_key_values["p"] = 0x13;
	_keyboard_key_values["q"] = 0x14;
	_keyboard_key_values["r"] = 0x15;
	_keyboard_key_values["s"] = 0x16;
	_keyboard_key_values["t"] = 0x17;
	_keyboard_key_values["u"] = 0x18;
	_keyboard_key_values["v"] = 0x19;
	_keyboard_key_values["w"] = 0x1a;
	_keyboard_key_values["x"] = 0x1b;
	_keyboard_key_values["y"] = 0x1c;
	_keyboard_key_values["z"] = 0x1d;
	_keyboard_key_values["1"] = 0x1e;
	_keyboard_key_values["2"] = 0x1f;
	_keyboard_key_values["3"] = 0x20;
	_keyboard_key_values["4"] = 0x21;
	_keyboard_key_values["5"] = 0x22;
	_keyboard_key_values["6"] = 0x23;
	_keyboard_key_values["7"] = 0x24;
	_keyboard_key_values["8"] = 0x25;
	_keyboard_key_values["9"] = 0x26;
	_keyboard_key_values["0"] = 0x27;
	//modifiers
	_keyboard_key_values["Tab"] = 0x2b;
	_keyboard_key_values["Caps_Lock"] = 0x39;
	_keyboard_key_values["Shift_l"] = 0xe1;
	_keyboard_key_values["Ctrl_l"] = 0xe0;
	_keyboard_key_values["Alt_l"] = 0xe2;
	_keyboard_key_values["Super_l"] = 0xe3;
	_keyboard_key_values["Super_r"] = 0xe7;
	_keyboard_key_values["Alt_r"] = 0xe6;
	_keyboard_key_values["Menu"] = 0x65;
	_keyboard_key_values["Ctrl_r"] = 0xe4;
	_keyboard_key_values["Shift_r"] = 0xe5;
	_keyboard_key_values["Return"] = 0x28;
	_keyboard_key_values["Backspace"] = 0x2a;
	_keyboard_key_values["Caps_Lock"] = 0x39;
	//special characters
	_keyboard_key_values["Space"] = 0x2b;
	_keyboard_key_values["Tilde"] = 0x35;
	_keyboard_key_values["Minus"] = 0x2d;
	_keyboard_key_values["Equals"] = 0x2e;
	_keyboard_key_values["Bracket_l"] = 0x2f;
	_keyboard_key_values["Bracket_r"] = 0x30;
	_keyboard_key_values["Backslash"] = 0x31;
	_keyboard_key_values["Semicolon"] = 0x33;
	_keyboard_key_values["Apostrophe"] = 0x34;
	_keyboard_key_values["Comma"] = 0x36;
	_keyboard_key_values["Period"] = 0x37;
	_keyboard_key_values["Slash"] = 0x38;
	_keyboard_key_values["Int_Key"] = 0x64;
	//navigation
	_keyboard_key_values["Right"] = 0x4f;
	_keyboard_key_values["Left"] = 0x50;
	_keyboard_key_values["Down"] = 0x51;
	_keyboard_key_values["Up"] = 0x52;
	_keyboard_key_values["Insert"] = 0x49;
	_keyboard_key_values["Home"] = 0x4a;
	_keyboard_key_values["PgUp"] = 0x4b;
	_keyboard_key_values["Delete"] = 0x4c;
	_keyboard_key_values["End"] = 0x4d;
	_keyboard_key_values["PgDown"] = 0x4e;
	//numpad
	_keyboard_key_values["Num_Slash"] = 0x54;
	_keyboard_key_values["Num_Asterisk"] = 0x55;
	_keyboard_key_values["Num_Minus"] = 0x56;
	_keyboard_key_values["Num_Plus"] = 0x57;
	_keyboard_key_values["Num_Return"] = 0x58;
	_keyboard_key_values["Num_1"] = 0x59;
	_keyboard_key_values["Num_2"] = 0x5a;
	_keyboard_key_values["Num_3"] = 0x5b;
	_keyboard_key_values["Num_4"] = 0x5c;
	_keyboard_key_values["Num_5"] = 0x5d;
	_keyboard_key_values["Num_6"] = 0x5e;
	_keyboard_key_values["Num_7"] = 0x5f;
	_keyboard_key_values["Num_8"] = 0x60;
	_keyboard_key_values["Num_9"] = 0x61;
	_keyboard_key_values["Num_0"] = 0x62;
	_keyboard_key_values["Num_Period"] = 0x63;
	_keyboard_key_values["Num_Lock"] = 0x53;
	//media controls, etc. TODO
	//special keys
	_keyboard_key_values["Lang1"] = 0x90;
	_keyboard_key_values["Lang2"] = 0x91;
	_keyboard_key_values["Lang3"] = 0x92;
	_keyboard_key_values["Lang4"] = 0x93;
	_keyboard_key_values["Lang5"] = 0x94;
	_keyboard_key_values["Lang6"] = 0x95;
	_keyboard_key_values["Lang7"] = 0x96;
	_keyboard_key_values["Lang8"] = 0x97;
	_keyboard_key_values["Lang9"] = 0x98;
	_keyboard_key_values["F13"] = 0x68;
	_keyboard_key_values["F14"] = 0x69;
	_keyboard_key_values["F15"] = 0x6a;
	_keyboard_key_values["F16"] = 0x6b;
	_keyboard_key_values["F17"] = 0x6c;
	_keyboard_key_values["F18"] = 0x6d;
	_keyboard_key_values["F19"] = 0x6e;
	_keyboard_key_values["F20"] = 0x6f;
	_keyboard_key_values["F21"] = 0x70;
	_keyboard_key_values["F22"] = 0x71;
	_keyboard_key_values["F23"] = 0x72;
	_keyboard_key_values["F24"] = 0x73;
	
}
