#include <Arduino.h>

#include "Logging.h"

#include "APIData.h"
#include "BTHandler.h"
#include "INA219Handler.h"
#include "FZ35Handler.h"
#include "Display.h"


BTHandler server;
INA219Handler ina219;
// FZ35Handler fz35;
Display display;

API_Data data;





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
  // ToDo

   _logd("Start Service Display...");
   display.begin();

}

String str;
char ch;

long timer1 = millis();
long timer2 = millis()+500;
String s;
boolean conected = false;
unsigned int i;
void loop()
{
  // notify changed value
  if ((millis() - timer1) > 2000) 
  {
  
    ina219.getData(&data);
    display.drawData(&data);


    if (server.isConnected())
    { 
      if (!conected) {
         display.btConnected(true);
         conected =true;
         _log("Client conected");
       }
     
       server.send((uint8_t *) &data,sizeof(data));
    } else {
      if (conected) {
         display.btConnected(false);
         conected =false;
         _log("Client disconected");
       }
    }

    timer1 = millis();
  } 
}