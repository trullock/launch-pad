/*
  SinglePadDIY.ino 
  
  1. Receives commands from control device over rfSerial link. The serial RX is sampled, if the
    data received matches the preamble, the Command counter is incremented. Then the second 
    serial RX is received, if it matches a command then action is taken.
    Important note: the Launch command ':L' will not function without first receiving a continuity
    command as well as being received prior to the hardware timeout limit, and the continuity button is 
    not being pressed. 
    Once the ':L' is executed the relay is closed. The relay will stay closed as long as it continues
    to receive ':L' commands. 
    The relay will open when:
    a. a ':R' command is received,
    b. a ':C' command is received,
    c. the hardware timeout occurs ( such as inturrption of the serial signal )
    d. the continuity button is pressed
    
    - Commands are two bytes, if not in order input is ignored and serial sequence is restarted
    a. -':C' Continuity command returns '1' or '0' depending on value of analog continuity input
       -sets timer0 to WAITTIME 
       -opens relay
       -sets RelayUnlock to 1 
    b. -':L' Launch command if timer0 not expired and RelayUnlock set then close relay
    c. -':R' Reset command opens relay
       -clears timer0
       -clears PadEnable
  2. Locally checks continuity with Push Button
      - reports continutiy status on local LED output.
  3. Hardware Timer interrupt disables outputs if no control commands are received after WAITTIME
      - when timer0 expires 
        - opens relay
        - clears PadEnable
  */
#include <TimerOne.h>
#include "comm-channel.h"


// Defines Continuity limit and Hardware timeout
#define CLIM 709    // Continutiy Analog threshold
#define WAITIME 100 // 1 sec (100 x 10ms) delay before reset

// Hardware pin definitions
const int RELAY = 4;  // relay output
const int LED = 5;    // led output
const int COUT = 6;   // continuity voltage source
const int CONT = 7;   // continuity button input
int Analog0 = A0;     // Analog input

CommChannel comms;

// Analog Continuity value
volatile int Cin = 0;                   // continuity value read

// RelayUnlock
volatile unsigned char  RelayUnlock = 0;  // enable for relay
// timer registers
volatile unsigned char timer0    = 0;   // timer0 
// command variable
volatile unsigned char command = 0;     // command read
/***********************************************************************/
/*                                                                     */
/* Setup function                                                      */
/*   initialize hardware and software variables                        */
/*   this routine is only executed once after startup                  */
/***********************************************************************/
void setup() {

	// Hardware I/O 
	pinMode(RELAY, OUTPUT);
	pinMode(LED, OUTPUT);
	pinMode(COUT, OUTPUT); 
	pinMode(CONT, INPUT);

	// Hardware Timer1 
	Timer1.initialize(10000); // Timer1 interrupt every 10ms
	Timer1.attachInterrupt( timerIsr ); // attach service routine

	// Initalize outputs
	digitalWrite(RELAY, 0);  // Turn off Relay
	digitalWrite(LED, 0);    // Turn off LED
	digitalWrite(COUT, 0);   // Turn off continuity source

	// Initalize variables
	RelayUnlock = 0;
	timer0 = 0;
}


/************************************************************************/
/*                                                                      */
/* Interrupt function                                                   */
/*   decrement timer and handle continutiy button and hardware timeout  */
/************************************************************************/
void hwIsr()
{   
    // place holder for hardware Interrupts
}

void timerIsr(){               // hardware timer interrupt routine 
  // timer0  (software variable for timing)
  if( timer0 != 0 ) timer0--;  // if timer0 is not zero, then decrement
  // if Continuity Pressed
  if( digitalRead(CONT) == 0){ // if Continuity Pressed
    timer0 = 0;                // clear timer
    digitalWrite(RELAY, 0);    // open relay
    digitalWrite(COUT, 1);     // enable continuity source
    Cin = analogRead( Analog0 ); // read continuity
    if( Cin <= CLIM ){         // Cin should be lower than CLIM
      digitalWrite(LED ,1);    // if good then set LED ON
    }else{
      digitalWrite(LED ,0);    // else if bad then set LED OFF
    }
  }else{                       // if Continutiy NOT pressed
    if( timer0 == 0 ){         // if timer0 is done then
      RelayUnlock = 0;         // lock relay enable
      digitalWrite(LED ,0);    // turn off LED
      digitalWrite(RELAY, 0);  // open relay
      digitalWrite(COUT, 0);   // turn off continuity source
    }
  }
}
/*************************************************************************/
/*                                                                       */
/* Main function                                                         */
/*      read serial commands and execute                                 */
/*************************************************************************/
void loop() {
	command = comms.read(); // then read in command
	switch (command)
	{
		// Continutiy Command received
		case 'C':
			digitalWrite(RELAY, 0);	// Force Relay Open
			digitalWrite(COUT, 1);	 // Enable continuity source
			Cin = analogRead(Analog0); // read continuity
			if (Cin < CLIM)
			{					  // Cin should be lower than CLIM
				comms.write('1'); // if good then send '1' to controller
			}
			else
			{
				comms.write('0'); // send '0' for bad cont. to controller
			}
			RelayUnlock = 1;	   // regardless of continuity Unlock relay
			timer0 = WAITIME;	  // set timer0 to WAITIME
			digitalWrite(COUT, 0); // disable continutiy source
			if (digitalRead(CONT) == 1)
			{						  // if continutiy released
				digitalWrite(LED, 0); // turn off LED
			}
			break; // go to next loop
		// Launch Command received
		case 'L':
			if ((digitalRead(CONT) == 1) && (timer0 != 0))
			{						   // if continutiy button not pressed
				digitalWrite(COUT, 0); // and timer not expired, disable continutiy source
				if (RelayUnlock == 1)
					digitalWrite(RELAY, 1); // then if relay is unlocked enable relay
				timer0 = WAITIME;			// reset timer0 to WAITIME
			}
			break; // go to next loop
		// Reset Command received
		case 'R':
			digitalWrite(RELAY, 1); // open relay
			RelayUnlock = 0;		// lock relay enable
			timer0 = 0;				// clear timer0
			break;					// go to next loop
		//
		default:   //All other commands are ignored
			break; // go to next loop
	}
}

