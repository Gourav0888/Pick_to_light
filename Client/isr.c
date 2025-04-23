/*
 * File:   isr.c
 * Author: Gourav Singh
 *
 * Created on 19 February, 2025, 9:59 PM
 */

#include "client.h"

void __interrupt() isr(void)
{
    if(INT0IF)
    {
        off_flag = !off_flag;
        if(off_flag==0)
            state = e_main_menu;
        
        INT0IF = 0;
    }
}
