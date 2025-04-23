/*
 * File:   main.c
 * Author: Gourav Singh
 *
 * Created on 20 February, 2025, 12:49 PM
 */

#include <xc.h>
#include "server.h"
#include <string.h>
unsigned char ch;
static char read=0, flag=0, index=0;
unsigned char data[9]={0};
unsigned char u_st[5]={0};
void init_config(void)
{
    init_can();
    init_uart();
    puts("Press enter to start communication: \n\r");
	 /* Enabling peripheral interrupt */
   PEIE = 1;
    
    /* Enabling global interrupt */
   GIE = 1;
}


void main(void) 
{
    init_config();
    data[8]='\0';
    u_st[5] = '\0';
    while(1)
    {
        if(ch==13)
        {
            flag++;
            if(flag==1)
            {
                puts("Enter the P_ID: \n\r");
                read++;
            }
            else if(flag==2)
            {
                puts("\n\rEnter the U_ST: \n\r");
                read++;
            }
            else if(flag==3)
            {
                int front = 4, back=7;
                for(int i=4; i>=0; i--)
                {
                    if(u_st[i]>='0' && u_st[i]<='9')
                    {
                        data[back--] = u_st[i];
                    }
                    else
                    {
                        data[front++] = '0';
                    }
                }
            
                puts("\n\rData transmitting\n\r");
                can_transmit();
                puts("Entered data: ");
                
                puts(data);
                puts("\n\r");
                index = 0;
                flag = 0;
                read = 0;
                memset(data, 0, 8);
                memset(u_st, 0, 4);
            }
            
            ch='\0';
        }
        
        if(flag==1 && read==1)
        {
            if(ch!='\0')
            {
                putch(ch);
                if(index>=0 && index<=3)
                {
                    data[index++] = ch;
                }
                ch = '\0';
            }
        }
        else if(flag==2 && read==2)
        {
            if(ch!='\0')
            {
                putch(ch);
                if(index>=4 && index<=7)
                {
                    u_st[index-4] = ch;
                    index++;
                }
                ch = '\0';
            }
        }
       
        
        if(can_receive())
        {
            puts("U_st  P_id\n\r");
            putch(can_payload[D0]);
            putch(can_payload[D1]);
            putch(can_payload[D2]);
            putch(can_payload[D3]);
            putch(' ');
            putch(' ');
            putch(can_payload[D4]);
            putch(can_payload[D5]);
            putch(can_payload[D6]);
            putch(can_payload[D7]);
            puts("\n\r");
            
            puts("Press enter to start communication: \n\r");
        }
        
        
    }
}
