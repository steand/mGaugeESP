#include "FZ35Handler.h"

FZ35Handler::FZ35Handler()
{
 voltage =5.5;
 current =2.0;
 capacity = 0.0;
 time = 0.0;
} 

boolean FZ35Handler::readDevice()
{ 
    // Test data
    if ( voltage<= 0.0) voltage = 5.5;
    fzStruct.voltage = voltage = voltage - 0.1;
    if ( current <= 0.0) current = 2.0;
    fzStruct.current = current = current - 0.01; 
    if ( capacity > 10.0 ) capacity = 1.0;
    fzStruct.capacity = capacity = capacity + 0.02;
    fzStruct.time = time + 0.001;
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

FZ35Handler::fz35Struct FZ35Handler::getStruct()
{
    return fzStruct;
}

String FZ35Handler::format()
{
   
   
    String s = "#FZ35,"+String(voltage,3) + "," + String(current,3) + "," + String(capacity,3);
    return s;
}
