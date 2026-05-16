/*
 * FLEX_interface.h
 * Flexible sensor driver public API
 * Created: 2/28/2026
 * Author:  hamza
 *
 * FIX: FLEX_Resistance output pointer changed from u16* to u32*.
 *
 * Root cause of the original bug:
 *   The resistance formula  R = (1023 * R_fixed / adcValue) - R_fixed
 *   with R_fixed = 10000 Ω can produce values up to ~100 000 Ω when
 *   the sensor is barely bent (low ADC reading).  A u16 can only hold
 *   values up to 65 535, so the result was silently truncated and the
 *   wrong resistance was returned to the caller.
 *   Using u32 (max ~4.29 billion) covers the full realistic range.
 */

#ifndef FLEX_INTERFACE_H_
#define FLEX_INTERFACE_H_

#include "STD_types.h"

void FLEX_Init      (void);
void FLEX_Read      (u8 sensorID, u16* pu16ADCValue);
void FLEX_Resistance(u8 sensorID, u32* pu32Resistance);   /* FIX: was u16* */

#endif /* FLEX_INTERFACE_H_ */
