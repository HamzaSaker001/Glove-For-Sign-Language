/*
 * GFD_program.c
 * Gesture finger decoder implementation
 * Created: 2/28/2026
 * Author:  hamza
 *
 * FIX 1: Explicit (u8) cast added when building Local_u8CurrentGesture
 *         to silence potential implicit-conversion warnings on some
 *         AVR-GCC versions.
 *
 * FIX 2: Added a short _delay_ms(5) after LCD_voidClear() to give the
 *         LCD controller time to finish the clear operation before the
 *         next string is written.  Without this, on some LCD modules the
 *         first character of the new string is lost.
 *
 * Gesture bit mapping (bit 0 = thumb, bit 4 = pinky):
 *   Bit 0 -> Sensor 0 -> PA0 -> thumb
 *   Bit 1 -> Sensor 1 -> PA1 -> index finger
 *   Bit 2 -> Sensor 2 -> PA2 -> middle finger
 *   Bit 3 -> Sensor 3 -> PA3 -> ring finger
 *   Bit 4 -> Sensor 4 -> PA4 -> pinky finger
 *
 * A bit is SET (1) when the corresponding finger is BENT
 * (ADC reading > GFD_FINGER_THRESHOLD = 400).
 *
 * Word list (satisfies >= 15 word requirement):
 *   0b00000 = 0x00  -> Open Hand
 *   0b11111 = 0x1F  -> Closed Fist
 *   0b00001 = 0x01  -> Thumb
 *   0b00010 = 0x02  -> Index
 *   0b00100 = 0x04  -> Middle
 *   0b01100 = 0x0C  -> Peace
 *   0b10001 = 0x11  -> Rock
 *   0b00111 = 0x07  -> I Love You
 *   0b10101 = 0x15  -> Hello
 *   0b01010 = 0x0A  -> Thank You
 *   0b11000 = 0x18  -> Yes
 *   0b00011 = 0x03  -> No
 *   0b11110 = 0x1E  -> Wait
 *   0b01111 = 0x0F  -> Please
 *   0b10110 = 0x16  -> Friend
 *   default         -> Unknown Sign
 */

#define F_CPU 16000000UL
#include <util/delay.h>

#include "Bit_Math.h"
#include "STD_types.h"

#include "DIO_interface.h"

#include "FLEX_interface.h"
#include "LCD_interface.h"

#include "GFD_config.h"
#include "GFD_interface.h"


/* Track the last gesture to avoid unnecessary LCD updates */
static u8 GFD_u8LastGesture = 0xFF;   /* 0xFF = invalid/uninitialised */


/* ------------------------------------------------------------------ */

void GFD_voidInit(void)
{
    FLEX_Init();
    LCD_voidINIT();
}


/* ------------------------------------------------------------------ */

void GFD_voidUpdate(void)
{
    u8  Local_u8CurrentGesture = 0;
    u16 Local_u16AdcValue      = 0;
    u8  i;

    /* Read all 5 fingers and build a 5-bit gesture byte */
    for (i = 0; i < 5; i++)
    {
        Local_u16AdcValue = 0;
        FLEX_Read(i, &Local_u16AdcValue);

        if (Local_u16AdcValue > GFD_FINGER_THRESHOLD)
        {
            /* FIX: explicit cast to u8 to suppress conversion warnings */
            SET_BIT(Local_u8CurrentGesture, (u8)i);
        }
    }

    /* Only update the LCD when the gesture changes */
    if (Local_u8CurrentGesture != GFD_u8LastGesture)
    {
        LCD_voidClear();
        _delay_ms(5);   /* FIX: wait for LCD clear to complete */

        switch (Local_u8CurrentGesture)
        {
            /* --- 15 defined words ---------------------------------- */
            case 0x00: LCD_voidDisplayString((u8*)"Open Hand");    break;  /* 0b00000 */
            case 0x1F: LCD_voidDisplayString((u8*)"Closed Fist");  break;  /* 0b11111 */
            case 0x01: LCD_voidDisplayString((u8*)"Thumb");        break;  /* 0b00001 */
            case 0x02: LCD_voidDisplayString((u8*)"Index");        break;  /* 0b00010 */
            case 0x04: LCD_voidDisplayString((u8*)"Middle");       break;  /* 0b00100 */
            case 0x0C: LCD_voidDisplayString((u8*)"Peace");        break;  /* 0b01100 */
            case 0x11: LCD_voidDisplayString((u8*)"Rock");         break;  /* 0b10001 */
            case 0x07: LCD_voidDisplayString((u8*)"I Love You");   break;  /* 0b00111 */
            case 0x15: LCD_voidDisplayString((u8*)"Hello");        break;  /* 0b10101 */
            case 0x0A: LCD_voidDisplayString((u8*)"Thank You");    break;  /* 0b01010 */
            case 0x18: LCD_voidDisplayString((u8*)"Yes");          break;  /* 0b11000 */
            case 0x03: LCD_voidDisplayString((u8*)"No");           break;  /* 0b00011 */
            case 0x1E: LCD_voidDisplayString((u8*)"Wait");         break;  /* 0b11110 */
            case 0x0F: LCD_voidDisplayString((u8*)"Please");       break;  /* 0b01111 */
            case 0x16: LCD_voidDisplayString((u8*)"Friend");       break;  /* 0b10110 */
            /* ------------------------------------------------------- */
            default:   LCD_voidDisplayString((u8*)"Unknown Sign"); break;
        }

        GFD_u8LastGesture = Local_u8CurrentGesture;
    }
}
