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

#include "BTHandler.h"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "a05fde7e-bacb-40b9-9856-efb85cdb8f66"
#define CHARACTERISTIC_UUID "eb99eb2b-048a-4fa7-a81f-4f62ca333f07"


BTHandler::BTHandler()
{
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

  // Config advertising and start it
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

boolean BTHandler::send()

{

    if (callback->isConnected()) {
        // _logd("Send ->  Struct ");
        API_Data data = Data.getApiData();
        pCharacteristic->setValue((uint8_t *)&data,sizeof(data));
        pCharacteristic->notify();
        return true;
    } 

    _loge("Try to send Data but Client not conneced. Data.");
    return false;
}


