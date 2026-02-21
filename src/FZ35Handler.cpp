#include "FZ35Handler.h"

// #define TESTDATA_ON



void FZ35Handler::begin()
{
    fxSerial.begin(9600,SERIAL_8N1, FZ35_RxT_PIN, FZ35_TxT_PIN);
    voltage =5.5;
    current =2.0;
    capacity = 0.0;
    time = 0;
    fxSerial.print("stop\r\n");
}

void FZ35Handler::start()
{
     fxSerial.print("start\r\n");
}

void FZ35Handler::stop()
{
    fxSerial.print("stop\r\n");
}


void FZ35Handler::loop()
{
    
#ifdef TESTDATA_ON
   return;
#endif   

    char ch;

    while (fxSerial.available() > 0)
    {

        ch = fxSerial.read();

        switch (ch)
        {
        case 10:
            pos = 0;
            break;
        case 13:
            // _logd("Fz35 data: %s", inStr.c_str());
            switch (pos)
            {
            case 0:
                voltage = inStr.toFloat();
                break;
            case 1:
                current = inStr.toFloat();
                break;
            case 2:
                capacity = inStr.toFloat();
                break;
            case 3:
                time = inStr.toInt() * 60;
                inStr.remove(0, inStr.indexOf(':') + 1);
                time += inStr.toInt();
                break;
            default:
                _loge("Wrong pos #%d", pos);
                break;
            }
            pos++;
            inStr = "";
        case 32:
            break; // delete space
        default:
            inStr += String(ch);
        }
    }
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

int FZ35Handler::getTime()
{
    return time;
}

boolean FZ35Handler::getData(API_Data *data)
{
     /* Test data
    if ( voltage<= 0.0) voltage = 5.5;
    voltage = voltage - 0.1;
    if ( current <= 0.0) current = 2.0;
    current = current - 0.01; 
    if ( capacity > 10.0 ) capacity = 1.0;
    capacity = capacity = capacity + 0.02;
    time = time + 0.001;
    */
    data->fz35Voltage = voltage;
    data->fz35Current = current;
    data->fz35Capacity = capacity;
    data->fz35DischargeTime = time;

#ifdef TESTDATA_ON
    data->fz35Voltage = 21.0;
    data->fz35Current = 4.2;
    data->fz35Capacity = 2.7;
    data->fz35DischargeTime = 128;
#endif

    return true;
}
