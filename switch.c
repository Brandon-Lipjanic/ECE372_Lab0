/* 
 * File:   switch.c
 * Author: blipjanic1616
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0
#define FLAG_DOWN 0
#define FLAG_RAISED 1

void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;
    CNCONDbits.ON = 1; //Enable the switch
     
    CNPUDbits.CNPUD6 = 1; // Enable Pull Up Resistor
    IEC1bits.CNDIE = 1; //Enable CN interrupts
    IFS1bits.CNDIF = FLAG_DOWN; // Flag down
    
    return;
}