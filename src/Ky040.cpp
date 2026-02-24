#include "Ky040.h"
#include <functional>
#include "FunctionalInterrupt.h"

Ky040::Ky040(uint8_t swPin, uint8_t clkPin, uint8_t dtPin)
{
    this->swPin = swPin;
    this->clkPin = clkPin;
    this->dtPin = dtPin;
}

void Ky040::begin()
{
    pinMode(swPin,INPUT_PULLUP);
    pinMode(clkPin,INPUT_PULLUP);
    pinMode(dtPin,INPUT_PULLUP);
    
    
    button = false;
    waitPressed = millis();


    auto isr = [this]() {
        button = true;
    };
    attachInterrupt(digitalPinToInterrupt(swPin), isr, FALLING);


}

boolean Ky040::buttonPressed()
{      
    if (button) {
        if (millis() - waitPressed < 2000 ) { // debounce for 2 sec. 
           button = false; 
           return false;
        }
        boolean ret = button;
        button = false;
        waitPressed = millis();
        return ret;
    }
    return false;
    
}


void Ky040::activateRotaries()
{ 
    auto isr = [this]() {
        btnEncTime = millis();
        if (btnEncTime - last_btnEncTime > 250) // debounce 250msec
         { if(digitalRead(dtPin)) pos++;
            else pos--;
            last_btnEncTime = btnEncTime;
        }
       
    };
    pos = 0;
    attachInterrupt(digitalPinToInterrupt(clkPin), isr, FALLING);
}

void Ky040::deactivateRotaries()
{
    detachInterrupt(digitalPinToInterrupt(clkPin));
}

int Ky040::getRotaries()
{   
    int ret = pos;
    pos = 0;
    return ret;
}
