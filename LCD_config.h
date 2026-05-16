/*
 * LCD_config.h
 * LCD hardware pin configuration for ATmega32
 *
 * FIX: LCD 4-bit data pins (D4-D7) have been moved to PORTC
 *      in LCD_private.h to avoid conflict with ADC inputs on
 *      PORTA (PA0-PA4 are used by the 5 flex sensors).
 *
 * Wiring summary (4-bit mode):
 *   RS  -> PB1
 *   E   -> PB2
 *   D4  -> PC0
 *   D5  -> PC1
 *   D6  -> PC2
 *   D7  -> PC3
 *   RW  -> GND (always write)
 *   VSS -> GND
 *   VDD -> 5V
 *   VEE -> pot wiper (contrast)
 *   A   -> 5V via 220 Ω (backlight)
 *   K   -> GND
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* RS pin */
#define LCD_RS_PORT   DIO_PORTB
#define LCD_RS_PIN    DIO_PIN1

/* Enable pin */
#define LCD_E_PORT    DIO_PORTB
#define LCD_E_PIN     DIO_PIN2

/*
 * LCD_DATA_PORT is only used in 8-bit mode.
 * In 4-bit mode the individual pin definitions in
 * LCD_private.h are used instead.
 */
#define LCD_DATA_PORT  DIO_PORTA   /* 8-bit mode only – not used in this project */

#endif /* LCD_CONFIG_H_ */
