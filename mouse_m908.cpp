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
#include <fstream>
#include <exception>
#include <regex>
#include <getopt.h>

#include "include/rd_mouse.h"
#include "include/load_config.h"
#include "include/print_help.cpp"

// this is the default version string
// the version string gets overwritten by the makefile
#ifndef VERSION_STRING
#define VERSION_STRING "no version defined during compilation"
#endif



// this function checks its arguments and opens the mouse accordingly
// (with vid and pid or with bus and device)
template< typename T >int open_mouse_wrapper( T &m, const bool flag_bus, const bool flag_device,
	const std::string &string_bus, const std::string &string_device );

// function to perform all actions on the mouse
template< typename T > int perform_actions( 
bool flag_config, bool flag_profile, bool flag_macro, bool flag_number,
bool flag_bus, bool flag_device, bool flag_kernel_driver,
bool flag_dump_settings, bool flag_read_settings,
std::string string_config, std::string string_profile, std::string string_macro,
std::string string_number, std::string string_bus, std::string string_device,
std::string string_dump, std::string string_read );



// main function
int main( int argc, char **argv ){
	
	try{
		// if no arguments: print help
		if( argc == 1 ){
			print_help();
			return 0;
		}
		
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
			{"version", no_argument, 0, 'v'},
			{"dump", required_argument, 0, 'D'},
			{"read", required_argument, 0, 'R'},
			{"model", required_argument, 0, 'M'},
			{0, 0, 0, 0}
		};
		
		bool flag_config = false, flag_profile = false;
		bool flag_macro = false, flag_number = false;
		bool flag_bus = false, flag_device = false;
		bool flag_kernel_driver = false;
		bool flag_version = false;
		bool flag_dump_settings = false;
		bool flag_read_settings = false;
		//bool flag_repeat;
		
		std::string string_config, string_profile;
		std::string string_macro, string_number;
		//std::string string_repeat;
		std::string string_bus, string_device;
		std::string string_dump, string_read;
		std::string string_model = "";
		
		// string_model is set by the -M option, if empty,
		// rd_mouse::detect() is called
		
		//parse command line options
		int c, option_index = 0;
		while( (c = getopt_long( argc, argv, "hc:p:m:n:b:d:kvD:R:M:",
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
				case 'v':
					flag_version = true;
					break;
				case 'D':
					flag_dump_settings = true;
					string_dump = optarg;
					break;
				case 'R':
					flag_read_settings = true;
					string_read = optarg;
					break;
				case 'M':
					string_model = optarg;
					break;
				case '?':
					break;
				default:
					break;
			}
		}
		
		// print version if requested
		if( flag_version )
			std::cout << "Version: " << VERSION_STRING << "\n";
		
		// detect mouse if no model was specified
		if( string_model == "" ){
			
			string_model = rd_mouse::detect();
			
			// no mouse found by detect()
			if( string_model == "" ){
				
				throw std::string( 
					"Couldn't detect mouse.\n"
					"- Check hardware and permissions (maybe you need to be root?)\n"
					"- Try with the --model option\n"
					"If nothing works please report this as a bug."
				);
				
			}
		}
		
		// parse model → call perform_actions()
		if( string_model == "908" ){
			
			return perform_actions< mouse_m908 >(
				flag_config, flag_profile, flag_macro, flag_number,
				flag_bus, flag_device, flag_kernel_driver,
				flag_dump_settings, flag_read_settings,
				string_config, string_profile, string_macro,
				string_number, string_bus, string_device,
				string_dump, string_read );
				
		}else if( string_model == "709" ){
			
			return perform_actions< mouse_m709 >(
				flag_config, flag_profile, flag_macro, flag_number,
				flag_bus, flag_device, flag_kernel_driver,
				flag_dump_settings, flag_read_settings,
				string_config, string_profile, string_macro,
				string_number, string_bus, string_device,
				string_dump, string_read );
				
		}else if( string_model == "711" ){
			
			return perform_actions< mouse_m711 >(
				flag_config, flag_profile, flag_macro, flag_number,
				flag_bus, flag_device, flag_kernel_driver,
				flag_dump_settings, flag_read_settings,
				string_config, string_profile, string_macro,
				string_number, string_bus, string_device,
				string_dump, string_read );
				
		}else if( string_model == "715" ){
			
			return perform_actions< mouse_m715 >(
				flag_config, flag_profile, flag_macro, flag_number,
				flag_bus, flag_device, flag_kernel_driver,
				flag_dump_settings, flag_read_settings,
				string_config, string_profile, string_macro,
				string_number, string_bus, string_device,
				string_dump, string_read );
				
		}else{
			
			throw std::string(
				"Unknown model, valid options are:\n"
				"709\n711\n715\n908"
			);
			
		}
	
	} catch( std::string const &message ){ // print error message and quit
		
		std::cerr << message << "\n";
		return 1;
		
	} catch( std::exception const &e ){ // handle exceptions
		
		std::cerr << "An exception occured:\n" << e.what() << "\n";
		return 1;
		
	}
	
	return 0;
}



