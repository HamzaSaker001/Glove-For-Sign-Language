/*
 * LCD_private.h
 * LCD internal configuration (not exposed to application layer)
 *
 * FIX: Data pins D4-D7 moved from PORTA to PORTC.
 *
 * Root cause of the original bug:
 *   PORTA pins PA0-PA4 are the ADC input channels used by the
 *   5 flex sensors (ADC_CHANNEL_0 .. ADC_CHANNEL_4).
 *   The original code placed LCD D4 on PA4, which is the same
 *   pin as ADC channel 4 (sensor 5).  Driving PA4 as a digital
 *   output for the LCD corrupts the ADC reading for that finger.
 *
 * Solution:
 *   Keep flex sensors on PA0-PA4 (ADC inputs, PORTA DDR = input).
 *   Move LCD 4-bit data bus to PC0-PC3 (PORTC is otherwise unused).
 *   RS and E remain on PB1 and PB2 — no conflict there.
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

static void PRV_voidEnableTriggerWrite(void);

/* LCD mode selection */
#define LCD_8_BIT_MODE  1
#define LCD_4_BIT_MODE  2

#define LCD_MODE   LCD_4_BIT_MODE   /* project uses 4-bit mode */

/*
 * 4-bit data pins — PORTC (PC0-PC3)
 *
 * FIX was: DIO_PORTA / DIO_PIN4..7  (conflicted with ADC)
 * Now:     DIO_PORTC / DIO_PIN0..3  (free pins, no conflict)
 */
#define LCD_D4_PORT   DIO_PORTC
#define LCD_D4_PIN    DIO_PIN0

#define LCD_D5_PORT   DIO_PORTC
#define LCD_D5_PIN    DIO_PIN1

#define LCD_D6_PORT   DIO_PORTC
#define LCD_D6_PIN    DIO_PIN2

#define LCD_D7_PORT   DIO_PORTC
#define LCD_D7_PIN    DIO_PIN3

#endif /* LCD_PRIVATE_H_ */
