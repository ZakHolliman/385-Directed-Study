#include <msp430.h>

/* This program demonstrates a while loop in C on the MSP430.
 */

int main(void){
// Initialize
	WDTCTL = WDTPW | WDTHOLD;	                    // Stop watchdog timer
	
	int count = 0;

// Main Loop
	while(1){
	    count = count + 1;
	}

	return 0;
}
