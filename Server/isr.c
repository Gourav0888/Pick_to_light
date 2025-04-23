/*
 * File:   isr.c
 * Author: Gourav Singh
 *
 * Created on 21 March, 2025, 7:15 PM
 */

#include <xc.h>
#include "server.h"

extern unsigned char ch;
    
void __interrupt() isr(void)
{
    if (RCIF == 1)
    {
        if (OERR == 1)
            OERR = 0;
        
        ch = RCREG;
        
        RCIF = 0;
    }
}