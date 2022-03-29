#include <msp430.h>

/* This program demonstrates the Capture ability of timers on the MSP430 using C. It uses a timer
 *      configured to ACLK in CONTINUOUS mode, divided down by 8. When we press a button (Switch 1)
 *      it will enter an Interrupt Routine that grabs the current value of the timer in the Capture
 *      Control Register, and store it in a variable named "captured", allowing us to view the stored
 *      value.
 */

int captured = 0;                               // This variable will hold the captured value from the timer

int main(void){
// Initialize
    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer

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

    // Timer B
    TB0CTL |= TBCLR;                            // Ensure the clock starts cleared
    TB0CTL |= TBSSEL__ACLK;                     // Set clock frequency to use ACLK
    TB0CTL |= MC__CONTINUOUS;                   // Set mode control of timer to CONTINUOUS
    TB0CTL |= ID__8;                            // Set ID to divide by 8

    // Set up capture
    TB0CCTL0 |= CAP;                             // Put CCR0 into CAPTURE mode
    TB0CCTL0 |= CM__BOTH;                       // Put sensitivity to BOTH edges
    TB0CCTL0 |= CCIS__GND;                      // Put input level at GND



// Interrupts
    P4IE |= BIT1;                               // Enable local IRQ for P4.1 / S1

    __enable_interrupt();                       // Enable global interrupts GIE

// Main Loop
    while(1){}

    return 0;
}

// ------Interrupt Service Routines ----------------------------------- //
#pragma vector = PORT4_VECTOR;
__interrupt void ISR_PORT4_S1(void){
    // ISR
    P1OUT ^= BIT0;                              // Toggle LED 1 / P1.0
    TB0CCTL0 ^= CCIS0;                          // Switch back and forth between GND and VCC
    captured = TB0CCR0;                         // Store captured value

    // Housekeeping
    P4IFG &= ~BIT1;                             // Clear flag
}
