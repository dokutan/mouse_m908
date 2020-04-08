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


/*
 * This is a standalone .ini parser, written to replace boost property
 * tree in the mouse_m908 project. It is not intended to be a general
 * purpose replacement.
 * 
 */

#ifndef SIMPLE_INI_PARSER
#define SIMPLE_INI_PARSER

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>

class simple_ini_parser{
	
	private:
	
	std::map< std::string, std::string > _ini_values;
	
	public:
	
	// read and parse ini file
	int read_ini( std::string path );
	
	// get values
	std::string get( std::string key, std::string default_value );
	
	// print all key-value pairs
	int print_all();
};

#endif
