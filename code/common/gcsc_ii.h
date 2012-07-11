/*
 ==============================================================================
 Name        : gcsc_ii.h
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

#ifndef GCSC_II_H_
#define GCSC_II_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* ************************************************************************* */
/*!
 \defgroup gcsc_ii

 \brief These APIs and definitions are for the main controller.
 */
/* ************************************************************************* */

// Timebase
#define TMR0_TIMEOUT_USEC (10000) // 10.000 msec

// Common time definitions
#define USEC_PER_SEC (1000000)
#define MSEC_PER_USEC (1000)

// Timeout definitions
#define EXPIRED (0)
#define DEBOUNCE_TIMEOUT_USEC        (200000) // 200 msec = 0.2 sec
#define LAMP_TIMEOUT_USEC            (700000) // 700 msec = 0.7 sec
#define ACTIVE_TIMEOUT_USEC        (30000000) // 30 sec
#define LONG_PRESS_TIMEOUT_USEC     (1500000) // 1.5 sec

// Timeout counter definitions
#define DEBOUNCE_TIMEOUT_COUNT (DEBOUNCE_TIMEOUT_USEC / USEC_PER_TICK)
#define LONG_PRESS_TIMEOUT_COUNT ( \
    (LONG_PRESS_TIMEOUT_USEC / USEC_PER_TICK) \
            - DEBOUNCE_TIMEOUT_COUNT)
#define ACTIVE_TIMEOUT_COUNT (ACTIVE_TIMEOUT_USEC / USEC_PER_TICK)
#define LAMP_TIMEOUT_COUNT (LAMP_TIMEOUT_USEC / USEC_PER_TICK)

// Output mask defintions
#define PORT_MASK (LAMP1 | LAMP2 | BELL)
#define ALL_OFF (~PORT_MASK & PORT_MASK)

/* ************************************************************************** */
/*!
 \ingroup gcsc_ii

 \brief Main loop.

 Runs the controller.

 \param[in] None.

 \return Nothing.

 */
/* ************************************************************************** */

void gcsc_ii( void );

#ifdef __cplusplus
}
#endif

#endif /* GCSC_II_H_ */
