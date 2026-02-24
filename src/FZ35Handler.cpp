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


boolean FZ35Handler::updateData()
{
    Data.setFzVoltage(voltage);
    Data.setFzCurrent(current);
    Data.setFzCapacity(capacity);
    Data.setFzTime(time);

#ifdef TESTDATA_ON
    Data.setFzVoltage(21.0);
    Data.setFzCurrent(4.2);
    Data.setFzCapacity(2.7);
    Data.setFzTime(128);
#endif

    return true;
}
