#include <msp430.h> 

/* This program demonstrates creating an output on the MSP430 in C by configuring LED1 (Port 1 Bit 0)
 *      to blink on and off
 */

int main(void){
// Initialize
	WDTCTL = WDTPW | WDTHOLD;	                    // Stop watchdog timer
	
	// Enable Digital I/O
	PM5CTL0 &= ~LOCKLPM5;                           // Disable Low Power Mode
    // Remember that for using &| we need the ~ to make the mask of LOCKLPM5 look like 0b11110111 instead of 0b00001000

	// Setup LED1 (P1.0)
	P1DIR |= BIT0;                                  // Set LED1 / P1.0 to OUTPUT

// Main Loop
	while(1){
	    P1OUT ^= BIT0;                              // Toggle LED1

	    int i = 0;

	    for(i = 0; i < 0xFFFF; i++){}               // Have some delay between toggles
	}

	return 0;
}
