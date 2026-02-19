#include "FZ35Handler.h"




void FZ35Handler::begin()
{
    fxSerial.begin(9600,SERIAL_8N1, 16, 17);
    voltage =5.5;
    current =2.0;
    capacity = 0.0;
    time = 0.0;
}

void FZ35Handler::loop()
{
    char ch;
        /*
    fxSerial.write('r');
    fxSerial.write('e');  
    fxSerial.write('a');
    fxSerial.write('d');  

   fxSerial.write(13);
    fxSerial.write(10);  
*/


    // fxSerial.flush();
    
    while (fxSerial.available() > 0){
          ch = fxSerial.read();
        _logd("fz35 : %d = %s",ch, String(ch));
    }

    
}

boolean FZ35Handler::readDevice()
{ 
    // Test data
    if ( voltage<= 0.0) voltage = 5.5;
    voltage = voltage - 0.1;
    if ( current <= 0.0) current = 2.0;
    current = current - 0.01; 
    if ( capacity > 10.0 ) capacity = 1.0;
    capacity = capacity = capacity + 0.02;
    time = time + 0.001;
    return true;
}

float FZ35Handler::getVoltage()
{
    return voltage;
}

float FZ35Handler::getCurrent()
{
    return current;
}

float FZ35Handler::getCapcity()
{
    return capacity;
}

boolean FZ35Handler::getData(API_Data *data)
{
    data->fz35Voltage = voltage;
    data->fz35Current = current;
    data->fz35Capacity = capacity;
    data->fz35DischargeTime = time;
    return true;
}
