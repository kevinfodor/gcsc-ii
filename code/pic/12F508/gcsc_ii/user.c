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

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */
    TRIS = 0b00001000;
           //----1---   GP3 inputs
           //--00-000   GP0,1,2,4,5 outputs

    /* Initialize peripherals */
    OPTION = 0b11010111;
             //1------- Wake-up on pinchange disabled. (GPWU=1)
             //-1------ Weak pullups disabled. (GPPU=1)
             //--0----- T0CS, use internal instruction cycle clock Fosc/4
             //---1---- T0SE, don't care.
             //----0--- Prescaler assigned to TMR0 (PSA=0)
             //-----111 Prescaler 1:256 (PS=111) 256 usec

    return;
}

