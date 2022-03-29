#include <msp430.h>

/* This program uses a timer configured to ACLK in count UP mode, with a threshold set at the
 * value 16384. When the timer triggers, it will trigger an Interrupt that toggles an LED.
 */

int main(void){
// Initialize
    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer

    // Enable Digital I/O
    PM5CTL0 &= ~LOCKLPM5;                       // Disable Low Power Mode

// Peripherals
    // LED1 (P1.0)
    P1DIR |= BIT0;                              // Set LED1 / P1.0 to OUTPUT

    // Timer B
    TB0CTL |= TBCLR;                            // Ensure the clock starts cleared
    TB0CTL |= TBSSEL__ACLK;                     // Set clock frequency to use ACLK
    TB0CTL |= MC__UP;                           // Set mode control of timer to UP
    TB0CCR0 = 16384;                            // Set CCR0 to 16384

    // Interrupts
    TB0CCTL0 |= CCIE;                           // Enable local IRQ for CCR0

    __enable_interrupt();                       // Enable global interrupts GIE

// Main Loop
    while(1){}

    return 0;
}

// ------Interrupt Service Routines ----------------------------------- //
#pragma vector = TIMER0_B0_VECTOR;
__interrupt void ISR_TB0_CCR0(void){
    // ISR
    P1OUT ^= BIT0;                              // Toggle LED1

    // Housekeeping
    TB0CCTL0 &= ~CCIFG;                         // Clear flag of TB0CCTL0
}
