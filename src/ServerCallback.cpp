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
