#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "socal/socal.h"
#include "socal/hps.h"
#include "socal/alt_gpio.h"
#include "hps_0.h"
#include "led.h"
#include "seg7.h"
#include <stdbool.h>
#include <pthread.h>

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

volatile unsigned long *h2p_lw_led_addr=NULL;
volatile unsigned long *h2p_lw_hex_addr=NULL;

int main(int argc, char **argv)
{
	int ret;
	void *virtual_base;
	int fd;
	// map the address space for the LED registers into user space so we can interact with them.
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}
	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );	
	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return(1);
	}
	h2p_lw_led_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + LED_PIO_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	h2p_lw_hex_addr=virtual_base + ( ( unsigned long  )( ALT_LWFPGASLVS_OFST + SEG7_IF_BASE ) & ( unsigned long)( HW_REGS_MASK ) );
	if(argv[1] == NULL)
	{
		SEG7_Unique(0);
	}
	else if(atoi(argv[1])>=10)
	{		
		SEG7_Unique(9);
	}
	else
	{
		SEG7_Unique(atoi(argv[1]));
	}

	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );

	}
	close( fd );
	return 0;
}