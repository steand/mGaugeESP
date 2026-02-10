/*
   Display.h - Header file for class "Display".

   The Main-Display for MiniLab

   Works for tft 480x320 and setRotation(1)
   Implement for ESP32 (only)

   Copyright (C) 2019  by Stefan Andres

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



 
class Display {

private:
   TFT_eSPI tft;           // Invoke custom library
   void drawFrame(int x, int y);
   void drawChanel(int x, int y, String name);
   void printValue(int x, int y, float value, int font);
   float maxVoltage[2];
   float minVoltage[2];
   float oldVoltage[2];
   float maxCurrent[2];
   float minCurrent[2];
   
   
public:
	void begin();
   void clear();
   void updateVoltage(int chanel,float voltage,bool overload=false);
   void updateCurrent(int chanel,float current,bool overload=false);
   void btConnected(boolean conect = false);
   

};


#endif  // _DISPLAY_H
