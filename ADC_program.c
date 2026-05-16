/*
 * ADC_program.c
 * ADC driver implementation for ATmega32
 * Created: 2/9/2026
 * Author:  hamza
 */

#include "Bit_Math.h"
#include "STD_types.h"

#include "ADC_interface.h"
#include "ADC_register.h"


void ADC_voidInit(ADC_refVoltage_t copy_tRefVol)
{
    switch (copy_tRefVol)
    {
        case ADC_REFERENCE_AVCC:
            CLR_BIT(ADMUX_REG, REFS1);
            SET_BIT(ADMUX_REG, REFS0);
            break;

        case ADC_REFERENCE_AREF:
            CLR_BIT(ADMUX_REG, REFS1);
            CLR_BIT(ADMUX_REG, REFS0);
            break;

        case ADC_REFERENCE_INTERNAL:
            SET_BIT(ADMUX_REG, REFS1);
            SET_BIT(ADMUX_REG, REFS0);
            break;
    }

    /* Right-adjust result (ADLAR = 0) */
    CLR_BIT(ADMUX_REG, ADLAR);

    /* Enable ADC */
    SET_BIT(ADCSRA_REG, ADEN);

    /* Single conversion mode (auto-trigger off) */
    CLR_BIT(ADCSRA_REG, ADATE);

    /* Disable ADC interrupt (polling mode) */
    CLR_BIT(ADCSRA_REG, ADIE);

    /* Prescaler = 128  ->  16 MHz / 128 = 125 kHz (within 50–200 kHz range) */
    SET_BIT(ADCSRA_REG, ADPS2);
    SET_BIT(ADCSRA_REG, ADPS1);
    SET_BIT(ADCSRA_REG, ADPS0);
}


void ADC_voidGetDigitalValue(ADC_ChannelId_t copy_tChannelId, u16* pu16DigitalValue)
{
    if ((copy_tChannelId < 8) && (pu16DigitalValue != NULL))
    {
        /* Clear channel selection bits MUX4:MUX0 */
        ADMUX_REG &= 0xE0;

        /* Select the requested channel */
        ADMUX_REG |= copy_tChannelId;

        /* Start a single conversion */
        SET_BIT(ADCSRA_REG, ADSC);

        /* Busy-wait until the conversion-complete flag is set */
        while (0 == GET_BIT(ADCSRA_REG, ADIF));

        /* Clear the flag (write 1 to clear) */
        SET_BIT(ADCSRA_REG, ADIF);

        /* Read the 10-bit result */
        *pu16DigitalValue = ADC_u16_REG;
    }
}
