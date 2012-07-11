/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <htc.h>           /* HiTech General Includes */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void) {
    /* TODO Add clock switching code if appropriate.  */

    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */

    // Configure internal clock to 8MHz
    OSCCON = 0b01100000; // IRCFx = 110

    OSCTUNE = 0b10000000; // x4 PLL disabled
    // Use HFINTOSC as clock source, 31.25kHz
    // 16MHz / 512 = 31.25kHz

    // Wait for clock to become stable
    while (!OSCCONbits.IOFS);

    return;
}
