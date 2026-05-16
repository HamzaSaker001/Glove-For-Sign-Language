/*
 * DIO_interface.h
 * DIO driver public API for ATmega32
 * Created: 11/3/2025
 * Author:  hamza
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "STD_types.h"
#include "Bit_Math.h"

/* Pin direction */
#define DIO_PIN_INPUT    0
#define DIO_PIN_OUTPUT   1

/* Port direction */
#define DIO_PORT_INPUT   0x00
#define DIO_PORT_OUTPUT  0xFF

/* Port IDs */
#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

/* Pin IDs */
#define DIO_PIN0    0
#define DIO_PIN1    1
#define DIO_PIN2    2
#define DIO_PIN3    3
#define DIO_PIN4    4
#define DIO_PIN5    5
#define DIO_PIN6    6
#define DIO_PIN7    7

/* Pin state */
#define DIO_PIN_LOW     0
#define DIO_PIN_HIGH    1

/************************************** APIs Prototypes **************************************/

/* PIN APIs */
void DIO_voidSetPinDirection  (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection);
void DIO_voidSetPinValue      (u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue);
void DIO_voidTogglePinValue   (u8 copy_u8PortId, u8 copy_u8PinId);
void DIO_voidGetPinValue      (u8 copy_u8PortId, u8 copy_u8PinId, u8* pu8PinValue);
void DIO_voidActivePinInternalPUR(u8 copy_u8PortId, u8 copy_u8PinId);

/* PORT APIs */
void DIO_voidSetPortDirection (u8 copy_u8PortId, u8 copy_u8PortDirection);
void DIO_voidSetPortValue     (u8 copy_u8PortId, u8 copy_u8PortValue);
void DIO_voidTogglePortValue  (u8 copy_u8PortId);                        /* FIX: was missing implementation */
void DIO_voidGetPortValue     (u8 copy_u8PortId, u8* pu8PortValue);      /* FIX: was missing implementation */
void DIO_voidActivePortInternalPUR(u8 copy_u8PortId);

#endif /* DIO_INTERFACE_H_ */