template< typename T > int perform_actions( 
bool flag_config, bool flag_profile, bool flag_macro, bool flag_number,
bool flag_bus, bool flag_device, bool flag_kernel_driver,
bool flag_dump_settings, bool flag_read_settings,
std::string string_config, std::string string_profile, std::string string_macro,
std::string string_number, std::string string_bus, std::string string_device,
std::string string_dump, std::string string_read ){
	
	// create mouse object
	T m;
	
	// set whether to detach kernel driver
	m.set_detach_kernel_driver( !flag_kernel_driver );
	
	// open mouse, throws std::string in case of an error, handling in main()
	open_mouse_wrapper( m, flag_bus, flag_device, string_bus, string_device );
	
	try{
		// read settings and dump raw data
		if( flag_dump_settings ){
			
			// dump to file or cout
			if( string_dump != "-" ){
				std::ofstream out( string_dump );
				
				if( out.is_open() ){				
					// dump settings
					m.dump_settings( out );
				
					out.close();
				} else{
					throw std::string( "Couldn't open "+string_dump );
				}
			} else{
				m.dump_settings( std::cout );
			}
			
		}
		
		// read settings and print in .ini format
		if( flag_read_settings ){
			
			// dump to file or cout
			if( string_read != "-" ){
				std::ofstream out( string_read );
				
				if( out.is_open() ){				
					// read settings
					m.read_and_print_settings( out );
				
					out.close();
				} else{
					throw std::string( "Couldn't open "+string_read );
				}
			} else{
				m.read_and_print_settings( std::cout );
			}
			
		}
		
		// load and write config
		if( flag_config ){
			
			simple_ini_parser pt;
			if( pt.read_ini( string_config ) != 0 )
				throw std::string( "Could not open configuration file." );
			
			// lookup table int → profile enum
			std::array< mouse_m908::rd_profile, 5 > profile_lut = { mouse_m908::profile_1, mouse_m908::profile_2, mouse_m908::profile_3, mouse_m908::profile_4, mouse_m908::profile_5 };
			
			//parse config file
			for( int i = 1; i < 6; i++ ){
				
				if( pt.get("profile"+std::to_string(i)+".lightmode", "") == "breathing" ){ m.set_lightmode( profile_lut[i-1], mouse_m908::lightmode_breathing ); }
				if( pt.get("profile"+std::to_string(i)+".lightmode", "") == "rainbow" ){ m.set_lightmode( profile_lut[i-1], mouse_m908::lightmode_rainbow ); }
				if( pt.get("profile"+std::to_string(i)+".lightmode", "") == "static" ){ m.set_lightmode( profile_lut[i-1], mouse_m908::lightmode_static ); }
				if( pt.get("profile"+std::to_string(i)+".lightmode", "") == "wave" ){ m.set_lightmode( profile_lut[i-1], mouse_m908::lightmode_wave ); }
				if( pt.get("profile"+std::to_string(i)+".lightmode", "") == "alternating" ){ m.set_lightmode( profile_lut[i-1], mouse_m908::lightmode_alternating ); }
				if( pt.get("profile"+std::to_string(i)+".lightmode", "") == "reactive" ){ m.set_lightmode( profile_lut[i-1], mouse_m908::lightmode_reactive ); }
				if( pt.get("profile"+std::to_string(i)+".lightmode", "") == "flashing" ){ m.set_lightmode( profile_lut[i-1], mouse_m908::lightmode_flashing ); }
				if( pt.get("profile"+std::to_string(i)+".lightmode", "") == "off" ){ m.set_lightmode( profile_lut[i-1], mouse_m908::lightmode_off ); }
				
				if( pt.get("profile"+std::to_string(i)+".color", "").length() == 6 ){
					m.set_color( profile_lut[i-1],
					{(uint8_t)stoi( pt.get("profile"+std::to_string(i)+".color", "").substr(0,2), 0, 16),
					(uint8_t)stoi( pt.get("profile"+std::to_string(i)+".color", "").substr(2,2), 0, 16), 
					(uint8_t)stoi( pt.get("profile"+std::to_string(i)+".color", "").substr(4,2), 0, 16)} );
				}
				
				if( pt.get("profile"+std::to_string(i)+".brightness", "").length() != 0 ){
					m.set_brightness( profile_lut[i-1], (uint8_t)stoi( pt.get("profile"+std::to_string(i)+".brightness", ""), 0, 16) );
				}
				
				if( pt.get("profile"+std::to_string(i)+".speed", "").length() != 0 ){
					m.set_speed( profile_lut[i-1], (uint8_t)stoi( pt.get("profile"+std::to_string(i)+".speed", ""), 0, 16) );
				}
				
				if( pt.get("profile"+std::to_string(i)+".scrollspeed", "").length() != 0 ){
					m.set_scrollspeed( profile_lut[i-1], (uint8_t)stoi( pt.get("profile"+std::to_string(i)+".scrollspeed", ""), 0, 16) );
				}
				
				// DPI
				for( int j = 1; j < 6; j++ ){
					
					// DPI level disabled
					if( pt.get("profile"+std::to_string(i)+".dpi"+std::to_string(j)+"_enable", "") == "0" )
						m.set_dpi_enable( profile_lut[i-1], j-1, false );
					
					// DPI value
					if( pt.get("profile"+std::to_string(i)+".dpi"+std::to_string(j), "").length() != 0 ){ // non-empty dpi value
						
						if( m.set_dpi( profile_lut[i-1], j-1, pt.get("profile"+std::to_string(i)+".dpi"+std::to_string(j), "") ) != 0 ) // if invalid dpi value
							std::cerr << "Warning: Unknown DPI value " << pt.get("profile"+std::to_string(i)+".dpi"+std::to_string(j), "") << "\n";
					}
				}
				
				if( pt.get("profile"+std::to_string(i)+".report_rate", "") == "125" ){ m.set_report_rate( profile_lut[i-1], mouse_m908::r_125Hz ); }
				if( pt.get("profile"+std::to_string(i)+".report_rate", "") == "250" ){ m.set_report_rate( profile_lut[i-1], mouse_m908::r_250Hz ); }
				if( pt.get("profile"+std::to_string(i)+".report_rate", "") == "500" ){ m.set_report_rate( profile_lut[i-1], mouse_m908::r_500Hz ); }
				if( pt.get("profile"+std::to_string(i)+".report_rate", "") == "1000" ){ m.set_report_rate( profile_lut[i-1], mouse_m908::r_1000Hz ); }
				
				// button mapping
				for( auto key : m.button_names() ){
					if( pt.get("profile"+std::to_string(i)+"."+key.second, "").length() != 0 ){ m.set_key_mapping( profile_lut[i-1], key.first, pt.get("profile"+std::to_string(i)+"."+key.second, "") );	}
				}
				
			}
			
			// write settings
			m.write_settings();
			
		}
		
		// change active profile
		if( flag_profile ){
			
			
			// set profile
			if( !std::regex_match( string_profile, std::regex("[1-5]") ) ){
				
				throw std::string( "Wrong argument, expected 1-5." );
				return 1;
			}
			
			if( string_profile == "1" ){ m.set_profile( mouse_m908::profile_1 ); }
			if( string_profile == "2" ){ m.set_profile( mouse_m908::profile_2 ); }
			if( string_profile == "3" ){ m.set_profile( mouse_m908::profile_3 ); }
			if( string_profile == "4" ){ m.set_profile( mouse_m908::profile_4 ); }
			if( string_profile == "5" ){ m.set_profile( mouse_m908::profile_5 ); }
			
			// write profile
			m.write_profile();
			
		}
		
		// send all macros
		if( flag_macro && !flag_number ){
			
			// load macros
			int r = m.set_all_macros( string_macro );
			
			if( r != 0 )
				throw std::string( "Couldn't load macros." );
			
			// write macros
			for( int i = 1; i < 16; i++ )
				m.write_macro(i);
			
		}
		
		// send individual macro
		if( flag_macro && flag_number ){
			
			
			// set macro and macro slot (number)
			int number;
			
			if( std::regex_match( string_number, std::regex("[0-9]+") ) ){
				number = (int)stoi(string_number);
			} else{
				throw std::string( "Wrong argument, expected 1-15." );
			}
			
			if( number < 1 || number > 15 )
				throw std::string( "Wrong argument, expected 1-15." );
			
			if( m.set_macro( number, string_macro ) != 0 )
				throw std::string( "Couldn't load macro" );
			
			// write macro
			m.write_macro(number);
			
			// Repeating macros appear to be broken (in the official software as well),
			// so this option is disabled for now.
			// If you want to try it out, uncomment the next section and the
			// appropriate lines in the commandline options section
			/*if( flag_repeat ){
				int repeat = (int)stoi(string_repeat);
				r = m.set_macro_repeat( number, repeat );
				if( r != 0 ){
					std::cout << "Invalid repeats\n";
					return 1;
				}
				m.write_macro_repeat( number );
			}*/
			
		} else if( !flag_macro && flag_number ){
			throw std::string( "Misssing option, --macro and --number must be used together." );
		}
	
	
	// error handling
	} catch( std::string const &message ){ // close mouse, rethrow
		
		m.close_mouse();
		throw message;
		
	} catch( std::exception const &e ){ // close mouse, rethrow
		
		m.close_mouse();
		throw e;
		
	}
	
	// close mouse
	m.close_mouse();
	
	return 0;
}



