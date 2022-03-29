#include <msp430.h>

/* This program demonstrates creating Digital I/O input with C on the MSP430 by configuring
 *      Switch 1 (Port 4 Bit 1) to turn LED 1 (Port 1 Bit 0) on when pressed, and off when
 *      not pressed.
 */

int main(void){
// Initialize
	WDTCTL = WDTPW | WDTHOLD;	                // Stop watchdog timer

	// Enable Digital I/O
	PM5CTL0 &= ~LOCKLPM5;                       // Disable Low Power Mode
	
	// LED1 (P1.0)
	P1DIR |= BIT0;                              // Set LED1 / P1.0 to OUTPUT

	// Switch 1 (P4.1)
	P4DIR &= ~BIT1;                             // Set P4.1 / S1 to INPUT
	P4REN |= BIT1;                              // Enable up or down resistor on P4.1 / S1
	P4OUT |= BIT1;                              // Set resistor for P4.1 / S1 to be PULL UP
	P4IES |= BIT1;                              // Sensitivity for P4.1 / S1 is HIGH->LOW

	int readS1;

// Main Loop
	while(1){
	    readS1 = P4IN;                          // Read P4
	    readS1 &= BIT1;                         // Clear all bits except for BIT 1

	    if(readS1 == 0){
	        P1OUT |= BIT0;                      // When pressed, Turn LED1 ON
	    } else {
	        P1OUT &= ~BIT0;                     // When not pressed, Turn LED1 OFF
	    }
	}

	return 0;
}
