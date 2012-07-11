/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

#if _12F508 == 1

// Definitions for outputs (lamps, bell)
#define LAMP1       (0b00010000) // GP4
#define LAMP2       (0b00100000) // GP5
#define BELL        (0b00000100) // GP2
#define HEARTBEAT   (0b00000010) // GP1
#define PORT  (GPIO)

// Definitions for inputs
#define TRIGGER (GPIObits.GP3 ? 0 : 1)

// Definitions for clock timer and delay
#define FOSC (4000000)
#define TMR0_PRS (256) // Prescaler 1:256
#define TMR0_CLOCK_TICK_USEC ((TMR0_PRS * USEC_PER_SEC) / (FOSC / 4)) // 256 usec
#define TMR0_COUNT (TMR0_TIMEOUT_USEC / TMR0_CLOCK_TICK_USEC) // 39
#define USEC_PER_TICK (TMR0_COUNT * TMR0_CLOCK_TICK_USEC) // 9984

#define TIMER_EXPIRED (TMR0 == TMR0_COUNT)
#define TIMER_RESET (TMR0 = 0)

#elif _12F1840

// Definitions for outputs (lamps, bell)
#define LAMP1       (0b00010000) // RA4
#define LAMP2       (0b00100000) // RA5
#define BELL        (0b00000100) // RA2
#define HEARTBEAT   (0b00000100) // RA1
#define PORT  (PORTA)

// Definitions for inputs
#define TRIGGER (PORTAbits.RA3 ? 0 : 1)

// Definitions for clock timer and delay
#define FOSC (4000000)
#define TMR0_PRS (256) // Prescaler 1:256
#define TMR0_CLOCK_TICK_USEC ((TMR0_PRS * USEC_PER_SEC) / (FOSC / 4)) // 256 usec
#define TMR0_COUNT (TMR0_TIMEOUT_USEC / TMR0_CLOCK_TICK_USEC) // 39
#define USEC_PER_TICK (TMR0_COUNT * TMR0_CLOCK_TICK_USEC) // 9984

#define TIMER_EXPIRED (TMR0 == TMR0_COUNT)
#define TIMER_RESET (TMR0 = 0)

#else

#error Sorry! Incorrect header used for target chip.

#endif

void InitApp(void);         /* I/O and Peripheral Initialization */
