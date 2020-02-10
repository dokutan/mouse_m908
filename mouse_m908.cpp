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
 * g++ mouse_m908.cpp -o mouse_m908 -lusb-1.0
 * 
 */

#include <map>
#include <array>
#include <string>
#include <iostream>
#include <exception>
#include <regex>
#include <getopt.h>

#include "include/mouse_m908.h"
#include "include/print_help.cpp"
#include "include/load_config.cpp"

int main( int argc, char **argv ){
	
	mouse_m908 m;
	
	//command line options
	static struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"config", required_argument, 0, 'c'},
		{"profile", required_argument, 0, 'p'},
		{"macro", required_argument, 0, 'm'},
		{"number", required_argument, 0, 'n'},
		//{"repeat", required_argument, 0, 'r'},
		{"bus", required_argument, 0, 'b'},
		{"device", required_argument, 0, 'd'},
		{"kernel-driver", no_argument, 0, 'k'},
		{0, 0, 0, 0}
	};
	
	bool flag_config = false, flag_profile = false;
	bool flag_macro = false, flag_number = false;
	bool flag_bus = false, flag_device = false;
	bool flag_kernel_driver = false;
	//bool flag_repeat;
	std::string string_config, string_profile;
	std::string string_macro, string_number;
	//std::string string_repeat;
	std::string string_bus, string_device;
	
	//parse command line options
	int c, option_index = 0;
	//while( (c = getopt_long( argc, argv, "hc:p:m:n:r:",
	while( (c = getopt_long( argc, argv, "hc:p:m:n:b:d:k",
	long_options, &option_index ) ) != -1 ){
		
		switch( c ){
			case 'h':
				print_help();
				return 0;
				break;
			case 'c':
				flag_config = true;
				string_config = optarg;
				break;
			case 'p':
				flag_profile = true;
				string_profile = optarg;
				break;
			case 'm':
				flag_macro = true;
				string_macro = optarg;
				break;
			case 'n':
				flag_number = true;
				string_number = optarg;
				break;
			case 'b':
				flag_bus = true;
				string_bus = optarg;
				break;
			case 'd':
				flag_device = true;
				string_device = optarg;
				break;
			//case 'r':
			//	flag_repeat = true;
			//	string_repeat = optarg;
			//	break;
			case 'k':
				flag_kernel_driver = true;
				break;
			case '?':
				break;
			default:
				break;
		}
	}
	
	// set wether to detach kernel driver
	m.set_detach_kernel_driver( !flag_kernel_driver );
	
	//load and write config
	if( flag_config ){
		try{
			
			simple_ini_parser pt;
			if( pt.read_ini( string_config ) != 0 ){
				std::cout << "Could not open configuration file.\n";
				return 1;
			}
			
			//parse config file
			//profile 1
			if( pt.get("profile1.lightmode", "") == "breathing" ){ m.set_lightmode( mouse_m908::profile_1, mouse_m908::lightmode_breathing ); }
			if( pt.get("profile1.lightmode", "") == "rainbow" ){ m.set_lightmode( mouse_m908::profile_1, mouse_m908::lightmode_rainbow ); }
			if( pt.get("profile1.lightmode", "") == "static" ){ m.set_lightmode( mouse_m908::profile_1, mouse_m908::lightmode_static ); }
			if( pt.get("profile1.lightmode", "") == "wave" ){ m.set_lightmode( mouse_m908::profile_1, mouse_m908::lightmode_wave ); }
			if( pt.get("profile1.lightmode", "") == "alternating" ){ m.set_lightmode( mouse_m908::profile_1, mouse_m908::lightmode_alternating ); }
			if( pt.get("profile1.lightmode", "") == "reactive" ){ m.set_lightmode( mouse_m908::profile_1, mouse_m908::lightmode_reactive ); }
			if( pt.get("profile1.lightmode", "") == "flashing" ){ m.set_lightmode( mouse_m908::profile_1, mouse_m908::lightmode_flashing ); }
			if( pt.get("profile1.lightmode", "") == "off" ){ m.set_lightmode( mouse_m908::profile_1, mouse_m908::lightmode_off ); }
			if( pt.get("profile1.color", "").length() == 6 ){
				m.set_color( mouse_m908::profile_1,
				{(uint8_t)stoi( pt.get("profile1.color", "").substr(0,2), 0, 16),
				(uint8_t)stoi( pt.get("profile1.color", "").substr(2,2), 0, 16), 
				(uint8_t)stoi( pt.get("profile1.color", "").substr(4,2), 0, 16)} );
			}
			if( pt.get("profile1.brightness", "").length() != 0 ){
				m.set_brightness( mouse_m908::profile_1, (uint8_t)stoi( pt.get("profile1.brightness", ""), 0, 16) );
			}
			if( pt.get("profile1.speed", "").length() != 0 ){
				m.set_speed( mouse_m908::profile_1, (uint8_t)stoi( pt.get("profile1.speed", ""), 0, 16) );
			}
			if( pt.get("profile1.scrollspeed", "").length() != 0 ){
				m.set_scrollspeed( mouse_m908::profile_1, (uint8_t)stoi( pt.get("profile1.scrollspeed", ""), 0, 16) );
			}
			if( pt.get("profile1.dpi1_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_1, 0, false ); }
			if( pt.get("profile1.dpi2_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_1, 1, false ); }
			if( pt.get("profile1.dpi3_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_1, 2, false ); }
			if( pt.get("profile1.dpi4_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_1, 3, false ); }
			if( pt.get("profile1.dpi5_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_1, 4, false ); }
			if( pt.get("profile1.dpi1", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_1, 0, (uint8_t)stoi( pt.get("profile1.dpi1", ""), 0, 16) );	}
			if( pt.get("profile1.dpi2", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_1, 1, (uint8_t)stoi( pt.get("profile1.dpi2", ""), 0, 16) );	}
			if( pt.get("profile1.dpi3", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_1, 2, (uint8_t)stoi( pt.get("profile1.dpi3", ""), 0, 16) );	}
			if( pt.get("profile1.dpi4", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_1, 3, (uint8_t)stoi( pt.get("profile1.dpi4", ""), 0, 16) );	}
			if( pt.get("profile1.dpi5", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_1, 4, (uint8_t)stoi( pt.get("profile1.dpi5", ""), 0, 16) );	}
			if( pt.get("profile1.button_left", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 0, pt.get("profile1.button_left", "") );	}
			if( pt.get("profile1.button_right", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 1, pt.get("profile1.button_right", "") );	}
			if( pt.get("profile1.button_middle", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 2, pt.get("profile1.button_middle", "") );	}
			if( pt.get("profile1.button_fire", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 3, pt.get("profile1.button_fire", "") );	}
			if( pt.get("profile1.button_dpi_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 4, pt.get("profile1.button_dpi_up", "") );	}
			if( pt.get("profile1.button_dpi_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 5, pt.get("profile1.button_dpi_down", "") );	}
			if( pt.get("profile1.button_1", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 6, pt.get("profile1.button_1", "") );	}
			if( pt.get("profile1.button_2", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 7, pt.get("profile1.button_2", "") );	}
			if( pt.get("profile1.button_3", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 8, pt.get("profile1.button_3", "") );	}
			if( pt.get("profile1.button_4", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 9, pt.get("profile1.button_4", "") );	}
			if( pt.get("profile1.button_5", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 10, pt.get("profile1.button_5", "") );	}
			if( pt.get("profile1.button_6", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 11, pt.get("profile1.button_6", "") );	}
			if( pt.get("profile1.button_7", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 12, pt.get("profile1.button_7", "") );	}
			if( pt.get("profile1.button_8", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 13, pt.get("profile1.button_8", "") );	}
			if( pt.get("profile1.button_9", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 14, pt.get("profile1.button_9", "") );	}
			if( pt.get("profile1.button_10", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 15, pt.get("profile1.button_10", "") );	}
			if( pt.get("profile1.button_11", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 16, pt.get("profile1.button_11", "") );	}
			if( pt.get("profile1.button_12", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 17, pt.get("profile1.button_12", "") );	}
			if( pt.get("profile1.scroll_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 18, pt.get("profile1.scroll_up", "") );	}
			if( pt.get("profile1.scroll_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_1, 19, pt.get("profile1.scroll_down", "") );	}
			if( pt.get("profile1.report_rate", "") == "125" ){ m.set_report_rate( mouse_m908::profile_1, mouse_m908::r_125Hz ); }
			if( pt.get("profile1.report_rate", "") == "250" ){ m.set_report_rate( mouse_m908::profile_1, mouse_m908::r_250Hz ); }
			if( pt.get("profile1.report_rate", "") == "500" ){ m.set_report_rate( mouse_m908::profile_1, mouse_m908::r_500Hz ); }
			if( pt.get("profile1.report_rate", "") == "1000" ){ m.set_report_rate( mouse_m908::profile_1, mouse_m908::r_1000Hz ); }
			//profile 2
			if( pt.get("profile2.lightmode", "") == "breathing" ){ m.set_lightmode( mouse_m908::profile_2, mouse_m908::lightmode_breathing ); }
			if( pt.get("profile2.lightmode", "") == "rainbow" ){ m.set_lightmode( mouse_m908::profile_2, mouse_m908::lightmode_rainbow ); }
			if( pt.get("profile2.lightmode", "") == "static" ){ m.set_lightmode( mouse_m908::profile_2, mouse_m908::lightmode_static ); }
			if( pt.get("profile2.lightmode", "") == "wave" ){ m.set_lightmode( mouse_m908::profile_2, mouse_m908::lightmode_wave ); }
			if( pt.get("profile2.lightmode", "") == "alternating" ){ m.set_lightmode( mouse_m908::profile_2, mouse_m908::lightmode_alternating ); }
			if( pt.get("profile2.lightmode", "") == "reactive" ){ m.set_lightmode( mouse_m908::profile_2, mouse_m908::lightmode_reactive ); }
			if( pt.get("profile2.lightmode", "") == "flashing" ){ m.set_lightmode( mouse_m908::profile_2, mouse_m908::lightmode_flashing ); }
			if( pt.get("profile2.lightmode", "") == "off" ){ m.set_lightmode( mouse_m908::profile_2, mouse_m908::lightmode_off ); }
			if( pt.get("profile2.color", "").length() == 6 ){
				m.set_color( mouse_m908::profile_2,
				{(uint8_t)stoi( pt.get("profile2.color", "").substr(0,2), 0, 16),
				(uint8_t)stoi( pt.get("profile2.color", "").substr(2,2), 0, 16), 
				(uint8_t)stoi( pt.get("profile2.color", "").substr(4,2), 0, 16)} );
			}
			if( pt.get("profile2.brightness", "").length() != 0 ){
				m.set_brightness( mouse_m908::profile_2, (uint8_t)stoi( pt.get("profile2.brightness", ""), 0, 16) );
			}
			if( pt.get("profile2.speed", "").length() != 0 ){
				m.set_speed( mouse_m908::profile_2, (uint8_t)stoi( pt.get("profile2.speed", ""), 0, 16) );
			}
			if( pt.get("profile2.scrollspeed", "").length() != 0 ){
				m.set_scrollspeed( mouse_m908::profile_2, (uint8_t)stoi( pt.get("profile2.scrollspeed", ""), 0, 16) );
			}
			if( pt.get("profile2.dpi1_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_2, 0, false ); }
			if( pt.get("profile2.dpi2_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_2, 1, false ); }
			if( pt.get("profile2.dpi3_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_2, 2, false ); }
			if( pt.get("profile2.dpi4_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_2, 3, false ); }
			if( pt.get("profile2.dpi5_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_2, 4, false ); }
			if( pt.get("profile2.dpi1", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_2, 0, (uint8_t)stoi( pt.get("profile2.dpi1", ""), 0, 16) );	}
			if( pt.get("profile2.dpi2", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_2, 1, (uint8_t)stoi( pt.get("profile2.dpi2", ""), 0, 16) );	}
			if( pt.get("profile2.dpi3", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_2, 2, (uint8_t)stoi( pt.get("profile2.dpi3", ""), 0, 16) );	}
			if( pt.get("profile2.dpi4", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_2, 3, (uint8_t)stoi( pt.get("profile2.dpi4", ""), 0, 16) );	}
			if( pt.get("profile2.dpi5", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_2, 4, (uint8_t)stoi( pt.get("profile2.dpi5", ""), 0, 16) );	}
			if( pt.get("profile2.button_left", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 0, pt.get("profile2.button_left", "") );	}
			if( pt.get("profile2.button_right", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 1, pt.get("profile2.button_right", "") );	}
			if( pt.get("profile2.button_middle", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 2, pt.get("profile2.button_middle", "") );	}
			if( pt.get("profile2.button_fire", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 3, pt.get("profile2.button_fire", "") );	}
			if( pt.get("profile2.button_dpi_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 4, pt.get("profile2.button_dpi_up", "") );	}
			if( pt.get("profile2.button_dpi_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 5, pt.get("profile2.button_dpi_down", "") );	}
			if( pt.get("profile2.button_1", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 6, pt.get("profile2.button_1", "") );	}
			if( pt.get("profile2.button_2", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 7, pt.get("profile2.button_2", "") );	}
			if( pt.get("profile2.button_3", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 8, pt.get("profile2.button_3", "") );	}
			if( pt.get("profile2.button_4", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 9, pt.get("profile2.button_4", "") );	}
			if( pt.get("profile2.button_5", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 10, pt.get("profile2.button_5", "") );	}
			if( pt.get("profile2.button_6", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 11, pt.get("profile2.button_6", "") );	}
			if( pt.get("profile2.button_7", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 12, pt.get("profile2.button_7", "") );	}
			if( pt.get("profile2.button_8", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 13, pt.get("profile2.button_8", "") );	}
			if( pt.get("profile2.button_9", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 14, pt.get("profile2.button_9", "") );	}
			if( pt.get("profile2.button_10", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 15, pt.get("profile2.button_10", "") );	}
			if( pt.get("profile2.button_11", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 16, pt.get("profile2.button_11", "") );	}
			if( pt.get("profile2.button_12", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 17, pt.get("profile2.button_12", "") );	}
			if( pt.get("profile2.scroll_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 18, pt.get("profile2.scroll_up", "") );	}
			if( pt.get("profile2.scroll_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_2, 19, pt.get("profile2.scroll_down", "") );	}
			if( pt.get("profile2.report_rate", "") == "125" ){ m.set_report_rate( mouse_m908::profile_2, mouse_m908::r_125Hz ); }
			if( pt.get("profile2.report_rate", "") == "250" ){ m.set_report_rate( mouse_m908::profile_2, mouse_m908::r_250Hz ); }
			if( pt.get("profile2.report_rate", "") == "500" ){ m.set_report_rate( mouse_m908::profile_2, mouse_m908::r_500Hz ); }
			if( pt.get("profile2.report_rate", "") == "1000" ){ m.set_report_rate( mouse_m908::profile_2, mouse_m908::r_1000Hz ); }
			//profile 3
			if( pt.get("profile3.lightmode", "") == "breathing" ){ m.set_lightmode( mouse_m908::profile_3, mouse_m908::lightmode_breathing ); }
			if( pt.get("profile3.lightmode", "") == "rainbow" ){ m.set_lightmode( mouse_m908::profile_3, mouse_m908::lightmode_rainbow ); }
			if( pt.get("profile3.lightmode", "") == "static" ){ m.set_lightmode( mouse_m908::profile_3, mouse_m908::lightmode_static ); }
			if( pt.get("profile3.lightmode", "") == "wave" ){ m.set_lightmode( mouse_m908::profile_3, mouse_m908::lightmode_wave ); }
			if( pt.get("profile3.lightmode", "") == "alternating" ){ m.set_lightmode( mouse_m908::profile_3, mouse_m908::lightmode_alternating ); }
			if( pt.get("profile3.lightmode", "") == "reactive" ){ m.set_lightmode( mouse_m908::profile_3, mouse_m908::lightmode_reactive ); }
			if( pt.get("profile3.lightmode", "") == "flashing" ){ m.set_lightmode( mouse_m908::profile_3, mouse_m908::lightmode_flashing ); }
			if( pt.get("profile3.lightmode", "") == "off" ){ m.set_lightmode( mouse_m908::profile_3, mouse_m908::lightmode_off ); }
			if( pt.get("profile3.color", "").length() == 6 ){
				m.set_color( mouse_m908::profile_3,
				{(uint8_t)stoi( pt.get("profile3.color", "").substr(0,2), 0, 16),
				(uint8_t)stoi( pt.get("profile3.color", "").substr(2,2), 0, 16), 
				(uint8_t)stoi( pt.get("profile3.color", "").substr(4,2), 0, 16)} );
			}
			if( pt.get("profile3.brightness", "").length() != 0 ){
				m.set_brightness( mouse_m908::profile_3, (uint8_t)stoi( pt.get("profile3.brightness", ""), 0, 16) );
			}
			if( pt.get("profile3.speed", "").length() != 0 ){
				m.set_speed( mouse_m908::profile_3, (uint8_t)stoi( pt.get("profile3.speed", ""), 0, 16) );
			}
			if( pt.get("profile3.scrollspeed", "").length() != 0 ){
				m.set_scrollspeed( mouse_m908::profile_3, (uint8_t)stoi( pt.get("profile3.scrollspeed", ""), 0, 16) );
			}
			if( pt.get("profile3.dpi1_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_3, 0, false ); }
			if( pt.get("profile3.dpi2_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_3, 1, false ); }
			if( pt.get("profile3.dpi3_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_3, 2, false ); }
			if( pt.get("profile3.dpi4_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_3, 3, false ); }
			if( pt.get("profile3.dpi5_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_3, 4, false ); }
			if( pt.get("profile3.dpi1", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_3, 0, (uint8_t)stoi( pt.get("profile3.dpi1", ""), 0, 16) );	}
			if( pt.get("profile3.dpi2", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_3, 1, (uint8_t)stoi( pt.get("profile3.dpi2", ""), 0, 16) );	}
			if( pt.get("profile3.dpi3", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_3, 2, (uint8_t)stoi( pt.get("profile3.dpi3", ""), 0, 16) );	}
			if( pt.get("profile3.dpi4", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_3, 3, (uint8_t)stoi( pt.get("profile3.dpi4", ""), 0, 16) );	}
			if( pt.get("profile3.dpi5", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_3, 4, (uint8_t)stoi( pt.get("profile3.dpi5", ""), 0, 16) );	}
			if( pt.get("profile3.button_left", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 0, pt.get("profile3.button_left", "") );	}
			if( pt.get("profile3.button_right", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 1, pt.get("profile3.button_right", "") );	}
			if( pt.get("profile3.button_middle", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 2, pt.get("profile3.button_middle", "") );	}
			if( pt.get("profile3.button_fire", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 3, pt.get("profile3.button_fire", "") );	}
			if( pt.get("profile3.button_dpi_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 4, pt.get("profile3.button_dpi_up", "") );	}
			if( pt.get("profile3.button_dpi_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 5, pt.get("profile3.button_dpi_down", "") );	}
			if( pt.get("profile3.button_1", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 6, pt.get("profile3.button_1", "") );	}
			if( pt.get("profile3.button_2", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 7, pt.get("profile3.button_2", "") );	}
			if( pt.get("profile3.button_3", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 8, pt.get("profile3.button_3", "") );	}
			if( pt.get("profile3.button_4", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 9, pt.get("profile3.button_4", "") );	}
			if( pt.get("profile3.button_5", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 10, pt.get("profile3.button_5", "") );	}
			if( pt.get("profile3.button_6", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 11, pt.get("profile3.button_6", "") );	}
			if( pt.get("profile3.button_7", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 12, pt.get("profile3.button_7", "") );	}
			if( pt.get("profile3.button_8", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 13, pt.get("profile3.button_8", "") );	}
			if( pt.get("profile3.button_9", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 14, pt.get("profile3.button_9", "") );	}
			if( pt.get("profile3.button_10", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 15, pt.get("profile3.button_10", "") );	}
			if( pt.get("profile3.button_11", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 16, pt.get("profile3.button_11", "") );	}
			if( pt.get("profile3.button_12", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 17, pt.get("profile3.button_12", "") );	}
			if( pt.get("profile3.scroll_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 18, pt.get("profile3.scroll_up", "") );	}
			if( pt.get("profile3.scroll_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_3, 19, pt.get("profile3.scroll_down", "") );	}
			if( pt.get("profile3.report_rate", "") == "125" ){ m.set_report_rate( mouse_m908::profile_3, mouse_m908::r_125Hz ); }
			if( pt.get("profile3.report_rate", "") == "250" ){ m.set_report_rate( mouse_m908::profile_3, mouse_m908::r_250Hz ); }
			if( pt.get("profile3.report_rate", "") == "500" ){ m.set_report_rate( mouse_m908::profile_3, mouse_m908::r_500Hz ); }
			if( pt.get("profile3.report_rate", "") == "1000" ){ m.set_report_rate( mouse_m908::profile_3, mouse_m908::r_1000Hz ); }
			//profile 4
			if( pt.get("profile4.lightmode", "") == "breathing" ){ m.set_lightmode( mouse_m908::profile_4, mouse_m908::lightmode_breathing ); }
			if( pt.get("profile4.lightmode", "") == "rainbow" ){ m.set_lightmode( mouse_m908::profile_4, mouse_m908::lightmode_rainbow ); }
			if( pt.get("profile4.lightmode", "") == "static" ){ m.set_lightmode( mouse_m908::profile_4, mouse_m908::lightmode_static ); }
			if( pt.get("profile4.lightmode", "") == "wave" ){ m.set_lightmode( mouse_m908::profile_4, mouse_m908::lightmode_wave ); }
			if( pt.get("profile4.lightmode", "") == "alternating" ){ m.set_lightmode( mouse_m908::profile_4, mouse_m908::lightmode_alternating ); }
			if( pt.get("profile4.lightmode", "") == "reactive" ){ m.set_lightmode( mouse_m908::profile_4, mouse_m908::lightmode_reactive ); }
			if( pt.get("profile4.lightmode", "") == "flashing" ){ m.set_lightmode( mouse_m908::profile_4, mouse_m908::lightmode_flashing ); }
			if( pt.get("profile4.lightmode", "") == "off" ){ m.set_lightmode( mouse_m908::profile_4, mouse_m908::lightmode_off ); }
			if( pt.get("profile4.color", "").length() == 6 ){
				m.set_color( mouse_m908::profile_4,
				{(uint8_t)stoi( pt.get("profile4.color", "").substr(0,2), 0, 16),
				(uint8_t)stoi( pt.get("profile4.color", "").substr(2,2), 0, 16), 
				(uint8_t)stoi( pt.get("profile4.color", "").substr(4,2), 0, 16)} );
			}
			if( pt.get("profile4.brightness", "").length() != 0 ){
				m.set_brightness( mouse_m908::profile_4, (uint8_t)stoi( pt.get("profile4.brightness", ""), 0, 16) );
			}
			if( pt.get("profile4.speed", "").length() != 0 ){
				m.set_speed( mouse_m908::profile_4, (uint8_t)stoi( pt.get("profile4.speed", ""), 0, 16) );
			}
			if( pt.get("profile4.scrollspeed", "").length() != 0 ){
				m.set_scrollspeed( mouse_m908::profile_4, (uint8_t)stoi( pt.get("profile4.scrollspeed", ""), 0, 16) );
			}
			if( pt.get("profile4.dpi1_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_4, 0, false ); }
			if( pt.get("profile4.dpi2_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_4, 1, false ); }
			if( pt.get("profile4.dpi3_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_4, 2, false ); }
			if( pt.get("profile4.dpi4_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_4, 3, false ); }
			if( pt.get("profile4.dpi5_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_4, 4, false ); }
			if( pt.get("profile4.dpi1", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_4, 0, (uint8_t)stoi( pt.get("profile4.dpi1", ""), 0, 16) );	}
			if( pt.get("profile4.dpi2", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_4, 1, (uint8_t)stoi( pt.get("profile4.dpi2", ""), 0, 16) );	}
			if( pt.get("profile4.dpi3", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_4, 2, (uint8_t)stoi( pt.get("profile4.dpi3", ""), 0, 16) );	}
			if( pt.get("profile4.dpi4", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_4, 3, (uint8_t)stoi( pt.get("profile4.dpi4", ""), 0, 16) );	}
			if( pt.get("profile4.dpi5", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_4, 4, (uint8_t)stoi( pt.get("profile4.dpi5", ""), 0, 16) );	}
			if( pt.get("profile4.button_left", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 0, pt.get("profile4.button_left", "") );	}
			if( pt.get("profile4.button_right", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 1, pt.get("profile4.button_right", "") );	}
			if( pt.get("profile4.button_middle", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 2, pt.get("profile4.button_middle", "") );	}
			if( pt.get("profile4.button_fire", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 3, pt.get("profile4.button_fire", "") );	}
			if( pt.get("profile4.button_dpi_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 4, pt.get("profile4.button_dpi_up", "") );	}
			if( pt.get("profile4.button_dpi_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 5, pt.get("profile4.button_dpi_down", "") );	}
			if( pt.get("profile4.button_1", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 6, pt.get("profile4.button_1", "") );	}
			if( pt.get("profile4.button_2", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 7, pt.get("profile4.button_2", "") );	}
			if( pt.get("profile4.button_3", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 8, pt.get("profile4.button_3", "") );	}
			if( pt.get("profile4.button_4", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 9, pt.get("profile4.button_4", "") );	}
			if( pt.get("profile4.button_5", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 10, pt.get("profile4.button_5", "") );	}
			if( pt.get("profile4.button_6", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 11, pt.get("profile4.button_6", "") );	}
			if( pt.get("profile4.button_7", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 12, pt.get("profile4.button_7", "") );	}
			if( pt.get("profile4.button_8", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 13, pt.get("profile4.button_8", "") );	}
			if( pt.get("profile4.button_9", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 14, pt.get("profile4.button_9", "") );	}
			if( pt.get("profile4.button_10", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 15, pt.get("profile4.button_10", "") );	}
			if( pt.get("profile4.button_11", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 16, pt.get("profile4.button_11", "") );	}
			if( pt.get("profile4.button_12", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 17, pt.get("profile4.button_12", "") );	}
			if( pt.get("profile4.scroll_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 18, pt.get("profile4.scroll_up", "") );	}
			if( pt.get("profile4.scroll_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_4, 19, pt.get("profile4.scroll_down", "") );	}
			if( pt.get("profile4.report_rate", "") == "125" ){ m.set_report_rate( mouse_m908::profile_4, mouse_m908::r_125Hz ); }
			if( pt.get("profile4.report_rate", "") == "250" ){ m.set_report_rate( mouse_m908::profile_4, mouse_m908::r_250Hz ); }
			if( pt.get("profile4.report_rate", "") == "500" ){ m.set_report_rate( mouse_m908::profile_4, mouse_m908::r_500Hz ); }
			if( pt.get("profile4.report_rate", "") == "1000" ){ m.set_report_rate( mouse_m908::profile_4, mouse_m908::r_1000Hz ); }
			//profile 5
			if( pt.get("profile5.lightmode", "") == "breathing" ){ m.set_lightmode( mouse_m908::profile_5, mouse_m908::lightmode_breathing ); }
			if( pt.get("profile5.lightmode", "") == "rainbow" ){ m.set_lightmode( mouse_m908::profile_5, mouse_m908::lightmode_rainbow ); }
			if( pt.get("profile5.lightmode", "") == "static" ){ m.set_lightmode( mouse_m908::profile_5, mouse_m908::lightmode_static ); }
			if( pt.get("profile5.lightmode", "") == "wave" ){ m.set_lightmode( mouse_m908::profile_5, mouse_m908::lightmode_wave ); }
			if( pt.get("profile5.lightmode", "") == "alternating" ){ m.set_lightmode( mouse_m908::profile_5, mouse_m908::lightmode_alternating ); }
			if( pt.get("profile5.lightmode", "") == "reactive" ){ m.set_lightmode( mouse_m908::profile_5, mouse_m908::lightmode_reactive ); }
			if( pt.get("profile5.lightmode", "") == "flashing" ){ m.set_lightmode( mouse_m908::profile_5, mouse_m908::lightmode_flashing ); }
			if( pt.get("profile5.lightmode", "") == "off" ){ m.set_lightmode( mouse_m908::profile_5, mouse_m908::lightmode_off ); }
			if( pt.get("profile5.color", "").length() == 6 ){
				m.set_color( mouse_m908::profile_5,
				{(uint8_t)stoi( pt.get("profile5.color", "").substr(0,2), 0, 16),
				(uint8_t)stoi( pt.get("profile5.color", "").substr(2,2), 0, 16), 
				(uint8_t)stoi( pt.get("profile5.color", "").substr(4,2), 0, 16)} );
			}
			if( pt.get("profile5.brightness", "").length() != 0 ){
				m.set_brightness( mouse_m908::profile_5, (uint8_t)stoi( pt.get("profile5.brightness", ""), 0, 16) );
			}
			if( pt.get("profile5.speed", "").length() != 0 ){
				m.set_speed( mouse_m908::profile_5, (uint8_t)stoi( pt.get("profile5.speed", ""), 0, 16) );
			}
			if( pt.get("profile5.scrollspeed", "").length() != 0 ){
				m.set_scrollspeed( mouse_m908::profile_5, (uint8_t)stoi( pt.get("profile5.scrollspeed", ""), 0, 16) );
			}
			if( pt.get("profile5.dpi1_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_5, 0, false ); }
			if( pt.get("profile5.dpi2_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_5, 1, false ); }
			if( pt.get("profile5.dpi3_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_5, 2, false ); }
			if( pt.get("profile5.dpi4_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_5, 3, false ); }
			if( pt.get("profile5.dpi5_enable", "") == "0" ){ m.set_dpi_enable( mouse_m908::profile_5, 4, false ); }
			if( pt.get("profile5.dpi1", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_5, 0, (uint8_t)stoi( pt.get("profile5.dpi1", ""), 0, 16) );	}
			if( pt.get("profile5.dpi2", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_5, 1, (uint8_t)stoi( pt.get("profile5.dpi2", ""), 0, 16) );	}
			if( pt.get("profile5.dpi3", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_5, 2, (uint8_t)stoi( pt.get("profile5.dpi3", ""), 0, 16) );	}
			if( pt.get("profile5.dpi4", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_5, 3, (uint8_t)stoi( pt.get("profile5.dpi4", ""), 0, 16) );	}
			if( pt.get("profile5.dpi5", "").length() != 0 ){ m.set_dpi( mouse_m908::profile_5, 4, (uint8_t)stoi( pt.get("profile5.dpi5", ""), 0, 16) );	}
			if( pt.get("profile5.button_left", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 0, pt.get("profile5.button_left", "") );	}
			if( pt.get("profile5.button_right", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 1, pt.get("profile5.button_right", "") );	}
			if( pt.get("profile5.button_middle", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 2, pt.get("profile5.button_middle", "") );	}
			if( pt.get("profile5.button_fire", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 3, pt.get("profile5.button_fire", "") );	}
			if( pt.get("profile5.button_dpi_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 4, pt.get("profile5.button_dpi_up", "") );	}
			if( pt.get("profile5.button_dpi_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 5, pt.get("profile5.button_dpi_down", "") );	}
			if( pt.get("profile5.button_1", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 6, pt.get("profile5.button_1", "") );	}
			if( pt.get("profile5.button_2", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 7, pt.get("profile5.button_2", "") );	}
			if( pt.get("profile5.button_3", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 8, pt.get("profile5.button_3", "") );	}
			if( pt.get("profile5.button_4", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 9, pt.get("profile5.button_4", "") );	}
			if( pt.get("profile5.button_5", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 10, pt.get("profile5.button_5", "") );	}
			if( pt.get("profile5.button_6", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 11, pt.get("profile5.button_6", "") );	}
			if( pt.get("profile5.button_7", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 12, pt.get("profile5.button_7", "") );	}
			if( pt.get("profile5.button_8", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 13, pt.get("profile5.button_8", "") );	}
			if( pt.get("profile5.button_9", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 14, pt.get("profile5.button_9", "") );	}
			if( pt.get("profile5.button_10", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 15, pt.get("profile5.button_10", "") );	}
			if( pt.get("profile5.button_11", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 16, pt.get("profile5.button_11", "") );	}
			if( pt.get("profile5.button_12", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 17, pt.get("profile5.button_12", "") );	}
			if( pt.get("profile5.scroll_up", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 18, pt.get("profile5.scroll_up", "") );	}
			if( pt.get("profile5.scroll_down", "").length() != 0 ){ m.set_key_mapping( mouse_m908::profile_5, 19, pt.get("profile5.scroll_down", "") );	}
			if( pt.get("profile5.report_rate", "") == "125" ){ m.set_report_rate( mouse_m908::profile_5, mouse_m908::r_125Hz ); }
			if( pt.get("profile5.report_rate", "") == "250" ){ m.set_report_rate( mouse_m908::profile_5, mouse_m908::r_250Hz ); }
			if( pt.get("profile5.report_rate", "") == "500" ){ m.set_report_rate( mouse_m908::profile_5, mouse_m908::r_500Hz ); }
			if( pt.get("profile5.report_rate", "") == "1000" ){ m.set_report_rate( mouse_m908::profile_5, mouse_m908::r_1000Hz ); }
			
			// open mouse
			if( flag_bus != flag_device ){ // improper arguments
				
				std::cout << "Missing argument, --bus and --device must be used together.\n";
				return 1;
				
			} else if( flag_bus && flag_device ){ // open with bus and device
				
				if( !std::regex_match( string_bus, std::regex("[0-9]+") ) ||
					!std::regex_match( string_device, std::regex("[0-9]+") ) ){
					
					std::cout << "Wrong argument, expected number.\n";
					return 1;
				}
				
				int r;
				r = m.open_mouse_bus_device( stoi(string_bus), stoi(string_device) );
				if( r != 0 ){
					std::cout << "Couldn't open mouse\n";
					return 1;
				}
				
			} else{ // open with vid and pid
				
				int r;
				r = m.open_mouse();
				if( r != 0 ){
					std::cout << "Couldn't open mouse\n";
					return 1;
				}
				
			}
			
			// write settings
			m.write_settings();
			
			m.close_mouse();
		} catch( std::exception& e ){
			std::cerr << "Error: " << e.what() << "\n";
			return 1;
		}
		
	}
	
	// change active profile
	if( flag_profile ){
		
		
		// set profile
		if( !std::regex_match( string_profile, std::regex("[1-5]") ) ){
			
			std::cout << "Wrong argument, expected 1-5.\n";
			return 1;
		}
		
		if( string_profile == "1" ){ m.set_profile( mouse_m908::profile_1 ); }
		if( string_profile == "2" ){ m.set_profile( mouse_m908::profile_2 ); }
		if( string_profile == "3" ){ m.set_profile( mouse_m908::profile_3 ); }
		if( string_profile == "4" ){ m.set_profile( mouse_m908::profile_4 ); }
		if( string_profile == "5" ){ m.set_profile( mouse_m908::profile_5 ); }
		
		
		// open mouse
		if( flag_bus != flag_device ){ // improper arguments
			
			std::cout << "Missing argument, --bus and --device must be used together.\n";
			return 1;
			
		} else if( flag_bus && flag_device ){ // open with bus and device
			
			if( !std::regex_match( string_bus, std::regex("[0-9]+") ) ||
				!std::regex_match( string_device, std::regex("[0-9]+") ) ){
				
				std::cout << "Wrong argument, expected number.\n";
				return 1;
			}
			
			int r;
			r = m.open_mouse_bus_device( stoi(string_bus), stoi(string_device) );
			if( r != 0 ){
				std::cout << "Couldn't open mouse\n";
				return 1;
			}
			
		} else{ // open with vid and pid
			
			int r;
			r = m.open_mouse();
			if( r != 0 ){
				std::cout << "Couldn't open mouse\n";
				return 1;
			}
			
		}
		
		// write profile
		m.write_profile();
		
		m.close_mouse();
		
	}
	
	// send macro
	if( flag_macro && flag_number ){
		
		
		// set macro and macro slot (number)
		int r;
		int number;
		
		if( std::regex_match( string_number, std::regex("[0-9]+") ) ){
			number = (int)stoi(string_number);
		} else{
			std::cout << "Wrong argument, expected 1-15.\n";
			return 1;
		}
		
		if( number < 1 || number > 15 ){
			std::cout << "Wrong argument, expected 1-15.\n";
			return 1;
		}
		
		r = m.set_macro( number, string_macro );
		if( r != 0 ){
			std::cout << "Couldn't load macro\n";
			return 1;
		}
		
		
		// open mouse
		if( flag_bus != flag_device ){ // improper arguments
			
			std::cout << "Missing argument, --bus and --device must be used together.\n";
			return 1;
			
		} else if( flag_bus && flag_device ){ // open with bus and device
			
			if( !std::regex_match( string_bus, std::regex("[0-9]+") ) ||
				!std::regex_match( string_device, std::regex("[0-9]+") ) ){
				
				std::cout << "Wrong argument, expected number.\n";
				return 1;
			}
			
			int r;
			r = m.open_mouse_bus_device( stoi(string_bus), stoi(string_device) );
			if( r != 0 ){
				std::cout << "Couldn't open mouse\n";
				return 1;
			}
			
		} else{ // open with vid and pid
			
			int r;
			r = m.open_mouse();
			if( r != 0 ){
				std::cout << "Couldn't open mouse\n";
				return 1;
			}
			
		}
		
		// write macro
		m.write_macro(number);
		
		/*if( flag_repeat ){
			int repeat = (int)stoi(string_repeat);
			r = m.set_macro_repeat( number, repeat );
			if( r != 0 ){
				std::cout << "Invalid repeats\n";
				return 1;
			}
			m.write_macro_repeat( number );
		}*/
		
		m.close_mouse();
		
	} else if( flag_macro || flag_number ){
		std::cout << "Misssing option, --macro and --number must be used together.\n";
	}
	
	return 0;
}
