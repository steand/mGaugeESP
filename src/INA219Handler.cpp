#include "INA219Handler.h"


#define TESTDATA_ON




INA219Handler::INA219Handler()
{

}

void INA219Handler::begin()
{

    
    Wire.begin(SDA_PIN,SDC_PIN);
    ina219[0] = new INA219_WE(0x40);
    ina219[0]->setShuntSizeInOhms(INAx40_RESISTOR);
    ina219[0]->setPGain(INA219_PG_320);
    ina219[0]->setBusRange(INA219_BRNG_32);
    ina219[0]->setMeasureMode(INA219_CONTINUOUS);

    ina219[1] = new INA219_WE(0x41);
    ina219[1]->setShuntSizeInOhms(INAx41_RESISTOR);
    ina219[1]->setPGain(INA219_PG_320);
    ina219[1]->setBusRange(INA219_BRNG_32);
    ina219[1]->setMeasureMode(INA219_CONTINUOUS);

    if (!ina219[0]->init())
    {
        _log("Failed to find INA219 chip fpr 0x40");
    }
    
     if (!ina219[1]->init())
    {
        _log("Failed to find INA219 chip fpr 0x41");
    }
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

        Display.updateVoltage(channel, voltage, state & API_STATE_INA_VOLTAGE);
        Display.updateCurrent(channel, current, state & API_STATE_INA_CURRENT);
        Display.updatePower(channel, power, state & API_STATE_INA_POWER);
    }
}
