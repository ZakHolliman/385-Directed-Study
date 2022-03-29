#include <msp430.h>

/*  This program demonstrates a switch statement in C on the MSP430.
 */

int main(void){
// Initialize
    WDTCTL = WDTPW | WDTHOLD;	                    // Stop watchdog timer
	
	int number = 2;
	int count = 0;

	while(1){
	    switch(number){
	    case 1:
	        count = 1;
	        break;

	    case 2:
	        count = 2;
	        break;

	    default:
	        break;
	    }
	}

	return 0;
}
