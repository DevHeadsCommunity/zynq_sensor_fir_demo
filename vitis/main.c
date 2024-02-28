/*
 * Program for multi-sensor interface with MiniZed using the PL defined Pmod, GPIO and SPI IP blocks
 * Pmod NAV at Pmod 1
 */

/***************** Includes *****************/
#include <stdio.h>
#include <sleep.h>
#include <time.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "SPI.h"
#include "Filter.h"

/***************** User Peripheral Instances *****************/
extern XGpio gpio1;
extern XSpi  SpiInstance;

int main()
{
    int Status;

    init_platform();	    //Initialize the UART

	/* Initialize the GPIO driver */
	Status = XGpio_Initialize(&gpio1, XPAR_AXI_GPIO_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("GPIO Initialization Failed!\r\n");
		return XST_FAILURE;
	}

	/* Set up the AXI SPI Controller */
	Status = XSpi_Init(&SpiInstance,SPI_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		xil_printf("SPI Initialization Failed!\r\n");
		return XST_FAILURE;
	}

    while(1)
    {
		NavDemo_Initialize();
		NavDemo_Run();
	    NavDemo_Cleanup();
    }
    return 0;
}
