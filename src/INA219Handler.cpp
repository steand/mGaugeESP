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
    /* Test data
   
        log inaData

    */

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

float INA219Handler::getVoltage(int channel)
{
    return ina219[channel]->getBusVoltage_V();;
}

float INA219Handler::getCurrent(int channel)
{
    return ina219[channel]->getCurrent_mA() / 1000.0;
}


boolean INA219Handler::getData(API_Data *data )
{
   

#ifdef TESTDATA_ON
    if (data->ina0Voltage <= 10.0F) data->ina0Voltage += 0.2F;
    else data->ina0Voltage = 9.0F;
    data->ina0Current  = 3.0;
    data->ina0Power    = data->ina0Current * data->ina0Voltage;
#else 
    data->ina0Voltage = ina219[0]->getBusVoltage_V();
    data->ina0Current  = ina219[0]->getCurrent_mA() / 1000.0; 
    data->ina0Power    = ina219[0]->getBusPower()/1000.0;

#endif


    data->inaState = 0;
    if (data->ina0Voltage >= 26.0) data->inaState = data->inaState | API_STATE_INA0_VOLTAGE | API_STATE_INA0_POWER;
    if (data->ina0Current  >= 3.2)  data->inaState = data->inaState | API_STATE_INA0_CURRENT | API_STATE_INA0_POWER;
    if (ina219[0]->getOverflow())   data->inaState = data->inaState | API_STATE_INA0_OVERFLOW;

    
#ifdef TESTDATA_ON
    static float f;
    data->ina1Voltage = sin(f)*5.0F;
    if ((f += 0.10F) > M_PI) f=0.0F;
    data->ina1Current  = 2.1;
    data->ina1Power    = data->ina1Voltage * data->ina1Current;
#else
    data->ina1Voltage = ina219[1]->getBusVoltage_V();
    data->ina1Current  = ina219[1]->getCurrent_mA() / 1000.0; 
    data->ina1Power    = ina219[1]->getBusPower()/1000.0;
#endif


    if (data->ina1Voltage >= 26.0) data->inaState = data->inaState | API_STATE_INA1_VOLTAGE | API_STATE_INA1_POWER;
    if (data->ina1Current  >= 3.2)  data->inaState = data->inaState | API_STATE_INA1_CURRENT | API_STATE_INA1_POWER;
    if (ina219[0]->getOverflow())   data->inaState = data->inaState | API_STATE_INA1_OVERFLOW;


    return (ina219[0]->getOverflow() || ina219[1]->getOverflow());
}

