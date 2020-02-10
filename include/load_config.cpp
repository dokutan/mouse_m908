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

// read and parse ini file
int simple_ini_parser::read_ini( std::string path ){
	
	// open file
	std::ifstream inifile;
	inifile.open( path );
	
	if( !inifile.is_open() )
		return 1;
	
	// go through each line
	std::string line, current_section = "";
	
	while( std::getline( inifile, line ) ){
		
		// empty line ?
		if( line.length() == 0 )
			continue;
		
		// comment ?
		if( line[0] == ';' || line[0] == '#' )
			continue;
		
		// remove whitespace
		line = std::regex_replace( line, std::regex("[[:space:]]"), "" );
		
		// section header?
		if( std::regex_match( line, std::regex("\\[[[:print:]]+\\]") ) ){
			current_section = std::regex_replace( line, std::regex("[\\[\\]]"), "" ) + ".";
			continue;
		}
		
		// key=value ?
		if( std::regex_match( line, std::regex("[[:print:]]+=[[:print:]]+") ) ){
			_ini_values.emplace( current_section + std::regex_replace( line, std::regex("=[[:print:]]+"), "" ),
				std::regex_replace( line, std::regex("[[:print:]]+="), "" ) );
		}
		
	}
	
	// close file
	inifile.close();
	
	return 0;
}

// get values
std::string simple_ini_parser::get( std::string key, std::string default_value ){
	
	// check if key exists
	if( _ini_values.find( key ) != _ini_values.end() ){
		return _ini_values.at( key );
	} else{
		return default_value;
	}
	
}

// print all key-value pairs
int simple_ini_parser::print_all(){
	
	for( auto i : _ini_values ){
		std::cout << i.first << "=" << i.second << "\n";
	}
	
	return 0;
}
