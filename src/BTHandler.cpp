//
// Created by Stefan Andres on 2026/01/18.
// Copyright (c) 2026 Andres-stefan. All rights reserved.
//

#include "BTHandler.h"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "a05fde7e-bacb-40b9-9856-efb85cdb8f66"
#define CHARACTERISTIC_UUID "eb99eb2b-048a-4fa7-a81f-4f62ca333f07"



BTHandler::BTHandler(){

   
}

void BTHandler::start(const char *name)
{ 
    // Create the BLE Device
  BLEDevice::init(name);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  callback = new ServerCallback(pServer);
  pServer->setCallbacks(callback);

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  startAdvertising();
}

void BTHandler::startAdvertising()
{
    BLEDevice::startAdvertising();
   _log("Waiting a client connection to notify...");
}


void BTHandler::send(String msg){
    if (callback->isConnected()) {
        _logd("Send : %s",msg.c_str());
        pCharacteristic->setValue(msg.c_str());
        pCharacteristic->notify();
    } else {
        _loge("Try to send Data but Client not conneced. Data. %s",msg.c_str());
    }


}

void BTHandler::send(uint8_t *data, size_t len)
{
    if (callback->isConnected()) {
        _logd("Send ->  Struct ");
        pCharacteristic->setValue(data,len);
        pCharacteristic->notify();
    } else {
        _loge("Try to send Data but Client not conneced. Data.");
    }
}

boolean BTHandler::isConnected()
{
    boolean connect = callback->isConnected();
    if (connect) {
        oldDeviceConnected = true;
    } else {
        if (oldDeviceConnected){
            oldDeviceConnected = false;
            startAdvertising();
        }
    }

    return connect;
}
