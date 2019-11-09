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

//helper functions

//init libusb and open mouse
int mouse_m908::open_mouse(){
	
	//vars
	int res = 0;
	
	//libusb init
	res = libusb_init( NULL );
	if( res < 0 ){
		return res;
	}
	
	//open device
	_handle = libusb_open_device_with_vid_pid( NULL, _mouse_vid, 
	_mouse_pid );
	if( !_handle ){
		return 1;
	}
	
	//detach kernel driver on interface 0 if active 
	if( libusb_kernel_driver_active( _handle, 0 ) ){
		res += libusb_detach_kernel_driver( _handle, 0 );
		if( res == 0 ){
			_detached_driver_0 = true;
		} else{
			return res;
		}
	}
	
	//detach kernel driver on interface 1 if active 
	if( libusb_kernel_driver_active( _handle, 1 ) ){
		res += libusb_detach_kernel_driver( _handle, 1 );
		if( res == 0 ){
			_detached_driver_1 = true;
		} else{
			return res;
		}
	}
	
	//detach kernel driver on interface 2 if active 
	if( libusb_kernel_driver_active( _handle, 2 ) ){
		res += libusb_detach_kernel_driver( _handle, 2 );
		if( res == 0 ){
			_detached_driver_2 = true;
		} else{
			return res;
		}
	}
	
	//claim interface 0
	res += libusb_claim_interface( _handle, 0 );
	if( res != 0 ){
		return res;
	}
	
	//claim interface 1
	res += libusb_claim_interface( _handle, 1 );
	if( res != 0 ){
		return res;
	}
	
	//claim interface 2
	res += libusb_claim_interface( _handle, 2 );
	if( res != 0 ){
		return res;
	}
	
	return res;
}

//close mouse
int mouse_m908::close_mouse(){
	
	//release interfaces 0, 1 and 2
	libusb_release_interface( _handle, 0 );
	libusb_release_interface( _handle, 1 );
	libusb_release_interface( _handle, 2 );
	
	//attach kernel driver for interface 0
	if( _detached_driver_0 ){
		libusb_attach_kernel_driver( _handle, 0 );
	}
	
	//attach kernel driver for interface 1
	if( _detached_driver_1 ){
		libusb_attach_kernel_driver( _handle, 1 );
	}
	
	
	//attach kernel driver for interface 2
	if( _detached_driver_2 ){
		libusb_attach_kernel_driver( _handle, 2);
	}
	
	//exit libusb
	libusb_exit( NULL );
	
	return 0;
}
