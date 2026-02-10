/*
Include file for logging via Serial.
Copyright (C) 2026  by Stefan Andres

Develop for ESP
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
#ifndef _INA219HANDLER_H_
#define _INA219HANDLER_H_
#include <Arduino.h>
#include "Logging.h"
#include <SPI.h>
#include <Wire.h>
#include "INA219_WE.h"

// #define SDA 45
// #define SDC 48

class INA219Handler
{
    

public:
    struct ina219Struct {
        float voltage;
        float current;
        float power;
    } ;

    INA219Handler();
    boolean readDevice();
    float getVoltage();
    float getCurrent();
    String format();
    ina219Struct getStruct();
    void begin();
    
private:
   
    float voltage;
    float current;
    ina219Struct inaStruct;
    INA219_WE *ina219;

};

#endif
