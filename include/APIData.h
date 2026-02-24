/*
   Copyright (C) 2026  by Stefan Andres (develop@andres-stefan.de)

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


#define API_STATE_INA_VOLTAGE  0b00000001 
#define API_STATE_INA_CURRENT  0b00000010 
#define API_STATE_INA_POWER    0b00000100 
#define API_STATE_INA_OVERFLOW 0b00001000

struct  API_Data {
    // order are nessery for 16, 32 & 64 bit memory architekture
    // do not change !!!
 
 float   inaVoltage[2];          // byte 0..7
 float   inaCurrent[2];           // byte 8..15
 float   inaPower[2];             // byte 16..23
 float   fz35Voltage;          // byte 24..27
 float   fz35Current;           // byte 28..31
 float   fz35Capacity;          // byte 32..35
 uint16_t fz35DischargeTime;    // byte 36..37 - in minutes
 uint8_t  inaState;             // byte 38
 uint8_t  fz35State;            // byte 39
};

struct ConfigData_t {
    boolean inaDisplay[2];
    float inaResistor[2];
};

extern API_Data apiData;


  

#endif