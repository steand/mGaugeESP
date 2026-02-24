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
#ifndef _INA219HANDLER_H_
#define _INA219HANDLER_H_
#include <Arduino.h>
#include "Logging.h"
#include <SPI.h>
#include <Wire.h>
#include "INA219_WE.h"
#include "Ky040.h"

#include "Data.h"     //global
#include "Display.h"  //global

#define I2C_FREQ 400000
#define SDA_PIN 2
#define SDC_PIN 1

#define KY040_SW_PIN  15
#define KY040_CLK_PIN 6
#define KY040_DT_PIN 7



class INA219Handler
{

public:

    INA219Handler();
    void logDevice(int channel); // for test only
    void updateData();
    void begin();
    void setResistors();
    void loop();

    
private:
    INA219_WE *ina219[2];
    Ky040 ky040;
    boolean setupActive;

    uint8_t pos;
    unsigned long loopTime;
    float resistors[2];
    boolean changeResistor;



};

#endif
