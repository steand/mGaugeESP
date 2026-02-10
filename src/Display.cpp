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

#include "btIconOn.h"
#include "btIconOff.h"
#include "warningIcon.h"


void Display::begin()
{   
    
    _log("Display Begin");
    tft.init();
    delay(500);
    tft.setRotation(1);
    clear();
    _log("Display End Begin");
}

void Display::drawFrame(int x, int y)
{


  int x1=x+5;
  int x2=x+235;
  int xm=x+120;
  tft.drawLine(x1,15,x2,15,TFT_WHITE);      //Horizontal
  tft.drawLine(x1,100,x2,100,TFT_WHITE);  //Horizontal
  tft.drawLine(x1,155,x2,155,TFT_WHITE);  //Horizontal 

  tft.drawLine(x1,230,x2,230,TFT_WHITE);  //Horizontal 
  tft.drawLine(x1,285,x2,285,TFT_WHITE);  //Horizontal 

  tft.drawLine(x1,15,x1,285,TFT_WHITE);    //Vertikal
  tft.drawLine(x2,15,x2,285,TFT_WHITE);    //Vertikal

  tft.drawLine(xm,100,xm,155,TFT_WHITE);    //Vertikal
  tft.drawLine(xm,230,xm,285,TFT_WHITE);    //Vertikal
  
  

}

void Display::drawChanel(int x, int y,String name) 
{

  drawFrame(x,y);

  tft.setTextColor(TFT_YELLOW,TFT_BLACK, true);

  tft.setTextDatum(CC_DATUM);
  tft.drawString(" "+name+" ",x+120,y+15,2);

  tft.setTextDatum(TL_DATUM);

  tft.drawString("Umin",x+15,y+102,2);
  tft.drawString("Umax",x+130,y+102,2);

  tft.setTextDatum(BR_DATUM);
 
  tft.drawString("V",x+215,y+90,4);
  tft.drawString("V",x+110,y+145,2);
  tft.drawString("V",x+225,y+145,2);



  tft.setTextColor(TFT_SKYBLUE,TFT_BLACK, true);

   tft.setTextDatum(TL_DATUM);

  tft.drawString("Imin",x+15,y+232,2);
  tft.drawString("Imax",x+130,y+232,2);

  tft.setTextDatum(BR_DATUM);
 
  tft.drawString("A",x+215,y+220,4);
  tft.drawString("A",x+110,y+275,2);
  tft.drawString("A",x+225,y+275,2);



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
 
  drawChanel(0,0,"Chanel I");
  drawChanel(240,0,"Chanel II");

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

  if (!overload)
  {

    printValue(x + 15, 85, voltage, 7);

    if (voltage < minVoltage[chanel])
    {
      minVoltage[chanel] = voltage;
      printValue(10 + x, 150, minVoltage[chanel], 4);
    }

    if (voltage > maxVoltage[chanel])
    {
      maxVoltage[chanel] = voltage;
      printValue(125 + x, 150, maxVoltage[chanel], 4);
    }
  }
  else
  {
    printValue(x + 15, 85, 99.999 , 7);
    tft.pushImage(x + 200, 23, 24, 24, warningIcon);
  }
}

void Display::updateCurrent(int chanel, float current, bool overload)
{

  int x;

  x = 0;
  if (chanel == 1)
    x = 240;

  tft.setTextColor(TFT_SKYBLUE, TFT_BLACK, true);

  if (!overload)
  {
    printValue(x + 15, 215, current, 7);

    if (current < minCurrent[chanel])
    {
      minCurrent[chanel] = current;
      printValue(x + 10, 280, minCurrent[chanel], 4);
    }

    if (current > maxCurrent[chanel])
    {
      maxCurrent[chanel] = current;
      printValue(x + 125, 280, maxCurrent[chanel], 4);
    }
  }
  else
  {
    printValue(x + 15, 215, 9.999, 7);
    tft.pushImage(x + 200, 163, 24, 24, warningIcon);
  }
}

void Display::btConnected(boolean conect)
{
  tft.setSwapBytes(true);
  if (conect) {
    tft.pushImage(100,290,32,32,btIconOn);
  } else {
    tft.pushImage(100,290,32,32,btIconOff);
  }
}
