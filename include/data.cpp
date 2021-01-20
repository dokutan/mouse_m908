/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

/*
 * This file contains internal constants and lookup tables that are
 * universal to all mice
 */

#include "rd_mouse.h"

// usb ids for all mice
std::set< uint16_t > rd_mouse::_c_all_vids = {
	0x04d9 // all known mice have the same VID
};
std::set< uint16_t > rd_mouse::_c_all_pids = {
	0xfc4d, // M908 Impact
	0xfc2a, // M709 Tiger
	0xfc30, // M711 Cobra (FPS)
	0xfc39, // M715 Dagger	
	0xfc41, // M990 Legend Chroma/RGB
	0xfc0f, // M990 Legend
	0xfc4f, // M719 Invader
	0xfc42, // M802 Titanoboa 2
	0xfc5e, // 2858 (?)
	0xfc58, // 2805 (?)
	0xfc61, // 2850 (?)
	0xfc40, // M901 Perdition (3)
	0xfa56, // M801 Mammoth
	0xfc56, // M801 Mammoth (?)
	0xfc49, // M910 Ranger
	0xfc5f, // M998-RGB and M808-RGB (?)
	0xfc38, // M607 Griffin
	0xfc3f  // (?)
};

//setting min and max values
const uint8_t rd_mouse::_c_scrollspeed_min = 0x01, rd_mouse::_c_scrollspeed_max = 0x3f;
const uint8_t rd_mouse::_c_brightness_min = 0x01, rd_mouse::_c_brightness_max = 0x03;
const uint8_t rd_mouse::_c_speed_min = 0x01, rd_mouse::_c_speed_max = 0x08;
const uint8_t rd_mouse::_c_level_min = 0, rd_mouse::_c_level_max = 4;
const uint8_t rd_mouse::_c_dpi_min = 0x04, rd_mouse::_c_dpi_max = 0x8c;
const uint8_t rd_mouse::_c_dpi_2_min = 0x00, rd_mouse::_c_dpi_2_max = 0x01;

//name → keycode
std::map< std::string, std::array<uint8_t, 3> > rd_mouse::_c_keycodes = {
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
	{ "led_mode_switch", { 0x9b, 0x04, 0x00 } },
	{ "none", { 0x00, 0x00, 0x00 } },
	{ "media_play", { 0x8e, 0x01, 0xcd } },
	{ "media_stop", { 0x8e, 0x01, 0xb7 } },
	{ "media_previous", { 0x8e, 0x01, 0xb6 } },
	{ "media_next", { 0x8e, 0x01, 0xb5 } },
	{ "media_volume_up", { 0x8e, 0x01, 0xe9 } },
	{ "media_volume_down", { 0x8e, 0x01, 0xea } },
	{ "media_mute", { 0x8e, 0x01, 0xe2 } } };

//modifier name → value
const std::map< std::string, uint8_t > rd_mouse::_c_keyboard_modifier_values = {
	{ "ctrl_l+", 1 },
	{ "shift_l+", 2 },
	{ "alt_l+", 4 },
	{ "super_l+", 8 },
	{ "ctrl_r+", 16 },
	{ "shift_r+", 32 },
	{ "alt_r+", 64 },
	{ "super_r+", 128 } };

