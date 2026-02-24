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

#ifndef _BTHANDLER_H_
#define _BTHANDLER_H_

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "ServerCallback.h"

#include "Data.h"

#include "Logging.h"

class BTHandler
{
public:
    BTHandler();
    void start(const char * name);
    void startAdvertising();
    boolean send();
    boolean isConnected();

private:
    ServerCallback *callback;
    BLEServer *pServer = NULL;
    BLECharacteristic *pCharacteristic = NULL;
    bool deviceConnected = false;
    bool oldDeviceConnected = false;

    API_Data data;

    uint32_t value = 0;
};

#endif // SRC_BTHANDLER_H_
