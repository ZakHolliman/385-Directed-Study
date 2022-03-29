#include <msp430.h>

/* This program demonstrates interrupts on the MSP430 in C using Switch 1 (Port 4 Bit 1) to toggle
 *      an LED (LED 1 / Port 1 Bit 0) when pressed.
 */


int main(void){
// Initialize
	WDTCTL = WDTPW | WDTHOLD;	                // Stop watchdog timer
	
	// Enable Digital I/O
	PM5CTL0 &= ~LOCKLPM5;                       // Disable Low Power Mode

	// Peripherals
	    // LED1 (P1.0)
	P1DIR |= BIT0;                              // Set LED1 / P1.0 to OUTPUT

	    // Switch 1 (P4.1)
	P4DIR &= ~BIT1;                             // Set P4.1 / S1 to INPUT
	P4REN |= BIT1;                              // Enable up or down resistor on P4.1 / S1
	P4OUT |= BIT1;                              // Set resistor for P4.1 / S1 to be PULL UP
	P4IES |= BIT1;                              // Sensitivity for P4.1 / S1 is HIGH->LOW

	// Interrupts
	    // Local
	P4IE |= BIT1;                               // Enable P4.1 / S1 IRQ

	__enable_interrupt();                       // Enable Global Interrupts GIE

	// Main Loop
	while(1){}

	return 0;
}

// ------Interrupt Service Routines ----------------------------------- //
#pragma vector = PORT4_VECTOR;                  // Says that the next routine right beneath this is going to be an ISR
__interrupt void ISR_Port4_S1(void){            // Defines this as an ISR
    // ISR
    P1OUT ^= BIT0;                              // Toggle LED1 / P1.0

    // Housekeeping
    P4IFG &= ~BIT1;                             // Clear P4.1 / S1 Flag
}
