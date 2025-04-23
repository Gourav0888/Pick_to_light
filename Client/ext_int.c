/*
 * File:   ext_int.c
 * Author: Gourav Singh
 *
 * Created on 19 February, 2025, 10:08 PM
 */

#include "ext_int.h"

void init_ext_int(void)
{
    INT0IE = 1;         //enable the external INT0
    INTEDG0 = 0;        //selecting falling edge
    PORTB = 0x00;
    TRISB = 0x01;       //RB0 as input, other pins as output
}