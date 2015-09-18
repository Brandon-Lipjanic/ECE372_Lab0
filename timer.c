/* 
 * File:   timer.c
 * Author: blipjanic1616
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#include "timer.h"

#define FCY 625000
#define TIME_DELAY 2

void initTimer1(){

    unsigned int prVal = (FCY*TIME_DELAY)/256.0 - 1;
    PR1 = prVal;
    TMR1 = 0;
    T1CONbits.TCS = 0;
    T1CONbits.TCKPS = 0b11; //prescalar 256
    IFS0bits.T1IF = 0; // Put the interrupt flag down
   


    //TODO: Initialize Timer 1 to have a period of
    // 2 second. Enable its interrupt
    return;
}

void initTimer2(){

    TMR2 = 0;
    T2CONbits.TCS = 0;
    T2CONbits.TCKPS = 0b111; //Prescalar of 256
    IFS0bits.T2IF = 0;  //Interupt Flag Down
   

    //TODO: Initialize Timer 2.
    return;
}

void delayMs(int delay){

    unsigned int prVal = (FCY*delay*0.001)/256.0 -1;
    PR2 = prVal;
    TMR2 = 0;
    T2CONbits.TON = 1; //Timer on
    IFS0bits.T2IF = 0; // Flag Down
    while(IFS0bits.T2IF == 0){} // While the flag is down, once flag is raised exit loop
    // Flag would be raised in hardware here.
    IFS0bits.T2IF = 0; //Flag Down
    T2CONbits.TON = 0; // Timer off


    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
    return;
}
