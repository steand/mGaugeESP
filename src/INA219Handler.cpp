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

#include "INA219Handler.h"


// #define TESTDATA_ON




INA219Handler::INA219Handler()
{

}

void INA219Handler::begin()
{

    
    Wire.begin(SDA_PIN,SDC_PIN);
    ina219[0] = new INA219_WE(0x40);
    ina219[0]->setShuntSizeInOhms(Data.getInaResistor(0));
    ina219[0]->setPGain(INA219_PG_320);
    ina219[0]->setBusRange(INA219_BRNG_32);
    ina219[0]->setMeasureMode(INA219_CONTINUOUS);

    ina219[1] = new INA219_WE(0x41);
    ina219[1]->setShuntSizeInOhms(Data.getInaResistor(1));
    ina219[1]->setPGain(INA219_PG_320);
    ina219[1]->setBusRange(INA219_BRNG_32);
    ina219[1]->setMeasureMode(INA219_CONTINUOUS);

    if (!ina219[0]->init())
    {
        _loge("Failed to find INA219 chip fpr 0x40");
    }
    
     if (!ina219[1]->init())
    {
        _loge("Failed to find INA219 chip fpr 0x41");
    }

    setupActive = false;
    ky040.init(KY040_SW_PIN,KY040_CLK_PIN,KY040_DT_PIN);
    ky040.begin();
    
}

void INA219Handler::setResistors()
{
    ina219[0]->setShuntSizeInOhms(Data.getInaResistor(0));
    ina219[1]->setShuntSizeInOhms(Data.getInaResistor(1));
}

int l;

void INA219Handler::logDevice(int channel)
{
    // Test only for develop

  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0; 
  bool ina219_overflow = false;
  
  shuntVoltage_mV = ina219[channel]->getShuntVoltage_mV();
  busVoltage_V = ina219[channel]->getBusVoltage_V();
  current_mA = ina219[channel]->getCurrent_mA();
  power_mW = ina219[channel]->getBusPower();
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  ina219_overflow = ina219[channel]->getOverflow();

  _logd("channel: %d ",channel); 
  
  _logd("Shunt Voltage [mV]: %f",shuntVoltage_mV);
  _logd("Bus Voltage [V]: %f",busVoltage_V);
  _logd("Load Voltage [V]: %f",loadVoltage_V);
  _logd("Current[mA]: %f",current_mA);
  _logd("Bus Power [mW]: %f",power_mW);
  if(!ina219_overflow){
    _logd("Values OK - no overflow");
  }
  else{
    _loge("Overflow! Choose higher shunt voltage range or a smaller shunt.");
  }
}

void INA219Handler::updateData()
{
#ifdef TESTDATA_ON
    static float f;
#endif

    uint8_t state;
    float voltage;
    float current;
    float power;

    for (int channel = 0; channel < 2; channel++)
    {

#ifdef TESTDATA_ON

        voltage = sin(f) * 5.0F;
        if ((f += 0.10F) > M_PI)
            f = 0.0F;
        current = 4.1F;
        power = voltage * current;
#else
        voltage = ina219[0]->getBusVoltage_V();
        current = ina219[0]->getCurrent_mA() / 1000.0;
        power = ina219[0]->getBusPower() / 1000.0;

#endif

        Data.setInaBusVoltage(channel, voltage);
        Data.setInaBusCurrent(channel, current);
        Data.setInaBusPower(channel, power);

        state = 0;
        if (voltage >= 26.0)
            state = state | API_STATE_INA_VOLTAGE | API_STATE_INA_POWER;
        if (current >= 3.2)
            state = state | API_STATE_INA_CURRENT | API_STATE_INA_POWER;
        if (ina219[0]->getOverflow())
            state = state | API_STATE_INA_OVERFLOW;
        Data.setInaState(channel, state);

        if (!setupActive) {
            Display.updateVoltage(channel, voltage, state & API_STATE_INA_VOLTAGE);
            Display.updateCurrent(channel, current, state & API_STATE_INA_CURRENT);
            Display.updatePower(channel, power, state & API_STATE_INA_POWER);
        } 
    }
}

void INA219Handler::loop()
{
    int posn;
    if (!setupActive) {
        if (ky040.buttonPressed()) {
            setupActive = true;
            ky040.activateRotaries();
            Display.drawSetup();
            pos=0;
            Display.activatePos(pos);
            resistors[0] = Data.getInaResistor(0);
            resistors[1] = Data.getInaResistor(1);
            Display.drawSetupResistor(0,resistors[0],ina219[0]->getCurrent_mA()/1000.0F);
            Display.drawSetupResistor(1,resistors[1],ina219[1]->getCurrent_mA()/1000.0F);
        } 
        return;
    }


    posn = ky040.getRotaries();
    if (!changeResistor) { 
        if ((posn > 0) && (pos < 3)) pos++;
        if ((posn < 0) && (pos > 0)) pos--;
        if (posn != 0) Display.activatePos(pos);
    } else {
        if (posn != 0 ) {
            resistors[pos] += float(posn)/1000.0F;
            ina219[pos]->setShuntSizeInOhms(resistors[pos]);
            Display.drawSetupResistor(pos,resistors[pos],ina219[pos]->getCurrent_mA()/1000.0F,true);
        }
      
        if (ky040.buttonPressed()) {
            changeResistor = false;
            Display.drawSetupResistor(pos,resistors[pos],ina219[pos]->getCurrent_mA()/1000.0F,false);
            pos = 2;
            Display.activatePos(pos);
        } 
    }

   
    if (ky040.buttonPressed()) {
        switch(pos) {
            case 0:
            case 1:
                changeResistor = true;
                Display.drawSetupResistor(pos,resistors[pos],ina219[pos]->getCurrent_mA()/1000.0F,true);
                break;
            case 2: 
                Data.setInaResistor(0,resistors[0]);
                Data.setInaResistor(1,resistors[1]);
                Data.save();
                pos = 3;
                Display.activatePos(pos);
                break;
            case 3:
                setupActive = false;
                setResistors();
                ky040.deactivateRotaries();
                Display.clear();
                break;
            default: // do nothing
                break;
        }
            
    }
    

}
