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

#include <iostream>

//prints a help message
void print_help(){
	std::cout << "Options:\n";
	std::cout << "-h --help\n\tDisplays this message.\n";
	std::cout << "-c --config\n\tLoads and applies settings from specified file.\n";
	std::cout << "-p --profile\n\tSets currently active profile (1-5).\n";
	std::cout << "-m --macro\n\tSelects macro file for sending.\n";
	std::cout << "-n --number\n\tSelects macro slot for sending (1-15).\n";
}
