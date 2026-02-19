/*
Copyright (C) 2026  by Stefan Andres

API data struct  for mGaugeESP
Include this file in *.cpp file

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.  

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/
#ifndef _API_DATA_H_
#define _API_DATA_H_
#include <Arduino.h>

/*
  ina#State:
    0b10000000 : Data not avalible
    0b00000001 : Voltage out of range
    0b00000010 : current overflow
    0b00000001 : Power out of range

  fz35State:
    0b00000001 : Data not avalible
*/

#define API_STATE_INA0_VOLTAGE  0b00000001 
#define API_STATE_INA0_CURRENT  0b00000010 
#define API_STATE_INA0_POWER    0b00000100 
#define API_STATE_INA0_OVERFLOW 0b00001000
#define API_STATE_INA1_VOLTAGE  0b00010000
#define API_STATE_INA1_CURRENT  0b00100000 
#define API_STATE_INA1_POWER    0b01000000 
#define API_STATE_INA1_OVERFLOW 0b10000000
#define API_STATE_fz35_START    0b00000001

struct  API_Data {
 
 float   ina0Voltage;          // byte 0..3
 float   ina0Current;           // byte 4..7
 float   ina0Power;             // byte 8..11
 float   ina1Voltage;          // byte 12..15
 float   ina1Current;           // byte 16..19
 float   ina1Power;             // byte 20..23 
 float   fz35Voltage;          // byte 24..27
 float   fz35Current;           // byte 28..31
 float   fz35Capacity;          // byte 32..35
 uint16_t fz35DischargeTime;    // byte 36..37 - in minutes
 uint8_t  inaState;             // byte 38
 uint8_t  fz35State;            // byte 39
};

  

#endif