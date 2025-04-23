/*
 * File:   main.c
 * Author: Gourav Singh
 *
 * Created on 19 February, 2025, 9:22 PM
 */


#include "client.h"

extern unsigned char can_payload[13];
unsigned char p_id[5], u_st[5];
unsigned char new_p_id[5], new_u_st[5];

void init_config(void)
{
    GIE = 1;
    PEIE = 1;
    init_ssd_control();
    init_digital_keypad();
    init_ext_int();
    init_can();
    state = e_main_menu;
    off_flag=1;
}

void main(void) 
{
    init_config();
    c0 = read_internal_eeprom(0x00);
    c1 = read_internal_eeprom(0x01);
    c2 = read_internal_eeprom(0x02);
    c3 = read_internal_eeprom(0x03);
    c4 = read_internal_eeprom(0x04);
    c5 = read_internal_eeprom(0x05);
    c6 = read_internal_eeprom(0x06);
    c7 = read_internal_eeprom(0x07);
    while(1)
    {
        if(can_receive())
        {
            if((c4==can_payload[D0]) && (c5==can_payload[D1]) && (c6==can_payload[D2]) && (c7==can_payload[D3]))
            {
//                for(int i = 0; i<3; i++) 
//                {
//                    count = count * 10 + can_payload[D4+i];
//                }
                count = (can_payload[D4]*1000) + (can_payload[D5]*100) + (can_payload[D6]*10) + (can_payload[D7]) ;
                off_flag=0;
                state = e_rec_u_st;
            }
        }
        
        if(off_flag)
        {
            off_state();
//            continue;
        }
        else
        {
            switch(state)
            {
                case e_main_menu:
                    main_menu();
                    break;
                
                case e_u_st:
                    universal_stock();
                    break;
                
                case e_p_id:
                    product_id();
                    break;
                
                case e_rec_u_st:
                    rec_u_st();
                    break;
                
            }
        }
    }
}