template< typename T >int open_mouse_wrapper( T &m, const bool flag_bus, const bool flag_device,
	const std::string &string_bus, const std::string &string_device ){
	
	int open_return = 0; // open_mouse() return value
	
	if( flag_bus != flag_device ){ // improper arguments
		
		throw std::string( "Missing argument, --bus and --device must be used together." );
		return 1;
		
	} else if( flag_bus && flag_device ){ // open with bus and device
		
		if( !std::regex_match( string_bus, std::regex("[0-9]+") ) ||
			!std::regex_match( string_device, std::regex("[0-9]+") ) ){
			
			throw std::string( "Wrong argument, expected number." );
			return 1;
		}
		
		open_return = m.open_mouse_bus_device( stoi(string_bus), stoi(string_device) );
		
	} else{ // open with vid and pid
		
		open_return = m.open_mouse();
		
	}
	
	// Could not open → print message
	if( open_return != 0 ){
		
		throw std::string(
			"Couldn't open mouse.\n"
			"- Check hardware and permissions (maybe you need to be root?)\n"
			"- Try with or without the --kernel-driver option\n"
			"- Try with the --model option\n"
			"- Try with the --bus and --device options\n"
			"If nothing works please report this as a bug."
		);
		
		return 1;
	}
	
	return 0;
}