//keyboard key name → value
std::map< std::string, uint8_t > rd_mouse::_c_keyboard_key_values = {
	//top row
	{ "Esc", 0x29 },
	{ "F1", 0x3a },
	{ "F2", 0x3b },
	{ "F3", 0x3c },
	{ "F4", 0x3d },
	{ "F5", 0x3e },
	{ "F6", 0x3f },
	{ "F7", 0x40 },
	{ "F8", 0x41 },
	{ "F9", 0x42 },
	{ "F10", 0x43 },
	{ "F11", 0x44 },
	{ "F12", 0x45 },
	{ "PrtSc", 0x46 },
	{ "ScrLk", 0x47 },
	{ "Pause", 0x48 },
	//alphanumeric
	{ "a", 0x04 },
	{ "b", 0x05 },
	{ "c", 0x06 },
	{ "d", 0x07 },
	{ "e", 0x08 },
	{ "f", 0x09 },
	{ "g", 0x0a },
	{ "h", 0x0b },
	{ "i", 0x0c },
	{ "j", 0x0d },
	{ "k", 0x0e },
	{ "l", 0x0f },
	{ "m", 0x10 },
	{ "n", 0x11 },
	{ "o", 0x12 },
	{ "p", 0x13 },
	{ "q", 0x14 },
	{ "r", 0x15 },
	{ "s", 0x16 },
	{ "t", 0x17 },
	{ "u", 0x18 },
	{ "v", 0x19 },
	{ "w", 0x1a },
	{ "x", 0x1b },
	{ "y", 0x1c },
	{ "z", 0x1d },
	{ "1", 0x1e },
	{ "2", 0x1f },
	{ "3", 0x20 },
	{ "4", 0x21 },
	{ "5", 0x22 },
	{ "6", 0x23 },
	{ "7", 0x24 },
	{ "8", 0x25 },
	{ "9", 0x26 },
	{ "0", 0x27 },
	//modifiers
	{ "Tab", 0x2b },
	{ "Caps_Lock", 0x39 },
	{ "Shift_l", 0xe1 },
	{ "Ctrl_l", 0xe0 },
	{ "Alt_l", 0xe2 },
	{ "Super_l", 0xe3 },
	{ "Super_r", 0xe7 },
	{ "Alt_r", 0xe6 },
	{ "Menu", 0x65 },
	{ "Ctrl_r", 0xe4 },
	{ "Shift_r", 0xe5 },
	{ "Return", 0x28 },
	{ "Backspace", 0x2a },
	{ "Caps_Lock", 0x39 },
	//special characters
	{ "Space", 0x2c },
	{ "Tilde", 0x35 },
	{ "Minus", 0x2d },
	{ "Equals", 0x2e },
	{ "Bracket_l", 0x2f },
	{ "Bracket_r", 0x30 },
	{ "Backslash", 0x31 },
	{ "Hash", 0x32 },
	{ "Semicolon", 0x33 },
	{ "Apostrophe", 0x34 },
	{ "Comma", 0x36 },
	{ "Period", 0x37 },
	{ "Slash", 0x38 },
	{ "Int_Key", 0x64 },
	//navigation
	{ "Right", 0x4f },
	{ "Left", 0x50 },
	{ "Down", 0x51 },
	{ "Up", 0x52 },
	{ "Insert", 0x49 },
	{ "Home", 0x4a },
	{ "PgUp", 0x4b },
	{ "Delete", 0x4c },
	{ "End", 0x4d },
	{ "PgDown", 0x4e },
	//numpad
	{ "Num_Slash", 0x54 },
	{ "Num_Asterisk", 0x55 },
	{ "Num_Minus", 0x56 },
	{ "Num_Plus", 0x57 },
	{ "Num_Return", 0x58 },
	{ "Num_1", 0x59 },
	{ "Num_2", 0x5a },
	{ "Num_3", 0x5b },
	{ "Num_4", 0x5c },
	{ "Num_5", 0x5d },
	{ "Num_6", 0x5e },
	{ "Num_7", 0x5f },
	{ "Num_8", 0x60 },
	{ "Num_9", 0x61 },
	{ "Num_0", 0x62 },
	{ "Num_Period", 0x63 },
	{ "Num_Lock", 0x53 },
	{ "Num_Equals", 0x67 },
	{ "Num_Comma", 0x85 },
	{ "Num_Paren_l", 0xb6 },
	{ "Num_Paren_r", 0xb7 },
	//special keys
	{ "Power", 0x66 },
	{ "Lang1", 0x90 },
	{ "Lang2", 0x91 },
	{ "Lang3", 0x92 },
	{ "Lang4", 0x93 },
	{ "Lang5", 0x94 },
	{ "Lang6", 0x95 },
	{ "Lang7", 0x96 },
	{ "Lang8", 0x97 },
	{ "Lang9", 0x98 },
	{ "F13", 0x68 },
	{ "F14", 0x69 },
	{ "F15", 0x6a },
	{ "F16", 0x6b },
	{ "F17", 0x6c },
	{ "F18", 0x6d },
	{ "F19", 0x6e },
	{ "F20", 0x6f },
	{ "F21", 0x70 },
	{ "F22", 0x71 },
	{ "F23", 0x72 },
	{ "F24", 0x73 },
	{ "Execute", 0x74 },
	{ "Help", 0x75 },
	{ "Props", 0x76 },
	{ "Select", 0x77 },
	{ "Stop", 0x78 },
	{ "Again", 0x79 },
	{ "Undo", 0x7a },
	{ "Cut", 0x7b },
	{ "Copy", 0x7c },
	{ "Paste", 0x7d },
	{ "Find", 0x7e },
	{ "Mute", 0x7f },
	{ "Volume_Up", 0x80 },
	{ "Volume_Down", 0x81 },
	{ "International1", 0x87 },
	{ "International2", 0x88 },
	{ "International3", 0x89 },
	{ "International4", 0x8a },
	{ "International5", 0x8b },
	{ "International6", 0x8c },
	{ "International7", 0x8d },
	{ "International8", 0x8e },
	{ "International9", 0x8f },
	// media keys
	{ "Media_Play_Pause", 0xe8 },
	{ "Media_Stop_CD", 0xe9 },
	{ "Media_Previous", 0xea },
	{ "Media_Next", 0xeb },
	{ "Media_Eject_CD", 0xec },
	{ "Media_Volume_Up", 0xed },
	{ "Media_Volume_Down", 0xee },
	{ "Media_Mute", 0xef },
	{ "Media_WWW", 0xf0 },
	{ "Media_Back", 0xf1 },
	{ "Media_Forward", 0xf2 },
	{ "Media_Stop", 0xf3 },
	{ "Media_Find", 0xf4 },
	{ "Media_Scroll_Up", 0xf5 },
	{ "Media_Scroll_Down", 0xf6 },
	{ "Media_Edit", 0xf7 },
	{ "Media_Sleep", 0xf8 },
	{ "Media_Screenlock", 0xf9 },
	{ "Media_Refresh", 0xfa },
	{ "Media_Calc", 0xfb } };

