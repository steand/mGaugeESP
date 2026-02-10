#include "ServerCallback.h"

ServerCallback::ServerCallback(BLEServer *pServer)
{
    this->pServer = pServer;
    deviceConnected = false;
    
}
void ServerCallback::onConnect(BLEServer *pServer)
{
    deviceConnected = true;
    _logd("Server connect ");
}

void ServerCallback::onDisconnect(BLEServer *pServer)
{
    deviceConnected = false;
    _logd("^Server disconnect ");
}

boolean ServerCallback::isConnected()
{
    return deviceConnected;
}
