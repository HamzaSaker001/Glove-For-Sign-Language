/*
 * DIO_program.c
 * DIO driver implementation for ATmega32
 * Created: 11/3/2025
 * Author:  hamza
 *
 * FIX: Added missing implementations for:
 *   - DIO_voidTogglePortValue
 *   - DIO_voidGetPortValue
 *   - DIO_voidActivePortInternalPUR
 */

#include "STD_types.h"
#include "Bit_Math.h"
#include "DIO_interface.h"
#include "DIO_register.h"


/* ------------------------------------------------------------------ */
/*  PIN APIs                                                            */
/* ------------------------------------------------------------------ */

void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection)
{
    switch (copy_u8PinDirection)
    {
        case DIO_PIN_INPUT:
            switch (copy_u8PortId)
            {
                case DIO_PORTA: CLR_BIT(DDRA_REG, copy_u8PinId); break;
                case DIO_PORTB: CLR_BIT(DDRB_REG, copy_u8PinId); break;
                case DIO_PORTC: CLR_BIT(DDRC_REG, copy_u8PinId); break;
                case DIO_PORTD: CLR_BIT(DDRD_REG, copy_u8PinId); break;
            }
            break;

        case DIO_PIN_OUTPUT:
            switch (copy_u8PortId)
            {
                case DIO_PORTA: SET_BIT(DDRA_REG, copy_u8PinId); break;
                case DIO_PORTB: SET_BIT(DDRB_REG, copy_u8PinId); break;
                case DIO_PORTC: SET_BIT(DDRC_REG, copy_u8PinId); break;
                case DIO_PORTD: SET_BIT(DDRD_REG, copy_u8PinId); break;
            }
            break;
    }
}


void DIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue)
{
    switch (copy_u8PinValue)
    {
        case DIO_PIN_LOW:
            switch (copy_u8PortId)
            {
                case DIO_PORTA: CLR_BIT(PORTA_REG, copy_u8PinId); break;
                case DIO_PORTB: CLR_BIT(PORTB_REG, copy_u8PinId); break;
                case DIO_PORTC: CLR_BIT(PORTC_REG, copy_u8PinId); break;
                case DIO_PORTD: CLR_BIT(PORTD_REG, copy_u8PinId); break;
            }
            break;

        case DIO_PIN_HIGH:
            switch (copy_u8PortId)
            {
                case DIO_PORTA: SET_BIT(PORTA_REG, copy_u8PinId); break;
                case DIO_PORTB: SET_BIT(PORTB_REG, copy_u8PinId); break;
                case DIO_PORTC: SET_BIT(PORTC_REG, copy_u8PinId); break;
                case DIO_PORTD: SET_BIT(PORTD_REG, copy_u8PinId); break;
            }
            break;
    }
}


void DIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId)
{
    switch (copy_u8PortId)
    {
        case DIO_PORTA: TOG_BIT(PORTA_REG, copy_u8PinId); break;
        case DIO_PORTB: TOG_BIT(PORTB_REG, copy_u8PinId); break;
        case DIO_PORTC: TOG_BIT(PORTC_REG, copy_u8PinId); break;
        case DIO_PORTD: TOG_BIT(PORTD_REG, copy_u8PinId); break;
    }
}


void DIO_voidGetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8* pu8PinValue)
{
    if ((copy_u8PortId <= 3) && (copy_u8PinId <= 7) && (pu8PinValue != NULL))
    {
        switch (copy_u8PortId)
        {
            case DIO_PORTA: *pu8PinValue = GET_BIT(PINA_REG, copy_u8PinId); break;
            case DIO_PORTB: *pu8PinValue = GET_BIT(PINB_REG, copy_u8PinId); break;
            case DIO_PORTC: *pu8PinValue = GET_BIT(PINC_REG, copy_u8PinId); break;
            case DIO_PORTD: *pu8PinValue = GET_BIT(PIND_REG, copy_u8PinId); break;
        }
    }
}


void DIO_voidActivePinInternalPUR(u8 copy_u8PortId, u8 copy_u8PinId)
{
    if ((copy_u8PortId <= 3) && (copy_u8PinId <= 7))
    {
        switch (copy_u8PortId)
        {
            case DIO_PORTA: SET_BIT(PORTA_REG, copy_u8PinId); break;
            case DIO_PORTB: SET_BIT(PORTB_REG, copy_u8PinId); break;
            case DIO_PORTC: SET_BIT(PORTC_REG, copy_u8PinId); break;
            case DIO_PORTD: SET_BIT(PORTD_REG, copy_u8PinId); break;
        }
    }
}


/* ------------------------------------------------------------------ */
/*  PORT APIs                                                           */
/* ------------------------------------------------------------------ */

void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection)
{
    switch (copy_u8PortId)
    {
        case DIO_PORTA: DDRA_REG = copy_u8PortDirection; break;
        case DIO_PORTB: DDRB_REG = copy_u8PortDirection; break;
        case DIO_PORTC: DDRC_REG = copy_u8PortDirection; break;
        case DIO_PORTD: DDRD_REG = copy_u8PortDirection; break;
    }
}


void DIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue)
{
    switch (copy_u8PortId)
    {
        case DIO_PORTA: PORTA_REG = copy_u8PortValue; break;
        case DIO_PORTB: PORTB_REG = copy_u8PortValue; break;
        case DIO_PORTC: PORTC_REG = copy_u8PortValue; break;
        case DIO_PORTD: PORTD_REG = copy_u8PortValue; break;
    }
}


/* FIX: was declared in interface but never implemented */
void DIO_voidTogglePortValue(u8 copy_u8PortId)
{
    switch (copy_u8PortId)
    {
        case DIO_PORTA: PORTA_REG ^= 0xFF; break;
        case DIO_PORTB: PORTB_REG ^= 0xFF; break;
        case DIO_PORTC: PORTC_REG ^= 0xFF; break;
        case DIO_PORTD: PORTD_REG ^= 0xFF; break;
    }
}


/* FIX: was declared in interface but never implemented */
void DIO_voidGetPortValue(u8 copy_u8PortId, u8* pu8PortValue)
{
    if (pu8PortValue == NULL) return;

    switch (copy_u8PortId)
    {
        case DIO_PORTA: *pu8PortValue = PINA_REG; break;
        case DIO_PORTB: *pu8PortValue = PINB_REG; break;
        case DIO_PORTC: *pu8PortValue = PINC_REG; break;
        case DIO_PORTD: *pu8PortValue = PIND_REG; break;
    }
}


/* FIX: was declared in interface but never implemented */
void DIO_voidActivePortInternalPUR(u8 copy_u8PortId)
{
    switch (copy_u8PortId)
    {
        case DIO_PORTA: PORTA_REG = 0xFF; break;
        case DIO_PORTB: PORTB_REG = 0xFF; break;
        case DIO_PORTC: PORTC_REG = 0xFF; break;
        case DIO_PORTD: PORTD_REG = 0xFF; break;
    }
}
