/*************************************************************************
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
**************************************************************************
* Description:                                                           *
* The following is a simple hello world program running MicroC/OS-II.The * 
* purpose of the design is to be a very simple application that just     *
* demonstrates MicroC/OS-II running on NIOS II.The design doesn't account*
* for issues such as checking system call return codes. etc.             *
*                                                                        *
* Requirements:                                                          *
*   -Supported Example Hardware Platforms                                *
*     Standard                                                           *
*     Full Featured                                                      *
*     Low Cost                                                           *
*   -Supported Development Boards                                        *
*     Nios II Development Board, Stratix II Edition                      *
*     Nios Development Board, Stratix Professional Edition               *
*     Nios Development Board, Stratix Edition                            *
*     Nios Development Board, Cyclone Edition                            *
*   -System Library Settings                                             *
*     RTOS Type - MicroC/OS-II                                           *
*     Periodic System Timer                                              *
*   -Know Issues                                                         *
*     If this design is run on the ISS, terminal output will take several*
*     minutes per iteration.                                             *
**************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "includes.h"
#include "system.h"
#include "sys/alt_irq.h"

// USB Module libraries
#include "basictyp.h"
#include "common.h"
#include "isr.h"
#include "usb.h"
#include "devicerequest.h"
#include "ISP1362_HAL.h"


// What are these for? Obviously one is for pio registers.. but what functions?
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    usb_task_stk[TASK_STACKSIZE];
OS_STK    gesture_task_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */
#define USB_PRIORITY		1
#define GESTURE_PRIORITY	2

/* Task for handling USB related tasks */
void usb_device_task(void* pdata)
{
	/*** Start of code taken from LED example project. ***/
	//Reset USB core and USB connections
	disable();
    disconnect_USB();
    usleep(1000000);
    Hal4D13_ResetDevice();
    bUSBCheck_Device_State.State_bits.DEVICE_DEFAULT_STATE = 1;
    bUSBCheck_Device_State.State_bits.DEVICE_ADDRESS_STATE = 0;
    bUSBCheck_Device_State.State_bits.DEVICE_CONFIGURATION_STATE = 0;
    bUSBCheck_Device_State.State_bits.RESET_BITS = 0;  
    usleep(1000000);
    reconnect_USB(); 
    CHECK_CHIP_ID();
    Hal4D13_AcquireD13(ISP1362_DC_IRQ,(void*)usb_isr);
    enable();
	
    bD13flags.bits.verbose=1;	
	/*** End of code taken from LED example project. ****/

	Hal4D13_RegAccess(); // Tests connection.
	
	
	// Each iteration checks
	while (1)
	{ 
		/* Commented out to see if I can test connection without doing any ongoing communication. Don't know if it will work this way.
		// Start of code taken from LED example project. 
		// So far code is taken verbatim, but I am going through each item so it does what I want it to do.
		if (bUSBCheck_Device_State.State_bits.RESET_BITS == 1)
		{
			disable();
			break;  
		}
		if (bD13flags.bits.suspend)
		{
			disable();
			bD13flags.bits.suspend= 0;
			enable();
			suspend_change();    
		} // Suspend Change Handler
		
		if (bD13flags.bits.DCP_state == USBFSM4DCP_SETUPPROC)
		{
			disable();
			SetupToken_Handler();
			enable();
		} // Setup Token Handler 
		
		if ((bD13flags.bits.DCP_state == USBFSM4DCP_REQUESTPROC) && !ControlData.Abort)
		{
			disable();
			bD13flags.bits.DCP_state = 0x00;
			DeviceRequest_Handler();
			enable();
		} // Device Request Handler
		
		usleep(1);
		*/
		/*** End of code taken from LED example project. ****/
		
		printf("Hello from task1\n");
		printf("This task is the USB device handler\n");
		OSTimeDlyHMSM(0, 0, 3, 0);
  }
}

/* Prints "Hello World" and sleeps for three seconds. 
*  
*  Will eventually analyze data gathered from glove to determine what gesture 
*  signals to send across USB. Passes a message to USB process that data is ready
*  to send.
*/
void gesture_task(void* pdata)
{
  while (1)
  { 
    printf("Hello from task2\n");
	printf("This task will be for gesture analysis\n");
    OSTimeDlyHMSM(0, 0, 3, 0);
  }
}
/* The main function creates two task and starts multi-tasking */
int main(void)
{
  
  OSTaskCreateExt(usb_device_task,
                  NULL,
                  (void *)&usb_task_stk[TASK_STACKSIZE-1],
                  USB_PRIORITY,
                  USB_PRIORITY,
                  usb_task_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
              
               
  OSTaskCreateExt(gesture_task,
                  NULL,
                  (void *)&gesture_task_stk[TASK_STACKSIZE-1],
                  GESTURE_PRIORITY,
                  GESTURE_PRIORITY,
                  gesture_task_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  OSStart();
  return 0;
}

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/
