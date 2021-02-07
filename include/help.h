/*
 * This program is free software you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

//help message
const std::string mouse_m908_help = 
R"(mouse_m908: Control various Redragon gaming mice.
GPLv3 or later.

Options:

-h --help
	Displays this message.
-c --config=arg
	Loads and applies settings from specified file.
-p --profile=arg
	Sets currently active profile (1-5).
-m --macro=arg
	Selects macro file for sending.
-n --number=arg
	Selects macro slot for sending (1-15).
-b --bus=arg
	USB bus id, requires -d.
-d --device=arg
	USB device number, requires -b.
-k --kernel-driver
	Do not attempt to detach kernel driver.
-v --version
	Print version.
-R --read=arg
	Read settings from the mouse and print configuration to the specified file ('-' = stdout).
-D --dump=arg
	Read settings from the mouse and dump the raw data to the specified file ('-' = stdout).
-M --model=arg
	Specifies the mouse model (? for a list of valid models).

Examples:

Send the configuration from example.ini
	mouse_m908 -c example.ini
Send the macro from example.macro to slot 1
	mouse_m908 -m example.macro -n 1
Send all macros from example.ini
	mouse_m908 -m example.ini
Read and print the current config in .ini format
	mouse_m908 -R -
)";