#include <msp430.h> 

/* This program demonstrates a for loop in C on the MSP430.
 */

int main(void){
// Initialize
	WDTCTL = WDTPW | WDTHOLD;	                    // Stop watchdog timer
	
	int i = 0;
	int count = 0;

// Main Loop
	while(1){                                       // Nest inside a while loop so that the program doesn't return and thus never ends
	    for(i = 0; i < 10; i++){
	        count++;
        }
	}

	return 0;
}
