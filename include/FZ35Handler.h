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
#ifndef _FZ35HANDLER_H_
#define _FZ35HANDLER_H_
#include <Arduino.h>
#include "Logging.h"
#include <HardwareSerial.h>
#include <Data.h>

#define FZ35_RxT_PIN 4
#define FZ35_TxT_PIN 5


class FZ35Handler
{
public:
    
    FZ35Handler() : fxSerial(1) {} ;
    void begin();
    void start();
    void stop();
    void loop();
    boolean updateData();


private:
    HardwareSerial fxSerial;
    float voltage;
    float current;
    float capacity;
    int time;
    int pos;

    String inStr;
};

#endif
