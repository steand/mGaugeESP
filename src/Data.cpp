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

#include "Data.h"

GData::GData() {}

void GData::setInaResistor(uint8_t channel, float resistor)
{
    this->inaResistor[channel] = resistor;
}

float GData::getInaResistor(uint8_t channel)
{
    return inaResistor[channel];
}


void GData::setInaBusVoltage(uint8_t channel, float voltage)
{
    apiData.inaVoltage[channel] = voltage;

}


void GData::setInaBusCurrent(uint8_t channel, float current)
{
    apiData.inaCurrent[channel] = current;
}

void GData::setInaBusPower(uint8_t channel, float power)
{
   apiData.inaPower[channel] = power;

}

void GData::setInaState(uint8_t channel, uint8_t status)
{
    if (channel == 0) apiData.inaState = (apiData.inaState & 0xF0) | status ;
    else apiData.inaState = (apiData.inaState & 0x0F) | status<<4 ;

}


void GData::setFzVoltage(float voltage)
{
    apiData.fz35Voltage = voltage;
}

void GData::setFzCurrent(float current)
{
    apiData.fz35Current = current;
}


void GData::setFzCapacity(float capacity)
{
    apiData.fz35Capacity = capacity;
}


void GData::setFzTime(uint16_t time)
{
    apiData.fz35DischargeTime = time;
}

void GData::setFzState(uint8_t status)
{
    apiData.fz35State = status;
}


API_Data GData::getApiData()
{
    return apiData;
}

void GData::begin()
{
    preferences.begin("Setup");
    load();
}

void GData::save()
{
    _logd("Preferences save");
    preferences.putBool("Init", true);
    preferences.putFloat("Resistor0",inaResistor[0] );
    preferences.putFloat("Resistor1",inaResistor[1] );

}

void GData::load()
{
    if (preferences.getBool("Init")) {
        _logd("Preferenc OK");
        inaResistor[0] = preferences.getFloat("Resistor0");
        inaResistor[1] = preferences.getFloat("Resistor1");

    } else {
        _logd("Preferences not init");
        inaResistor[0] = INAx40_RESISTOR;
        inaResistor[1] = INAx41_RESISTOR;
        save();
    }
}
