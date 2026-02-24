#ifndef _KY040_H
#define _KY040_H

#include <Arduino.h>

class Ky040 {

public:
    Ky040(uint8_t swPin,uint8_t clkPin,uint8_t dtPin );
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

    void rotariesISR();



};

#endif