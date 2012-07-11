/*
 ==============================================================================
 Name        : debouncer.h
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

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_

#ifdef __cplusplus
extern "C" {
#endif

    /* ************************************************************************* */
    /*!
     \defgroup debouncer

     \brief These APIs are used to interface with the input debouncer module
     */
    /* ************************************************************************* */

    /*
     * Debounce States
     *
     * There are 4 possible debounce states
     */
    typedef enum _debouncer_state_t {
        debouncer_inactive,
        debouncer_going_active, // unknown value
        debouncer_active,
        debouncer_going_inactive // unknown value

    } debouncer_state_t;

    /*
     * Debouncer object structure
     */
    typedef struct _debouncer_t {
        /*
         * Debounce count
         */
        uint_fast8_t max_cnt;

        /*
         * Current transition (bounce) count for continuous samples
         * of the same value.
         */
        uint_fast8_t cnt;

        /*
         * Current and previous debounce FSM state.
         */
        debouncer_state_t previous_state;
        debouncer_state_t current_state;

    } debouncer_t, *p_debouncer_t;

    /* ************************************************************************** */
    /*!
     \ingroup debouncer

     \brief Initialize a debouncer object.

     Initialize a debouncer object with the number of stable samples required
     to transition from active to inactive states.

     \param[in] p_debouncer - A pointer to a structure of type debouncer_t.
     \param[in] max_cnt - The number of samples to debounce.

     \return Nothing.

     */
    /* ************************************************************************** */

    void debouncer_init(p_debouncer_t p_debouncer, uint8_t max_cnt);

    /* ************************************************************************** */
    /*!
     \ingroup debouncer

     \brief Process input to be debounced.

     Called once for each input sample, given the input value.

     \param[in] p_debouncer - A pointer to a structure of type debouncer_t.
     \param[in] value - The current value of the input.

     \return bool - true if pressed, false if not pressed.

     */
    /* ************************************************************************** */

    bool debouncer_process(p_debouncer_t p_debouncer, bool value);

    /* ************************************************************************** */
    /*!
     \ingroup debouncer_changed

     \brief Determines if debouncer state changed since last call.

     Called to determine debouncer state change.

     \param[in] p_debouncer - A pointer to a structure of type debouncer_t.
 
     \return true if changed, otherwise false.

     */
    /* ************************************************************************** */

#define debouncer_changed(p) (p)->current_state != (p)->previous_state

    /* ************************************************************************** */
    /*!
     \ingroup debouncer_pressed

     \brief Determines if debouncer state has been pressed.

     Called to determine if input pressed.

     \param[in] p_debouncer - A pointer to a structure of type debouncer_t.

     \return true if pressed, otherwise false.

     */
    /* ************************************************************************** */

#define debouncer_pressed(p) \
    (((p)->current_state == debouncer_active) && \
                ((p)->previous_state == debouncer_going_active))

    /* ************************************************************************** */
    /*!
     \ingroup debouncer_released

     \brief Determines if debouncer state has been released.

     Called to determine if input released.

     \param[in] p_debouncer - A pointer to a structure of type debouncer_t.

     \return true if released, otherwise false.

     */
    /* ************************************************************************** */

#define debouncer_released(p) \
    (((p)->current_state == debouncer_inactive) && \
                ((p)->previous_state == debouncer_going_inactive))


    /* ************************************************************************** */
    /*!
     \ingroup debouncer_reset

     \brief Reset the debouncer state machine.

     Called to reset internal statemachine.

     \param[in] p_debouncer - A pointer to a structure of type debouncer_t.

     \return Nothing.

     */
    /* ************************************************************************** */

    void debouncer_reset(p_debouncer_t p_debouncer);

#ifdef __cplusplus
}
#endif

#endif /* DEBOUNCER_H_ */

