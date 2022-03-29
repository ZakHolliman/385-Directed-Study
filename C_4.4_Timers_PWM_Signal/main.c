#include <msp430.h>

/* This program generates a PWM signal using a timer configured to ACLK in UP mode, that counts
 * between two values and toggles an LED in between their times.
 *
 * The Timer has two CCR threshold registers that can trigger ISRs
 *      The first (TB0CCR1) is set to the value 1638.
 *      The second (TB0CCR0) is set to the value 32768.
 *
 * When the timer begins at 0, it will toggle the LED ON and begin counting in UP mode.
 *
 * When the timer reaches the first threshold (CCR1 = 1638) it will enter that Interrupt Routine, which
 *      will turn the LED OFF. It will remain off until we trigger the next ISR.
 *
 * When the timer reaches the second threshold (CCR0 = 32768) it will enter that Interrupt Routine
 *      which will turn the LED ON.
 *
 * This creates a pattern where the LED is on for a very short time and is off for an extended
 *      period of time (i.e. pulses)
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
    TB0CCR0 = 32768;                            // Set PWM period
    TB0CCR1 = 1638;                             // Set PWM duty cycle



    // Interrupts
    TB0CCTL0 |= CCIE;                           // Enable local IRQ for CCR0
    TB0CCTL1 |= CCIE;                           // Enable local IRQ for CCR1

    __enable_interrupt();                       // Enable global interrupts GIE

// Main Loop
    while(1){

    }

    return 0;
}

// ----- Interrupt Service Routines ----------------------------------- //
// ----- CCR0 -------------------------------- //
#pragma vector = TIMER0_B0_VECTOR;               // ISR for period
__interrupt void ISR_TB0_CCR0(void){
    // ISR
    P1OUT |= BIT0;                              // Set LED1 / P1.0 to ON

    // Housekeeping
    TB0CCTL0 &= ~CCIFG;                         // Clear flag
}

// ----- CCR1 -------------------------------- //
#pragma vector = TIMER0_B1_VECTOR;               // ISR for Duty Cycle
__interrupt void ISR_TB0_CCR1(void){
    // ISR
    P1OUT &= ~BIT0;                             // Set LED1 / P1.0 to OFF

    // Housekeeping
    TB0CCTL1 &= ~CCIFG;                         // Clear flag
}
