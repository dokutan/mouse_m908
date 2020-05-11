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
	std::cout << "mouse_m908: Control the Redragon M908 Impact gaming mouse.\n";
	std::cout << "GPLv3 or later.\n\n";
	
	std::cout << "Options:\n\n";
	
	std::cout << "-h --help\n\tDisplays this message.\n";
	std::cout << "-c --config=arg\n\tLoads and applies settings from specified file.\n";
	std::cout << "-p --profile=arg\n\tSets currently active profile (1-5).\n";
	std::cout << "-m --macro=arg\n\tSelects macro file for sending.\n";
	std::cout << "-n --number=arg\n\tSelects macro slot for sending (1-15).\n";
	std::cout << "-b --bus=arg\n\tUSB bus id, requires -d.\n";
	std::cout << "-d --device=arg\n\tUSB device number, requires -b.\n";
	std::cout << "-k --kernel-driver\n\tDo not attempt to detach kernel driver.\n";
	std::cout << "-v --version\n\tPrint version.\n";
	std::cout << "-R --read=arg\n\tRead settings from the mouse and print configuration to the specified file (\"-\" = stdout).\n";
	std::cout << "-D --dump=arg\n\tRead settings from the mouse and dump the raw data to the specified file (\"-\" = stdout).\n";
	//std::cout << "-r --repeat\n\tSets number of times the macro will be repeated (1-255).\n";
}
