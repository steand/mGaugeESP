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


#ifndef _GDATA_H
#define _GDATA_H

#include <Arduino.h>
#include <Preferences.h>

#include "APIData.h"
#include "Logging.h"

#define INAx40_RESISTOR 0.100  // must calibrated
#define INAx41_RESISTOR 0.100  // must calibrated

class GData {


public:
    GData();

    void setInaResistor(uint8_t channel, float resistor);
    float getInaResistor(uint8_t channel);
    
    
     // ina Data
    
    void setInaBusVoltage(uint8_t channel, float voltage);
    void setInaBusCurrent(uint8_t channel, float current);
    void setInaBusPower(uint8_t channel, float power);
    
    void setInaState(uint8_t channel, uint8_t status);

    //fz35 data

    void setFzVoltage(float voltage);
    void setFzCurrent(float current);
    void setFzCapacity(float capacity);
    void setFzTime(uint16_t time);
    void setFzState(uint8_t status);

    API_Data getApiData();

    void begin();
    void save();
    void load();


private:
    Preferences preferences;

    API_Data apiData;

    float inaResistor[2];
   

};

extern GData Data;

#endif