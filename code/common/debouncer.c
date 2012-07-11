/*
 ==============================================================================
 Name        : debouncer.c
 Date        : Jul 2, 2012
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

// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Other includes

// Module include
#include "debouncer.h"

// Local declarations

// Implementation

void debouncer_init(p_debouncer_t p_debouncer, uint8_t max_cnt) {
    /*
     * Initialize debouncer structure counters and initial value
     * as provided by the caller.
     */
    p_debouncer->max_cnt = max_cnt;
    debouncer_reset(p_debouncer);

    return;
}

bool debouncer_process(p_debouncer_t p_debouncer, bool value) {
    bool pressed;
    // Process input value through the debouncer FSM
    p_debouncer->previous_state = p_debouncer->current_state;
    switch (p_debouncer->current_state) {
        case debouncer_inactive:
            if (value) {
                // Re-load sample counter
                p_debouncer->cnt = p_debouncer->max_cnt;
                p_debouncer->current_state = debouncer_going_active;
            }
            break;

        case debouncer_going_active:
            if (value) {
                if (0 == p_debouncer->cnt) {
                    // Input is now stable
                    p_debouncer->current_state = debouncer_active;
                }
            } else {
                // Input is not stable
                p_debouncer->current_state = debouncer_going_inactive;
            }
            break;

        case debouncer_active:
            if (!value) {
                // Re-load sample counter
                p_debouncer->cnt = p_debouncer->max_cnt;
                p_debouncer->current_state = debouncer_going_inactive;
            }
            break;

        case debouncer_going_inactive:
            if (!value) {
                if (0 == p_debouncer->cnt) {
                    // Input is now stable
                    p_debouncer->current_state = debouncer_inactive;
                }
            } else {
                // Input is not stable
                p_debouncer->current_state = debouncer_going_active;
            }
            break;

        default:
            // Reset
            p_debouncer->cnt = 0;
            p_debouncer->current_state = debouncer_going_inactive;
            break;
    }

    // Decrement sample counter if needed
    if (p_debouncer->cnt > 0) {
        p_debouncer->cnt--;
    }

    pressed = debouncer_pressed(p_debouncer);

    return pressed;
}

void debouncer_reset(p_debouncer_t p_debouncer) {
    p_debouncer->cnt = 0;
    p_debouncer->previous_state =
            p_debouncer->current_state = debouncer_going_inactive;
    return;
}
