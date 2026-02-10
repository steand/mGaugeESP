#include <Arduino.h>

#include "Logging.h"

#include "BTHandler.h"
#include "INA219Handler.h"
#include "FZ35Handler.h"
#include "Display.h"

HardwareSerial fxSerial(1);

BTHandler server;
// INA219Handler ina219;
INA219Handler::ina219Struct inaStruct;
// FZ35Handler fz35;
Display display;

struct  {
  INA219Handler::ina219Struct inaStruct;
 // FZ35Handler::fz35Struct fzStruct;

} data;


void setup()
{
  // Wire.begin(8,9);
  _log_begin(115200);  
   delay(2000);
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(8, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW);

  _log("Start BLE Server <ESPTestBLE>...");
  server.start("ESPTestBLE");
  _log("Start Service <INA219>...");
  // ina219.begin();
  // ToDo
 // ina219.readDevice();
  _log("Start Service <FZ35>...");
  // ToDo
 // fz35.readDevice();
_log("Start Service <INA219>...");

   _log("Begin   Display...");
    display.begin();


    fxSerial.begin(9600,SERIAL_8N1, 16, 17);
    delay(500);
    fxSerial.println("start");
  
  




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
  
    // ina219.readDevice();
    // fz35.readDevice();
    // display.updateVoltage(ina219.getVoltage());
    // display.updateCurrent(ina219.getCurrent());

    display.updateVoltage(0,float(random(2000,24500)) / 1000.0);
    display.updateCurrent(0, float(random(-3600,3000)) / 1000.0);
    display.updateVoltage(1,float(random(2000,24500)) / 1000.0,true);
    display.updateCurrent(1, float(random(-3600,3000)) / 1000.0,true);

    if (server.isConnected())
    { 
      if (!conected) {
         display.btConnected(true);
         conected =true;
         _log("Client conected");
       }
      // server.send(ina219.format());
    //   fz35.readDevice();
       // data.inaStruct = ina219.getStruct();
     //  data.fzStruct = fz35.getStruct();

       server.sendSt((uint8_t *) &data,sizeof(data));
    } else {
      if (conected) {
         display.btConnected(false);
         conected =false;
         _log("Client disconected");
       }
    }
    /*
    fxSerial.write('r');
    fxSerial.write('e');  
    fxSerial.write('a');
    fxSerial.write('d');  

   fxSerial.write(13);
    fxSerial.write(10);  
*/


    // fxSerial.flush();
    
    _log("--------------------------------------");
    while (fxSerial.available() > 0){
          ch = fxSerial.read();
        _log("FX35 : %d = %s",ch, String(ch));
    }

    
    timer1 = millis();
  } 
}