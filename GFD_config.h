/*
 * GFD_config.h
 * Gesture finger decoder configuration
 * Created: 2/28/2026
 * Author:  hamza
 *
 * GFD_FINGER_THRESHOLD: ADC value above which a finger is
 * considered "bent" (finger closed).
 *
 * ADC range: 0-1023 (10-bit, AVCC reference = 5V)
 * A value of 400 corresponds to roughly 1.95 V on the ADC pin,
 * which is a mid-bend position for a typical flex sensor.
 * Adjust this value during calibration on real hardware.
 */

#ifndef GFD_CONFIG_H_
#define GFD_CONFIG_H_

#define GFD_FINGER_THRESHOLD    400

#endif /* GFD_CONFIG_H_ */
