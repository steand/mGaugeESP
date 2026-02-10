/*
Logging.ccp
Copyright (C) 2026  by Stefan Andres

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

#include <Arduino.h>
#include "Logging.h"

void __log_time(byte type, const char *filename,const char *function, int line) {
   // micros for 70 Minuten (overflow)
   const char *ta[] = {"[none","\x1b[91merror","\x1b[92minfo","\x1b[93mdebug"};
   long t = millis();
   long thour = (t % 360000000)/3600000;
   long tmin = (t % 3600000)/60000;
   long tsec = (t % 60000) / 1000;
   long tmil = t % 1000;
   char *p = strrchr(filename,'/') +1 ;
   __SERIAL.printf("%02lu:%02lu:%02lu.%03lu [%s:%d] %s() [%s\x1b[0m]: ",
                     thour,tmin, tsec , tmil ,p,line,function,ta[type]);
 }
