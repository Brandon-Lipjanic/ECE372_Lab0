/* 
 * File:   main.c
0 * Author: blipjanic1616
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led1, led2, led3, debouncePress, debounceRelease, debounceRelease2
} stateType;

    volatile  stateType state = led1;
 
//TODO: Use volatile variables that change within interrupts

int main() {
    
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    int ledStateCounter = 1; // This variable is use to determine which led state to transition to next based on previous state.
    
    //Define an initial state
   
    
    
    while(1){
        //TODO: Implement a state machine to create the desired functionality
        
        switch(state){
            case led1:
                turnOnLED(1); //Turn led1 on
                ledStateCounter = 1; //set stateCounter to 1
                while(PORTDbits.RD6 == RELEASED); // Wait for press
                
                state = debouncePress; //go to debouncePress
                TMR1 = 0; //reset timer register
                
                IFS0bits.T1IF = FLAG_DOWN; //flag down
                T1CONbits.TON = 1; //timer 1 on
                break;
            
            case led2:
                turnOnLED(2); //Turn led1 on
                ledStateCounter = 2; //set stateCounter to 2
                while(PORTDbits.RD6 == RELEASED); // Wait for press
                
                state = debouncePress; // go to debouncePress
                TMR1 = 0;   //reset timer register
             
                IFS0bits.T1IF = FLAG_DOWN; //flag down
                T1CONbits.TON = 1; //timer on
                break;
                
            case led3:
                turnOnLED(3); //Turn led1 on
                ledStateCounter = 3; //set stateCOunter to 3
                while(PORTDbits.RD6 == RELEASED); // Wait for press
                
                state = debouncePress; // go to debouncePress
                TMR1 = 0; //reset timer register
             
                IFS0bits.T1IF = FLAG_DOWN; //flag down
                T1CONbits.TON = 1; //timer on
                break;
                
            case debouncePress:
                delayMs(1.0);

                while(PORTDbits.RD6 == PRESSED){} //Wait for switch to be released.

                    //If the Timer1 Flag is not raised the button has been pressed
                    //for less than two seconds so it should go to the next LED
                    //which is determined in debounceRelease by variable ledStateCounter.
                    if(IFS0bits.T1IF == FLAG_DOWN){ 
                        state = debounceRelease;
                    }
                    //If the Timer1 Flag is raised the button has been pressed
                    //for more than two seconds so it should go to the previous 
                    //LED which is determined in the debounceRelease2 state by 
                    //variable ledStateCounter
                    else{
                        state = debounceRelease2;
                    }
                
                break;
                
            case debounceRelease:
                
                delayMs(1.0);

                //If the FSM was previously in state led1 go to state led2
                if(ledStateCounter == 1){
                    state = led2;
                }
                
                //If the FSM was previously in state led2 go to state led3
                else if(ledStateCounter == 2){
                    state = led3;
                }
                
                //If the FSM was previously in state led3 go to state led1
                else {
                    state = led1;
                }                   
                break;
            
            case debounceRelease2:
                delayMs(1.0);

                //If the FSM was previously in state led1 go to state led3.
                if(ledStateCounter == 1){
                    state = led3;
                }
                
                //If the FSM was previously in state led2 go to state led1.
                else if(ledStateCounter == 2){
                    state = led1;
                }
                
                //If the FSM was previously in state led3 go to state led2.
                else {
                    state = led2;
                }
                break;
        }
    }
    
    return 0;
}
