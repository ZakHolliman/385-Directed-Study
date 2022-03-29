#include <msp430.h>

/* This program demonstrates the overflow functionality of timers on the MSP430 using C by blinking
 *      an LED. The timer is configured to CONTINUOUS mode using ACLK (32.768kHz) and when its
 *      Interrupt triggers, it toggles an LED (LED 1 / P1.0).
 */

int main(void){
// Initialize
    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer

    // Enable Digital I/O
    PM5CTL0 &= ~LOCKLPM5;                       // Disable Low Power Mode

// Peripherals
    // LED1 (P1.0)
    P1DIR |= BIT0;                              // Set LED1 / P1.0 to OUTPUT

    // Timer
    TB0CTL |= TBCLR;                            // Ensure that the timer starts cleared
    TB0CTL |= TBSSEL__ACLK;                     // Set clock to ACLK
    TB0CTL |= MC__CONTINUOUS;                   // Set to CONINTUOUS MODE

    // Interrupts
    TB0CTL |= TBIE;                             // Enable local IRQ for TB0 Overflow

    __enable_interrupt();                       // Enable global interrupts GIE



// Main Loop
    while(1){}

    return 0;
}

// ----- Interrupts Service Routines -------------------- //
#pragma vector = TIMER0_B1_VECTOR;
__interrupt void ISR_TB0_Overflow(void){
    // ISR
    P1OUT ^= BIT0;                              // Toggle LED1 / P1.0

    // Housekeeping
    TB0CTL &= ~TBIFG;                           // Clear IRQ flag
}
