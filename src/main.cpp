#include <Arduino.h>

#include "Logging.h"

#include "Data.h"

#include "BTHandler.h"
#include "INA219Handler.h"
#include "FZ35Handler.h"
#include "Display.h"
#include "Ky040.h"


GData Data;  // Global!!!
GDisplay Display; // Global !!!

INA219Handler ina219;
FZ35Handler fz35;

BTHandler server;

Ky040 ky(15,6,7);

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

   ky.begin();
   ky.activateRotaries();

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
    _log("Rotary: %d",ky.getRotaries());
  }
  fz35.loop();
  if (ky.buttonPressed()) {_log("Pressed");}
}

