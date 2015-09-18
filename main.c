/* 
 * File:   main.c
0 * Author: gvanhoy
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
    
    //This function is necessary to use interrupts. 
   // enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    int ledStateCounter = 1; // This variable is use to determine which led state to transition to next based on prev state.
    
    //Define an initial state
   
    
    
    while(1){
        //TODO: Implement a state machine to create the desired functionality
        
        switch(state){
            case led1:
                turnOnLED(1); //Turn led1 on
                ledStateCounter = 1; //determine next state
                while(PORTDbits.RD6 ==1); // do nothing
                
                state = debouncePress; //go to debouncePress
                TMR1 = 0;
                IFS0bits.T1IF = 0; //flag down
                T1CONbits.TON = 1; //timer 1 on
                break;
            
            case led2:
                turnOnLED(2); //Turn led1 on
                ledStateCounter = 2;
                while(PORTDbits.RD6 ==1); // do nothing
                
                state = debouncePress; // go to debouncePress
                TMR1 = 0;
             
                IFS0bits.T1IF = 0; //flag down
                T1CONbits.TON = 1; //timer on
                break;
                
            case led3:
                turnOnLED(3); //Turn led1 on
                ledStateCounter = 3; //set state counter
                while(PORTDbits.RD6 ==1); // do nothing
                
                state = debouncePress; // go to debouncePress
                TMR1 = 0; //reset timer register
             
                IFS0bits.T1IF = 0; //flag down
                T1CONbits.TON = 1; //timer on
                break;
                
            case debouncePress:
                delayMs(1);

                while(PORTDbits.RD6 == 0){}

                    if(IFS0bits.T1IF == 0){
                        state = debounceRelease;
                    }
                    else{
                        state = debounceRelease2;
                    }
                
                break;
                
            case debounceRelease:
                
                delayMs(1);

                if(ledStateCounter == 1){
                    state = led2;
                }
                else if(ledStateCounter == 2){
                    state = led3;
                }
                else {
                    state = led1;
                }                   
                break;
            
            case debounceRelease2:
                delayMs(1);

                if(ledStateCounter == 1){
                    state = led3;
                }
                else if(ledStateCounter == 2){
                    state = led1;
                }
                else {
                    state = led2;
                }
                break;
        }
    }
    
    return 0;
}
