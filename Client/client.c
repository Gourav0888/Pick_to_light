/*
 * File:   client.c
 * Author: Gourav Singh
 *
 * Created on 19 February, 2025, 10:28 PM
 */

#include "client.h"

void off_state(void)
{
    ssd[0] = ssd_display[16];
    ssd[1] = ssd_display[16];
    ssd[2] = ssd_display[16];
    ssd[3] = ssd_display[16];
    
    display(ssd);
}

void main_menu(void)
{
    static unsigned char mode = 0;
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    
    if(key==SWITCH3)
    {
        mode = !mode;
    }
    
    if(key==SWITCH2)
    {
        if(!mode) 
            state = e_u_st;
        else 
            state = e_p_id;
        
        return;
    }
    
    if(mode==0)
    {
        ssd[0] = ssd_display[11];  //U
        ssd[1] = ssd_display[10];  //_
        ssd[2] = ssd_display[5];  //S
        ssd[3] = ssd_display[12];  //t
        
        display(ssd);
    }
    else
    {
        ssd[0] = ssd_display[13];  //P
        ssd[1] = ssd_display[10];  //_
        ssd[2] = ssd_display[15];  //I
        ssd[3] = ssd_display[14];  //d
        
        display(ssd);
    }
    
    
}

void universal_stock(void)
{
    static int field=3;
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    
    if(key==SWITCH2)
    {
        field--;
        if(field==-1)
            field = 3;
    }
    
    if(key==SWITCH1)
    {
        switch(field)
        {
            case 0:
                c0++;
                if(c0==10) c0=0;
                break;
            case 1:
                c1++;
                if(c1==10) c1=0;
                break;
            case 2:
                c2++;
                if(c2==10) c2=0;
                break;
            case 3:
                c3++;
                if(c3==10) c3=0;
                break;
        }
    }
    
    if(key==SWITCH3)
    {
        write_internal_eeprom(0x00, c0);
        write_internal_eeprom(0x01, c1);
        write_internal_eeprom(0x01, c1);
        write_internal_eeprom(0x02, c2);
        write_internal_eeprom(0x03, c3);
        state = e_main_menu;
        can_transmit();
        off_flag=1;
        return;
    }
    
    if(field==0)
        ssd[0] = ssd_display[c0] | DOT;    
    else 
        ssd[0] = ssd_display[c0]; 
    
    if(field==1)
        ssd[1] = ssd_display[c1] | DOT;    
    else 
        ssd[1] = ssd_display[c1];  
    
    if(field==2)
        ssd[2] = ssd_display[c2] | DOT;    
    else 
        ssd[2] = ssd_display[c2];  
    
    if(field==3)
        ssd[3] = ssd_display[c3] | DOT;    
    else 
        ssd[3] = ssd_display[c3];  
       
    display(ssd);
}

void product_id(void)
{
    static int field=3;
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    
    if(key==SWITCH2)
    {
        field--;
        if(field==-1)
            field = 3;
    }
    
    if(key==SWITCH1)
    {
        switch(field)
        {
            case 0:
                c4++;
                if(c4==10) c4=0;
                break;
            case 1:
                c5++;
                if(c5==10) c5=0;
                break;
            case 2:
                c6++;
                if(c6==10) c6=0;
                break;
            case 3:
                c7++;
                if(c7==10) c7=0;
                break;
        }
    }
    
    if(key==SWITCH3)
    {
        write_internal_eeprom(0x04, c4);
        write_internal_eeprom(0x05, c5);
        write_internal_eeprom(0x05, c5);
        write_internal_eeprom(0x06, c6);
        write_internal_eeprom(0x07, c7);
        
        state = e_main_menu;
        off_flag=1;
        return;
    }
    
    if(field==0)
        ssd[0] = ssd_display[c4] | DOT;    
    else 
        ssd[0] = ssd_display[c4]; 
    
    if(field==1)
        ssd[1] = ssd_display[c5] | DOT;    
    else 
        ssd[1] = ssd_display[c5];  
    
    if(field==2)
        ssd[2] = ssd_display[c6] | DOT;    
    else 
        ssd[2] = ssd_display[c6];  
    
    if(field==3)
        ssd[3] = ssd_display[c7] | DOT;    
    else 
        ssd[3] = ssd_display[c7];  
       
    display(ssd);
}

void rec_u_st(void)
{
    unsigned char key = read_digital_keypad(STATE_CHANGE);
    
    if(key==SWITCH1)
    {
        if(count != 9999)
            count++;
    }
    else if(key==SWITCH2 && count)
    {
        count--;
    }
                
    ssd[0] = ssd_display[count/1000];
    ssd[1] = ssd_display[(count/100) % 10];
    ssd[2] = ssd_display[(count/10) % 10];
    ssd[3] = ssd_display[count%10];
              
    display(ssd);
    
    if(key==SWITCH3)
    {
        write_internal_eeprom(0x00, count/1000);
        write_internal_eeprom(0x01, (count/100)%10);
        write_internal_eeprom(0x01, (count/100)%10);
        write_internal_eeprom(0x02, (count/10)%10);
        write_internal_eeprom(0x03, count%10);
        c0 = read_internal_eeprom(0x00);
        c1 = read_internal_eeprom(0x01);
        c2 = read_internal_eeprom(0x02);
        c3 = read_internal_eeprom(0x03);
        state = e_main_menu;
        off_flag=1;
        return;
        
    }
    
}