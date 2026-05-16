/*
 * STD_types.h
 * Standard type definitions for AVR ATmega32
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char      u8;
typedef signed char        s8;

typedef unsigned short int u16;
typedef signed short int   s16;

typedef unsigned long int  u32;
typedef signed long int    s32;

typedef float              f32;
typedef double             f64;

typedef enum boolean
{
    FALSE,
    TRUE
} bool_t;

#define NULL ((void*)0)

#endif /* STD_TYPES_H */
