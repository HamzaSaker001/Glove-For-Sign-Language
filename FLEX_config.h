/*
 * FLEX_config.h
 * Flexible sensor hardware configuration
 * Created: 2/28/2026
 * Author:  hamza
 *
 * All 5 sensors are read through the ADC on PORTA (PA0-PA4).
 * PORTA pins are configured as ADC inputs by the ADC driver —
 * do NOT set them as digital outputs elsewhere.
 */

#ifndef FLEX_CONFIG_H_
#define FLEX_CONFIG_H_

/* Number of flexible sensors (one per finger) */
#define FLEX_SENSOR_COUNT   5

/*
 * Sensor-to-ADC-channel mapping.
 * Sensor 1 = thumb  -> ADC channel 0 (PA0)
 * Sensor 2 = index  -> ADC channel 1 (PA1)
 * Sensor 3 = middle -> ADC channel 2 (PA2)
 * Sensor 4 = ring   -> ADC channel 3 (PA3)
 * Sensor 5 = pinky  -> ADC channel 4 (PA4)
 */
#define FLEX_SENSOR_1_PORT  0
#define FLEX_SENSOR_1_PIN   0

#define FLEX_SENSOR_2_PORT  0
#define FLEX_SENSOR_2_PIN   1

#define FLEX_SENSOR_3_PORT  0
#define FLEX_SENSOR_3_PIN   2

#define FLEX_SENSOR_4_PORT  0
#define FLEX_SENSOR_4_PIN   3

#define FLEX_SENSOR_5_PORT  0
#define FLEX_SENSOR_5_PIN   4

#endif /* FLEX_CONFIG_H_ */
