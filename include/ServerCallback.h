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

#ifndef _SERVERCALLBACK_H_
#define _SERVERCALLBACK_H_
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "Logging.h"

class ServerCallback : public BLEServerCallbacks {
 public:
ServerCallback(BLEServer* pServer);
void onConnect(BLEServer* pServer);
void onDisconnect(BLEServer* pServer);

boolean isConnected();
  
 private:
BLEServer* pServer;

boolean deviceConnected;

};

#endif