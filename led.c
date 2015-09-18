/* 
 * File:   led.c
 * Author: blipjanic1616
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"

#define OUTPUT 0
#define INPUT 1

void initLEDs(){
    
    //Set the three LED locations as outputs.
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
    return;
}

void turnOnLED(int led){

    // LED 1 (D0) on, rest off
    if(led == 1){
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 0;
    }
    
    // LED 2 (D1) on, rest off
    else if(led == 2){
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1;
        LATDbits.LATD2 = 0;
    }
    
    //LED 3 (D2) on, rest off
    else{
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 1;
    }
    return;
}