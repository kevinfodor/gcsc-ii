/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void) {
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */


    // Init I/O
    TRISD = 0b00000000; // PORTD bits 7:0 are all outputs (0)

    INTCON2bits.RBPU = 0; // enable PORTB internal pullups
    WPUBbits.WPUB0 = 1; // enable pull up on RB0
    ANSELH = 0x00; // AN8-12 are digital inputs (AN12 on RB0)

    TRISBbits.TRISB0 = 1; // PORTB bit 0 (connected to switch)
    // is input (1)

    // Init Timer
    INTCONbits.TMR0IF = 0; // clear roll-over interrupt flag
    T0CON = 0b01000111; // 8-bit, 1:256 prescale - increments every
    // instruction clock * 256
    TMR0H = 0; // clear timer - always write upper
    // byte first
    TMR0L = 0;
    T0CONbits.TMR0ON = 1; // start timer

    return;
}
