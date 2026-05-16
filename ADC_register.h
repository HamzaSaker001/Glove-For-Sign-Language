/*
 * ADC_register.h
 * ATmega32 ADC register addresses
 * Created: 2/9/2026
 * Author:  hamza
 */

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

/*
 * ATmega32 internal SRAM addresses (I/O address + 0x20):
 *   ADMUX  = 0x07 I/O  -> 0x27 SRAM
 *   ADCSRA = 0x06 I/O  -> 0x26 SRAM
 *   ADCH   = 0x04 I/O  -> 0x24 SRAM
 *   ADCL   = 0x05 I/O  -> 0x25 SRAM
 *
 * Reading ADC_u16_REG (at 0x24) reads ADCH:ADCL as a
 * little-endian 16-bit value which is correct for right-adjusted
 * result (ADLAR=0). ADCL must be read first; the hardware locks
 * ADCH until ADCL is read. A single 16-bit volatile read issued
 * by AVR-GCC reads the lower address first, so this is safe.
 */

#define ADMUX_REG   (*(volatile u8*)0x27)
#define REFS1       7
#define REFS0       6
#define ADLAR       5
#define MUX4        4
#define MUX3        3
#define MUX2        2
#define MUX1        1
#define MUX0        0

#define ADCSRA_REG  (*(volatile u8*)0x26)
#define ADEN        7
#define ADSC        6
#define ADATE       5
#define ADIF        4
#define ADIE        3
#define ADPS2       2
#define ADPS1       1
#define ADPS0       0

#define ADCL_REG    (*(volatile u8*)0x25)
#define ADCH_REG    (*(volatile u8*)0x24)
#define ADC_u16_REG (*(volatile u16*)0x24)   /* reads ADCL then ADCH correctly */

#define SFIOR_REG   (*(volatile u8*)0x50)
#define ADTS2       7
#define ADTS1       6
#define ADTS0       5

#endif /* ADC_REGISTER_H_ */
