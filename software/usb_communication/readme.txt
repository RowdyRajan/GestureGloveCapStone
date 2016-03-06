Software for group 2 capstone project DE2 board

Files in directory

basic_io.h 
-- Defines some macros for GPIO, 7 SEG Display and Time Delay

basic_typ.h 
-- Defines some aliases for basic types (eg. CHAR)

D13Bus.h 
-- Not sure exaclty, something to do with the D13 Bus. There are not many functions here but they seem fundamental (read/write to buffer, single transmit, burst transmit etc.)

common.h
-- A few bit level macros. IRQ macros. Structs and definitions for a few things. Also fairly fundamental like device_request struct and _IO_REQUEST. _D13FLAGS <- seems important

debug.h
-- A bunch of flags for debug testing are	 included here. This could be quite useful for checking if each part along the way is working. 


HAL4D13.h  
!!!-- One of the major files. Defines most of the values and functions used for the main interactions with the USB controller. 
	The USB.h file in the app notes from 2014 has most of 		this file (if not all) copied into it. However their 		file also includes some additional things like a 		struct called usb_device.
	Either they created it or it will be within another 		file in the example project.
The functions within this file deal mostly with configuration of various things including Endpoints, Interrupt registers, DMA etc. Also included are connect, setup, write/read endpoint.
--All methods begin with prefix "HAL4D13_"

hello_world_0.c
-- This file had the main function in the LED_DEVICE example project and it will likely be invaluable in learning how to implement USB communication in our own project. I changed the name of the main function so (hopefully) eclipse won't get confused.

iso.h
-- Very small file with three definitions and some iso (I assume isochronous communication related). Has a delay and read/write ISO endpoint funcitons.

isp1361_hal.h
-- The comments of this file seemed very promising, mentioning using A0 and A1 to select which controller (DC and HC) and which phase the communication will be for. Several macros are defined for read/write operations though its not clear how the address bits (A0 and A1) relate.
-- I would like to know where the constants USB_DC_BASE and USB_HC_BASE are defined.

isp1362_includes.h
-- This file just includes a all the local files and some basic c libraries. It actually seems like a bit of a frakenstien of small updates over the years. There are clearly old file names commented out etc.

isr.h
-- just some ISR control functions. Might be important for breaking out of interrupt control blocks.

LCD.h
-- Very basic LCD screen commands. Init, show_text, test_lcd. (might not need to include this file) [I will anyway for now]

mainloop.h
-- This file is a big deal. It has handler functions for a variety of requests received from the host. Notably it can handle device and vendor id requests.
-- Find out where the externs come from, especially ControlData and RaiseIRQL() function.
	> ControlData
	> RaiseIRQL
	
chap_9.h
-- Another major file. All methods contained begin with "chap9_"

usb.h
-- All the different 'discriptor' structs are defined here, along with a lot of constants starting with "USB_"

usb_irq.h
-- Just enable and disable irq functions. Most of what actualy happens is functions that must be within "system.h" or "sys/alt_irq.h"


-- Look into "system.h" and "sys/alt_irq.h" and any other similar local files referenced. Just see what is available in sys/ for instance.
-- I cannot find where any of the major extern variables or even their types are defined. Could be in the actuall hello_world file.
	> D13FLAGS
	> USBCHECK_DEVICE_STATES
	> CONTROL_XFER





