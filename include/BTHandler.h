//
// Created by Stefan Andres on 2026/01/18.
// Copyright (c) 2026 Andres-stefan. All rights reserved.
//

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
