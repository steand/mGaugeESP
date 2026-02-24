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

#ifndef _KY040_H
#define _KY040_H

#include <Arduino.h>
#include <functional>
#include "FunctionalInterrupt.h"

class Ky040 {

public:
    Ky040();
    Ky040(uint8_t swPin,uint8_t clkPin,uint8_t dtPin );
    void init(uint8_t swPin,uint8_t clkPin,uint8_t dtPin );
    void begin();
    int getRotaries();
    boolean buttonPressed();
    void activateRotaries();
    void deactivateRotaries();
private:
    uint8_t swPin;
    uint8_t clkPin;
    uint8_t dtPin;
    volatile int pos;
    volatile boolean button;
    unsigned long waitPressed;

    unsigned long btnEncTime = 0;
    unsigned long last_btnEncTime = 0;

};

#endif