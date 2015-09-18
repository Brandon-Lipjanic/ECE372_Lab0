/* 
 * File:   switch.c
 * Author: blipjanic1616
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0

void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;
    CNCONDbits.ON = 1;
     
    CNPUDbits.CNPUD6 = 1; // Enable Pull Up Resistor
    IEC1bits.CNDIE = 1; //Enable CN interrupts
    IFS1bits.CNDIF = 0; // Flag down
    
    return;
}