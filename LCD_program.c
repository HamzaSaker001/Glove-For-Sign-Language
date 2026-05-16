/*
 * LCD_program.c
 * LCD driver implementation for ATmega32
 * Created: 2/5/2026
 * Author:  hamza
 *
 * No logic changes needed here.
 * The pin conflict fix is entirely in LCD_private.h (D4-D7 -> PORTC).
 * This file reads those macros at compile time, so it automatically
 * uses the corrected PORTC pins without any source changes.
 */

#define F_CPU 16000000UL
#include <util/delay.h>

#include "Bit_Math.h"
#include "STD_types.h"

#include "DIO_interface.h"

#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"


/* ------------------------------------------------------------------ */
/*  Private helper                                                      */
/* ------------------------------------------------------------------ */

static void PRV_voidEnableTriggerWrite(void)
{
    DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
}


/* ------------------------------------------------------------------ */
/*  Initialisation                                                      */
/* ------------------------------------------------------------------ */

void LCD_voidINIT(void)
{
    /* Control pins always output */
    DIO_voidSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_E_PORT,  LCD_E_PIN,  DIO_PIN_OUTPUT);

#if LCD_MODE == LCD_8_BIT_MODE

    DIO_voidSetPortDirection(LCD_DATA_PORT, DIO_PORT_OUTPUT);
    _delay_ms(40);

    LCD_voidSendCommand(0b00111000);   /* Function set: 8-bit, 2 lines, 5×7 */
    _delay_us(45);

#elif LCD_MODE == LCD_4_BIT_MODE

    /* Set D4-D7 (now on PORTC PC0-PC3) as outputs */
    DIO_voidSetPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);
    _delay_ms(40);

    /* Send 0010 nibble to switch LCD into 4-bit mode */
    DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, 0);
    DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, 1);
    DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, 0);
    DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, 0);
    PRV_voidEnableTriggerWrite();

    LCD_voidSendCommand(0b00101000);   /* Function set: 4-bit, 2 lines, 5×7 */
    _delay_us(45);

#endif

    LCD_voidSendCommand(0b00001111);   /* Display ON, cursor ON, blink ON */
    _delay_us(45);

    LCD_voidSendCommand(0b00000001);   /* Clear display */
    _delay_ms(2);

    LCD_voidSendCommand(0b00000110);   /* Entry mode: increment, no shift */
}


/* ------------------------------------------------------------------ */
/*  Send a single character to the LCD                                  */
/* ------------------------------------------------------------------ */

void LCD_voidDisplayChar(u8 copy_u8Data)
{
    DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);  /* RS = 1 (data) */

#if LCD_MODE == LCD_8_BIT_MODE

    DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Data);
    PRV_voidEnableTriggerWrite();

#elif LCD_MODE == LCD_4_BIT_MODE

    /* Upper nibble first */
    DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Data, 4));
    DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Data, 5));
    DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Data, 6));
    DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Data, 7));
    PRV_voidEnableTriggerWrite();

    /* Lower nibble */
    DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Data, 0));
    DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Data, 1));
    DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Data, 2));
    DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Data, 3));
    PRV_voidEnableTriggerWrite();

#endif
}


/* ------------------------------------------------------------------ */
/*  Send a command byte to the LCD                                      */
/* ------------------------------------------------------------------ */

void LCD_voidSendCommand(u8 copy_u8cmnd)
{
    DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);   /* RS = 0 (command) */

#if LCD_MODE == LCD_8_BIT_MODE

    DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8cmnd);
    PRV_voidEnableTriggerWrite();

#elif LCD_MODE == LCD_4_BIT_MODE

    /* Upper nibble first */
    DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8cmnd, 4));
    DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8cmnd, 5));
    DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8cmnd, 6));
    DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8cmnd, 7));
    PRV_voidEnableTriggerWrite();

    /* Lower nibble */
    DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8cmnd, 0));
    DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8cmnd, 1));
    DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8cmnd, 2));
    DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8cmnd, 3));
    PRV_voidEnableTriggerWrite();

#endif
}


/* ------------------------------------------------------------------ */
/*  Higher-level LCD functions                                          */
/* ------------------------------------------------------------------ */

void LCD_voidDisplayString(u8* pu8String)
{
    u8 Local_u8Counter = 0;
    while (pu8String[Local_u8Counter] != '\0')
    {
        LCD_voidDisplayChar(pu8String[Local_u8Counter]);
        Local_u8Counter++;
    }
}


void LCD_voidClear(void)
{
    LCD_voidSendCommand(0b00000001);
    _delay_ms(2);
}


void LCD_voidShift(u8 copy_u8ShiftingDirection)
{
    switch (copy_u8ShiftingDirection)
    {
        case LCD_SHIFT_LEFT:
            LCD_voidSendCommand(0b00011000);
            _delay_us(45);
            break;
        case LCD_SHIFT_RIGHT:
            LCD_voidSendCommand(0b00011100);
            _delay_us(45);
            break;
    }
}


void LCD_voidgoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position)
{
    switch (copy_u8LineNumber)
    {
        case LCD_LINE_1:
            LCD_voidSendCommand(0b10000000 + copy_u8Position);
            _delay_us(45);
            break;
        case LCD_LINE_2:
            LCD_voidSendCommand(0b11000000 + copy_u8Position);
            _delay_us(45);
            break;
    }
}


void LCD_voidGoToStartPosition(void)
{
    LCD_voidSendCommand(0b00000010);
    _delay_ms(2);
}
