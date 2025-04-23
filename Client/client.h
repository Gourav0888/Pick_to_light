/* 
 * File:   client.h
 * Author: Gourav Singh
 *
 * Created on 19 February, 2025, 9:29 PM
 */

#ifndef CLIENT_H
#define	CLIENT_H
#include <xc.h>
#include "dkp.h"
#include "ssd.h"
#include "eeprom.h"
#include "ext_int.h"
#include "can.h"

typedef enum
{
    e_off, e_u_st, e_p_id, e_main_menu, e_rec_u_st
}State_t;

unsigned char ssd[MAX_SSD_CNT];
unsigned char ssd_display[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, UNDERSCORE, LETTER_U, LETTER_t, LETTER_P, LETTER_d, LETTER_I, BLANK};
//                               0    1    2     3      4     5    6     7      8     9        10        11        12         13        14         15      16
State_t state;
unsigned char off_flag;
unsigned char c0, c1, c2, c3, c4, c5, c6, c7;
int count = 0;

#define _XTAL_FREQ         20000000



void init_config(void);

void off_state(void);

void main_menu(void);

void universal_stock(void);

void product_id(void);

void rec_u_st(void);


#endif	/* CLIENT_H */

