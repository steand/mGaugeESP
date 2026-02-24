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

#ifndef _DISPLAY_H
#define _DISPLAY_H
#include "Arduino.h"
#include "Logging.h"

#include "SPI.h"
#include <TFT_eSPI.h> // Hardware-specific library

#include "Data.h"



 
class GDisplay {

private:
   TFT_eSPI tft;           // Invoke custom library
   void drawFrame(int x, int y);
   void drawchannel(int x, int y, String name);
   void printValue(int x, int y, float value, int font);

   uint8_t lastPos;
   
  
   
   
public:
   GDisplay();
	void begin();
   void clear();
   void btConnected(boolean connect = false);
   void fz35Connected(boolean connect = false);
   void updateVoltage(int channel,float voltage,bool overload=false);
   void updateCurrent(int channel,float current,bool overload=false);
   void updatePower(int channel,float power,bool overload=false);

   void drawSetup();
   void drawSetupResistor(uint8_t channel, float resistor, float current, boolean active = false);
   void activatePos(uint8_t pos);
   


};

extern GDisplay Display;

#endif  // _DISPLAY_H
