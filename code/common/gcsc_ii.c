/*
 ==============================================================================
 Name        : gcsc_ii.c
 Date        : Jul 03, 2012
 ==============================================================================

 BSD License
 -----------

 Copyright (c) 2012, and Kevin Fodor, All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 - Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 - Neither the name of Kevin Fodor nor the names of
 its contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.

 NOTICE:
 SOME OF THIS CODE MAY HAVE ELEMENTS TAKEN FROM OTHER CODE WITHOUT ATTRIBUTION.
 IF THIS IS THE CASE IT WAS DUE TO OVERSIGHT WHILE DEBUGGING AND I APOLOGIZE.
 IF ANYONE HAS ANY REASON TO BELIEVE THAT ANY OF THIS CODE VIOLATES OTHER
 LICENSES PLEASE CONTACT ME WITH DETAILS SO THAT I MAY CORRECT THE SITUATION.

 ==============================================================================
 */

// Compiler specific includes

#ifdef HI_TECH_C
// HiTEC-C Compiler include
#include <htc.h>
#endif

// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// chip specific include
#include "user.h"

// Project include
#include "debouncer.h"
#include "gcsc_ii.h"

/*
 * Controller States
 */
typedef enum _controller_state_t {
    controller_disabled,
    controller_short,
    controller_long,

} controller_state_t;

// Declare Globals

static controller_state_t state = controller_disabled;
static uint8_t output = ALL_OFF; // buffer for output signals

static debouncer_t trigger;
static uint16_t active_cnt;
static uint8_t lamp_cnt;
static uint8_t lpress_cnt;
static bool pressed;

// Prototypes
static void toggle(void);

/*
 * Implementation
 */

/*! \brief toggle
 */
static void toggle(void) {

    // Toggle lamps and bell as needed
    if (EXPIRED == lamp_cnt) {
        // Toggle LAMPs and signal BELL
        output = (((output ^ (LAMP1 | LAMP2)) | BELL) & PORT_MASK);

        // Reset lamp timer
        lamp_cnt = LAMP_TIMEOUT_COUNT;
    } else {
        // decrement lamp timeout
        lamp_cnt--;

        // Clear BELL
        output &= ~BELL;
    }
    return;
}

/*! \brief gcsc_ii
 */
void gcsc_ii(void) {

    // Initialize debouncer for the TRIGGER
    debouncer_init(&trigger, DEBOUNCE_TIMEOUT_COUNT);

    do {
        // Set LAMP1, LAMP2 and BELL output (turns off heartbeat)
        PORT = output;

        // Wait for timeout (~10 msec)
        while (0 == TIMER_EXPIRED);
        TIMER_RESET;

        // Turn on HEARTBEAT
        PORT |= HEARTBEAT;

        // Run debouncer on TRIGGER input and determine
        // current pressed state. Note, pressed state
        // if a one-shot indication.
        pressed = debouncer_process(&trigger, TRIGGER);

        /* Controller State Machine
         */
        switch (state) {
            case controller_disabled: // idle

                output = ALL_OFF;

                if (pressed) {
                    // Turn on LAMP1 and BELL
                    output = (LAMP1 | BELL);

                    // Load lamp timeout
                    lamp_cnt = LAMP_TIMEOUT_COUNT;

                    // Load active timeout
                    active_cnt = ACTIVE_TIMEOUT_COUNT;

                    // Load long-press timeout
                    lpress_cnt = LONG_PRESS_TIMEOUT_COUNT;

                    // go into 'long-press' non-timed mode
                    state = controller_long;
                }

                break;

            case controller_short:

                // Check if active timer is running
                if (EXPIRED != active_cnt) {
                    active_cnt--;

                    // Is button still held down?
                    if (debouncer_active == trigger.current_state) {
                        // Is button long pressed?
                        if (EXPIRED == lpress_cnt) {
                            // go into 'long-press' forever mode
                            state = controller_long;
                        } else {
                            lpress_cnt--;
                        }
                    }
                } else {
                    // cancel signal
                    state = controller_disabled;
                }

                // Fall thru...

            case controller_long:

                // Check if cancelled
                if (pressed) {
                    // cancel signal
                    state = controller_disabled;
                }

                toggle();

                break;

            default:
                state = controller_disabled;
                break;
        }

    } while (true);

    return;
}
