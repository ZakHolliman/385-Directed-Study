#include <msp430.h>

/* This program runs a timer set to ACLK which overflows at a 12-bit rate, and toggles an LED
 * using an Interrupt Service Routine.
 */

int main(void){
// Initialize
    WDTCTL = WDTPW | WDTHOLD;	                // Stop watchdog timer
	
	// Enable Digital I/O
	PM5CTL0 &= ~LOCKLPM5;                       // Disable Low Power Mode

	// LED1 (P1.0)
	P1DIR |= BIT0;                              // Set LED1 / P1.0 to OUTPUT

	// Timer B
	TB0CTL |= TBCLR;                            // Reset Timer
	TB0CTL |= TBSSEL__ACLK;                     // Set clock frequency to use ACLK
	TB0CTL |= MC__CONTINUOUS;                   // Set mode control of timer to CONTINUOUS
	TB0CTL |= CNTL_1;                           // Set timer to 12-bit overflow

	// Interrupts
	TB0CTL |= TBIE;                             // Enable local timer IRQ

	__enable_interrupt();                       // Enable global interrupts GIE

// Main Loop
	while(1){}

	return 0;
}

// ------Interrupt Service Routines ----------------------------------- //
#pragma vector = TIMER0_B1_VECTOR;
__interrupt void ISR_TIMER_OVERFLOW(void){
    // ISR
    P1OUT ^= BIT0;                              // Toggle LED1

    // Housekeeping
    TB0CTL &= ~TBIFG;                           // Clear flag
}
