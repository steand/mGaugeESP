/*
Display.cpp - Implementation file for class "Display".


Works for tft 480x320 and setRotation(0)
Implement for ESP8266 (only)

Copyright (C) 2023  by Stefan Andres

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


#include "Display.h"

#include "btIconOn_48x48.h"
#include "btIconOff_48x48.h"
#include "warningRed_24x24.h"
#include "warningYellow_24x24.h"


void Display::begin()
{   
    
    _log("Display Begin");
/*
     delay(500);
    digitalWrite(8, LOW);
     delay(500);
    digitalWrite(8, HIGH);
     delay(500); */

    tft.init();
   
    tft.setRotation(1);
    clear();
    _log("Display End Begin");
}

void Display::drawFrame(int x, int y)
{


  int x1=x+5;
  int x2=x+235;
  int xm=x+120;
  tft.drawLine(x1,15,x2,15,TFT_WHITE);    //Horizontal
                                          // voltage
  tft.drawLine(x1,100,x2,100,TFT_WHITE);  //Horizontal
                                          //current
  tft.drawLine(x1,185,x2,185,TFT_WHITE);  //Horizontal 
                                          // Power
  tft.drawLine(x1,270,x2,270,TFT_WHITE);  //Horizontal 

  tft.drawLine(x1,15,x1,270,TFT_WHITE);    //Vertikal
  tft.drawLine(x2,15,x2,270,TFT_WHITE);    //Vertikal

  

}

void Display::drawChanel(int x, int y,String name) 
{

  drawFrame(x,y);

  tft.setTextColor(TFT_YELLOW,TFT_BLACK, true);

  tft.setTextDatum(CC_DATUM);
  tft.drawString(" "+name+" ",x+120,y+15,2);

  tft.setTextDatum(BR_DATUM);
 
  tft.drawString("V",x+215,y+90,4);

  tft.setTextColor(TFT_SKYBLUE,TFT_BLACK, true);
 
  tft.drawString("A",x+215,y+175,4);

  tft.setTextColor(TFT_GREEN,TFT_BLACK, true);
 
  tft.drawString("A",x+215,y+260,4);
 


}

void Display::printValue(int x, int y, float value, int font)
{
  int w;
  if (font == 7) w = 175;
  else w = 85;
    
  tft.setTextPadding(w);
  String str = String(value,3);
  tft.setTextDatum(BR_DATUM);
  tft.drawString(str,x+w,y,font);
  
}


void Display::clear()
{
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
 
  drawChanel(0,0,"Chanel I");
  drawChanel(240,0,"Chanel II");


   
  tft.setTextDatum(CL_DATUM);
  tft.setTextColor(TFT_YELLOW,TFT_BLACK, true);

  
  tft.drawString("Voltage overflow",130,300,2);
  tft.pushImage(100,290,24,24,warningYellow_24x24);

  

  tft.setTextColor(TFT_SKYBLUE,TFT_BLACK, true);

  tft.drawString("Current overflow",330,300,2);
  
  tft.pushImage(300,290,24,24,warningRed_24x24);

  


  btConnected(false);
  for (int i=0;i<2;i++) {
  maxVoltage[i] = 0.0;
  minVoltage[i] = 30.0;
  maxCurrent[i] = -5.0;
  minCurrent[i] = 5.0;

  }
  
}

void Display::updateVoltage(int chanel, float voltage, bool overload)
{
  int x;

  x = 0;
  if (chanel == 1)
    x = 240;

  tft.setTextColor(TFT_YELLOW, TFT_BLACK, true);

  printValue(x + 15, 85, voltage, 7);
  
  if (overload)
  {
    tft.pushImage(x + 200, 23, 24, 24, warningYellow_24x24);
 //   tft.pushImage(100,290,24,24,warningYellow_24x24);
  }
  else
  {
    tft.drawRect(x + 200, 23, 24, 24,TFT_BLACK);
  }
}

void Display::updateCurrent(int chanel, float current, bool overload)
{

  int x;

  x = 0;
  if (chanel == 1)
    x = 240;

  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK, true);
  printValue(x + 15, 170, current, 7);

  if (overload)
  {
   tft.pushImage(x + 200, 108, 24, 24, warningRed_24x24);
  //  tft.pushImage(300,290,24,24,warningRed_24x24);
  }
  else
  {
    tft.drawRect(x + 200, 108, 24, 24,TFT_BLACK);
    
  }
}

void Display::btConnected(boolean conect)
{
 //  tft.setSwapBytes(true);
  if (conect) {
    tft.pushImage(20,272,48,48,btIconOn_48x48);
  } else {
    tft.pushImage(20,272,48,48,btIconOff_48x48);
  }
}
