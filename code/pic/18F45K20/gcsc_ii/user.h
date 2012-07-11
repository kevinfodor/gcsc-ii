/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

#if _18F45K20 == 1

// Definitions for outputs (lamps, bell)
#define LAMP1       (0b00000001) // RD0
#define LAMP2       (0b00000010) // RD1
#define BELL        (0b00000100) // RD2
#define HEARTBEAT   (0b00001000) // RD3
#define PORT (LATD)

// Definitions for inputs
#define TRIGGER (PORTBbits.RB0 ? 0 : 1)

// Definitions for clock timer and delay
#define FOSC (31250)
#define TMR0_CLOCK_TICK_USEC ((4 * USEC_PER_SEC) / FOSC) // 128 usec
#define TMR0_COUNT (256 - (TMR0_TIMEOUT_USEC / TMR0_CLOCK_TICK_USEC)) // 178
#define USEC_PER_TICK ((256 - TMR0_COUNT) * TMR0_CLOCK_TICK_USEC) // 9984

#define TIMER_EXPIRED (INTCONbits.TMR0IF)
#define TIMER_RESET (TMR0L = TMR0_COUNT);INTCONbits.TMR0IF = 0

#else

#error Sorry! Incorrect header used for target chip.

#endif

void InitApp(void);         /* I/O and Peripheral Initialization */