std::map< int, uint8_t >  rd_mouse::_c_snipe_dpi_values = {
	{ 200, 0x04 },
	{ 300, 0x06 },
	{ 400, 0x09 },
	{ 500, 0x0b },
	{ 600, 0x0d },
	{ 700, 0x0f },
	{ 800, 0x12 },
	{ 900, 0x14 },
	{ 1000, 0x16 },
	{ 1100, 0x18 }
};

std::map< uint8_t, rd_mouse::rd_report_rate > rd_mouse::_c_report_rate_values = {
	{ 8, rd_mouse::r_125Hz },
	{ 4, rd_mouse::r_250Hz },
	{ 2, rd_mouse::r_500Hz },
	{ 1, rd_mouse::r_1000Hz }
};

std::map< rd_mouse::rd_report_rate, std::string > rd_mouse::_c_report_rate_strings = {
	{ rd_mouse::r_125Hz, "125" },
	{ rd_mouse::r_250Hz, "250" },
	{ rd_mouse::r_500Hz, "500" },
	{ rd_mouse::r_1000Hz, "1000" }
};

std::map< std::array<uint8_t, 2>, rd_mouse::rd_lightmode > rd_mouse::_c_lightmode_values = {
	{ {0x00, 0x00}, rd_mouse::lightmode_off },
	{ {0x01, 0x04}, rd_mouse::lightmode_breathing },
	{ {0x01, 0x08}, rd_mouse::lightmode_rainbow },
	{ {0x01, 0x02}, rd_mouse::lightmode_static },
	{ {0x02, 0x00}, rd_mouse::lightmode_wave },
	{ {0x06, 0x00}, rd_mouse::lightmode_alternating },
	{ {0x07, 0x00}, rd_mouse::lightmode_reactive },
	{ {0x01, 0x10}, rd_mouse::lightmode_flashing }
};

std::map< rd_mouse::rd_lightmode, std::string > rd_mouse::_c_lightmode_strings = {
	{ rd_mouse::lightmode_off, "off" },
	{ rd_mouse::lightmode_breathing, "breathing" },
	{ rd_mouse::lightmode_rainbow, "rainbow" },
	{ rd_mouse::lightmode_static, "static" },
	{ rd_mouse::lightmode_wave, "wave" },
	{ rd_mouse::lightmode_alternating, "alternating" },
	{ rd_mouse::lightmode_reactive, "reactive" },
	{ rd_mouse::lightmode_flashing, "flashing" }
};