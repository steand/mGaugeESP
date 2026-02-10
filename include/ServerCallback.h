//
// Created by Stefan Andres on 2026/01/18.
// Copyright (c) 2026 Andres-stefan. All rights reserved.
//

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