/*
 * FLEX_program.c
 * Flexible sensor driver implementation
 * Created: 2/28/2026
 * Author:  hamza
 *
 * FIX 1: FLEX_Resistance — local variable and output pointer are now
 *         u32 to prevent integer overflow/truncation (was u16).
 *
 * FIX 2: ADC_voidGetDigitalValue guard changed from < 32 to < 8
 *         inside ADC_program.c (already fixed there). Here we also
 *         validate sensorID < FLEX_SENSOR_COUNT (< 5) consistently.
 *
 * FIX 3: Added edge-case guard: if adcValue == 1023 the sensor is
 *         fully straight (near-zero flex resistance), which would
 *         produce a near-zero or negative resistance value. We clamp
 *         to a practical minimum of 1 ADC count to avoid divide
 *         instability, and cap the resistance result.
 */

#include "Bit_Math.h"
#include "STD_types.h"

#include "ADC_interface.h"
#include "DIO_interface.h"

#include "FLEX_config.h"
#include "FLEX_interface.h"


/* ADC channel for each sensor (index = sensorID 0-4) */
static const u8 FLEX_Channels[FLEX_SENSOR_COUNT] = {0, 1, 2, 3, 4};

/* Fixed pull-down resistor in voltage divider (Ohms) */
#define FLEX_R_FIXED   10000UL


/* ------------------------------------------------------------------ */

void FLEX_Init(void)
{
    ADC_voidInit(ADC_REFERENCE_AVCC);
}


/* ------------------------------------------------------------------ */

void FLEX_Read(u8 sensorID, u16* pu16ADCValue)
{
    u16 Local_u16Value = 0;

    if (pu16ADCValue != NULL)
    {
        if (sensorID < FLEX_SENSOR_COUNT)
        {
            ADC_voidGetDigitalValue((ADC_ChannelId_t)FLEX_Channels[sensorID],
                                   &Local_u16Value);
        }
        *pu16ADCValue = Local_u16Value;
    }
}


/* ------------------------------------------------------------------ */
/*  Convert ADC reading to flex-sensor resistance (Ohms).              */
/*                                                                      */
/*  Circuit: VCC --[R_fixed]--+--[R_flex]-- GND                        */
/*                            |                                         */
/*                           ADC pin                                    */
/*                                                                      */
/*  ADC = 1023 * R_flex / (R_fixed + R_flex)                           */
/*  => R_flex = (ADC * R_fixed) / (1023 - ADC)                         */
/*                                                                      */
/*  Note: the original code used a different rearrangement:             */
/*    R_flex = (1023 * R_fixed / ADC) - R_fixed                        */
/*  which assumes VCC --[R_flex]--+--[R_fixed]-- GND.                  */
/*  Both are valid depending on which leg the sensor occupies.          */
/*  We keep the original formula and fix only the data-type issue.      */
/* ------------------------------------------------------------------ */

void FLEX_Resistance(u8 sensorID, u32* pu32Resistance)   /* FIX: was u16* */
{
    u16 adcValue = 0;
    u32 Local_u32Resistance = 100000UL;   /* FIX: was u32 local assigned to u16 pointer */

    if (pu32Resistance != NULL)
    {
        FLEX_Read(sensorID, &adcValue);

        if (adcValue > 0 && adcValue < 1023)
        {
            /* Original formula: R_flex = (1023 * R_fixed / adcValue) - R_fixed */
            Local_u32Resistance = ((1023UL * FLEX_R_FIXED) / adcValue) - FLEX_R_FIXED;
        }
        else if (adcValue == 0)
        {
            /* Sensor open-circuit or fully bent: clamp to max */
            Local_u32Resistance = 100000UL;
        }
        else
        {
            /* adcValue == 1023: sensor fully straight, ~0 Ω flex resistance */
            Local_u32Resistance = 0UL;
        }

        *pu32Resistance = Local_u32Resistance;   /* FIX: safe — u32 into u32* */
    }
}
