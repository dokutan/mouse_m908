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

#ifndef SIMPLE_INI_PARSER
#define SIMPLE_INI_PARSER

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>

/**
 * This is a standalone .ini parser, written to replace boost property
 * tree in the mouse_m908 project. It is not intended to be a general
 * purpose replacement, however there is nothing preventing that except
 * the very limited amount of features. 
 * 
 */
class simple_ini_parser{
	
	private:
	
	std::map< std::string, std::string > _ini_values;
	
	public:
	
	/** 
	 * Read the specified .ini file. The already existing key-value
	 * pairs do not get cleared, only overwritten.
	 * \return 0 if succesful
	 */
	int read_ini( std::string path );
	
	/**
	 * Get the value of the specified key.
	 * \return The value of the specified key, or the specified default
	 * value
	 */
	std::string get( std::string key, std::string default_value );
	
	/**
	 * Print all key-value pairs to stdout.
	 */
	int print_all();
};

#endif
