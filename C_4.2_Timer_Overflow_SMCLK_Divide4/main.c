#include <msp430.h>

/* This program runs a timer configured to SMCLK (1MHz) divided down by 4 to be 250kHz, and toggles
 * an LED with an Interrupt every time the timer overflows.
 */

int main(void){
// Initialize
    WDTCTL = WDTPW | WDTHOLD;                       // Stop watchdog timer

    // Enable Digital I/O
    PM5CTL0 &= ~LOCKLPM5;                           // Disable Low Power Mode

// Peripherals
    // LED1 (P1.0)
    P1DIR |= BIT0;                                  // Set LED1 / P1.0 to OUTPUT

    // Timer B
    TB0CTL |= TBCLR;                                // Ensure the clock starts CLEARED
    TB0CTL |= TBSSEL__SMCLK;                        // Set clock frequency to use SMCLK (1MHz)
    TB0CTL |= MC__CONTINUOUS;                       // Set mode control of timer to CONTINUOUS
    TB0CTL |= ID__4;                                // Set ID to DIVIDE by 4



// Interrupts
    TB0CTL |= TBIE;                                 // Enable local timer IRQ

    __enable_interrupt();                           // Enable global interrupts GIE

// Main Loop
    while(1){}

    return 0;
}

// ------Interrupt Service Routines ----------------------------------- //
#pragma vector = TIMER0_B1_VECTOR;
__interrupt void ISR_TIMER_OVERFLOW(void){
    // ISR
    P1OUT ^= BIT0;                                  // Toggle LED1

    // Housekeeping
    TB0CTL &= ~TBIFG;                               // Clear flag
}
