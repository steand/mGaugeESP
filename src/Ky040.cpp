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

#include "Ky040.h"
#include "Logging.h"

Ky040::Ky040()
{
}

Ky040::Ky040(uint8_t swPin, uint8_t clkPin, uint8_t dtPin)
{
    init(swPin,clkPin,dtPin);
}

void Ky040::init(uint8_t swPin, uint8_t clkPin, uint8_t dtPin)
{
    this->swPin = swPin;
    this->clkPin = clkPin;
    this->dtPin = dtPin;
}

void Ky040::begin()
{
    pinMode(swPin,INPUT_PULLUP);
    pinMode(clkPin,INPUT_PULLUP);
    pinMode(dtPin,INPUT_PULLUP);
    
    
    button = false;
    waitPressed = millis();


    auto isr = [this]() {
        button = true;
    };
    attachInterrupt(digitalPinToInterrupt(swPin), isr, FALLING);


}

boolean Ky040::buttonPressed()
{      
    if (button) {
        if (millis() - waitPressed < 1000 ) { // debounce for 1 sec. 
           button = false; 
           return false;
        }
        _logd("Button pressed");
        button = false;
        waitPressed = millis();
        return true;
    }
    return false;
    
}


void Ky040::activateRotaries()
{ 
    auto isr = [this]() {
        btnEncTime = millis();
        if (btnEncTime - last_btnEncTime > 250) // debounce 250msec
         { if(digitalRead(dtPin)) pos++;
            else pos--;
            last_btnEncTime = btnEncTime;
        }
       
    };
    pos = 0;
    attachInterrupt(digitalPinToInterrupt(clkPin), isr, FALLING);
}

void Ky040::deactivateRotaries()
{
    detachInterrupt(digitalPinToInterrupt(clkPin));
}

int Ky040::getRotaries()
{   
    int ret = pos;
    pos = 0;
    return ret;
}
