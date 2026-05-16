/*
 * LCD_interface.h
 * LCD driver public API for ATmega32
 * Created: 2/5/2026
 * Author:  hamza
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "STD_types.h"

/* Shift directions */
#define LCD_SHIFT_LEFT   1
#define LCD_SHIFT_RIGHT  2

/* Line numbers */
#define LCD_LINE_1   1
#define LCD_LINE_2   2

/************************************** APIs Prototypes **************************************/

void LCD_voidINIT               (void);
void LCD_voidDisplayChar        (u8  copy_u8Data);
void LCD_voidSendCommand        (u8  copy_u8cmnd);
void LCD_voidDisplayString      (u8* pu8String);
void LCD_voidClear              (void);
void LCD_voidShift              (u8  copy_u8ShiftingDirection);
void LCD_voidgoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position);
void LCD_voidGoToStartPosition  (void);

#endif /* LCD_INTERFACE_H_ */
