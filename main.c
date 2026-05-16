/*
 * main.c  (GFD_test.c)
 * Entry point for the sign-language gesture decoder
 * Created: 2/28/2026
 * Author:  hamza
 */

#include "GFD_interface.h"

int main(void)
{
    GFD_voidInit();      /* Initialise ADC, LCD */

    while (1)
    {
        GFD_voidUpdate(); /* Read sensors, decode gesture, update LCD */
    }

    return 0;
}
