/* 
 * File:   eeprom.h
 * Author: Gourav Singh
 *
 * Created on 19 February, 2025, 9:54 PM
 */
#ifndef EEPROM_H
#define EEPROM_H

void write_internal_eeprom(unsigned char address, unsigned char data); 
unsigned char read_internal_eeprom(unsigned char address);

#endif