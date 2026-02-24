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

#include <Arduino.h>

#include "Logging.h"

#include "Data.h"

#include "BTHandler.h"
#include "INA219Handler.h"
#include "FZ35Handler.h"
#include "Display.h"


GData Data;  // Global!!!
GDisplay Display; // Global !!!

INA219Handler ina219;
FZ35Handler fz35;

BTHandler server;

void setup()
{

  _log_begin(115200);  
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW);  // On Board RGB-LED off

  _logd("Start Service Data...");
   Data.begin();

 
  _logd("Start Service <INA219>...");
   ina219.begin();

  _logd("Start Service <FZ35>...");
   fz35.begin();

   _logd("Start Service Display...");
   Display.begin(); 

   _logd("Start BLE Server <ESPTestBLE>...");
   server.start("ESPTestBLE");


}

long timer1 = millis();
boolean conected = false;
void loop()
{
  // notify changed value
  if ((millis() - timer1) > 1000)
  {

    timer1 = millis()-1;
    ina219.updateData();
    
    if (server.isConnected())
    {
      if (!conected)
      {
        Display.btConnected(true);
        fz35.start();
        Display.fz35Connected(true);
        conected = true;
        _log("Client conected");
      }
      fz35.updateData();
      server.send();
    }
    else
    {
      if (conected)
      {
        Display.btConnected(false);
        fz35.stop();
        Display.fz35Connected(false);
        conected = false;
        _log("Client disconected");
      }
    } 
    
  }
  ina219.loop();
  fz35.loop();
 
}

