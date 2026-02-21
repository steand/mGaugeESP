#include <Arduino.h>

#include "Logging.h"

#include "APIData.h"

#include "BTHandler.h"
#include "INA219Handler.h"
#include "FZ35Handler.h"
#include "Display.h"


BTHandler server;
INA219Handler ina219;
FZ35Handler fz35;
API_Data data;
Display display;


void setup()
{

  _log_begin(115200);  
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW);  // On Board RGB-LED off

  _logd("Start BLE Server <ESPTestBLE>...");
   server.start("ESPTestBLE");

  _logd("Start Service <INA219>...");
   ina219.begin();

  _logd("Start Service <FZ35>...");
   fz35.begin();

   _logd("Start Service Display...");
   display.begin(); 
}

long timer1 = millis();
boolean conected = false;
void loop()
{
  // notify changed value
  if ((millis() - timer1) > 1000)
  {

    timer1 = millis()-1;
    ina219.getData(&data);
    
    if (server.isConnected())
    {
      if (!conected)
      {
        display.btConnected(true);
        fz35.start();
        display.fz35Connected(true);
        conected = true;
        _log("Client conected");
      }

      server.send((uint8_t *)&data, sizeof(data));
    }
    else
    {
      if (conected)
      {
        display.btConnected(false);
        fz35.stop();
        display.fz35Connected(false);
        conected = false;
        _log("Client disconected");
      }
    }
    
    display.drawData(&data);
  }
  fz35.loop();
}

