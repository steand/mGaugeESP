/*
Logging.h - Include file for logging via Serial.
Copyright (C) 2026  by Stefan Andres

lightweight logging for develop ESP.
If Loglevel 0 (off) all logging macros not compile (temporary removed).
This going to reduce binary size and increased speed at produktion time. 

Works for ESP only
Include this file in all *.cpp file
Log Level going to define _LOGGING in this file at compile time.

if you use Serial2 change _SERIAL to Serial2.

output format:
00:02.044 [main.cpp:20] setup() [info]: Logging Start (115200)
00:02.044 [main.cpp:22] setup() [debug]: Setup end

time will reset every 70 minutes to 00:00:000 !

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



#ifndef _LOGGING_H_
#define _LOGGING_H_

#define _LOGGING 3 //Logging Level = 0: none | 1:error | 2:info | 3:debug 

#define _NONE 0
#define _ERROR 1
#define _INFO 2
#define _DEBUG 3

#define __SERIAL Serial // Serial | Serial2

void __log_time(byte type, const char *filename,const char *function, int line);

// macro definiton for logging

#define _log_begin(__speed)    // start Serial for logging
#define _log(__log_x, ...)     // logs info (green)
#define _loge(__log_x, ...)   // logs error (red)
#define _logd(__log_x, ...)   // logs debug (yellow)


#if _LOGGING >0
#undef _loge
#undef _log_begin
#define _loge(__log_x, ...) __log_time(_ERROR,__FILE__ , __func__ , __LINE__ );\
                           __SERIAL.printf( __log_x"\n" ,##__VA_ARGS__)
#define _log_begin(__speed) delay(1000);\
                             __SERIAL.begin(__speed);\
                             __log_time(_INFO,__FILE__ , __func__ , __LINE__ );\
                             __SERIAL.printf("Logging Start (%d)\r\n",__speed)
#endif   

#if _LOGGING >1
#undef _log
#define _log(__log_x, ...) __log_time(_INFO,__FILE__ , __func__ , __LINE__ );\
                           __SERIAL.printf( __log_x"\r\n" ,##__VA_ARGS__)
#endif 

#if _LOGGING >2
#undef _logd
#define _logd(__log_x, ...) __log_time(_DEBUG,__FILE__ , __func__ , __LINE__ );\
                           __SERIAL.printf( __log_x"\r\n" ,##__VA_ARGS__)

#endif 


#endif /* _LOGGING_H_ */
