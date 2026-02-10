#include "INA219Handler.h"




INA219Handler::INA219Handler()
{

}

void INA219Handler::begin()
{

    
   // Wire.begin(45,3);
    ina219 = new INA219_WE(0x40);

    if (!ina219->init())
    {
        _log("Failed to find INA219 chip");
    }
}

int l;

boolean INA219Handler::readDevice()
{
    /* Test data
    inaStruct.voltage = sin(float(l)* DEG_TO_RAD)*3.0;
    if (l++>180) l=0;
    inaStruct.current = float(random(2000,3000))/1000; 
    inaStruct.power = inaStruct.voltage * inaStruct.current;
    */

  float shuntVoltage_mV = 0.0;
  float loadVoltage_V = 0.0;
  float busVoltage_V = 0.0;
  float current_mA = 0.0;
  float power_mW = 0.0; 
  bool ina219_overflow = false;
  
  shuntVoltage_mV = ina219->getShuntVoltage_mV();
  busVoltage_V = ina219->getBusVoltage_V();
  current_mA = ina219->getCurrent_mA();
  power_mW = ina219->getBusPower();
  loadVoltage_V  = busVoltage_V + (shuntVoltage_mV/1000);
  ina219_overflow = ina219->getOverflow();
  
  Serial.print("Shunt Voltage [mV]: "); Serial.println(shuntVoltage_mV);
  Serial.print("Bus Voltage [V]: "); Serial.println(busVoltage_V);
  Serial.print("Load Voltage [V]: "); Serial.println(loadVoltage_V);
  Serial.print("Current[mA]: "); Serial.println(current_mA);
  Serial.print("Bus Power [mW]: "); Serial.println(power_mW);
  if(!ina219_overflow){
    Serial.println("Values OK - no overflow");
  }
  else{
    Serial.println("Overflow! Choose higher shunt voltage range or a smaller shunt.");
  }
  Serial.println();

    return true;
}

float INA219Handler::getVoltage()
{
    return ina219->getBusVoltage_V();;
}

float INA219Handler::getCurrent()
{
    return ina219->getCurrent_mA() / 1000.0;
}

String INA219Handler::format()
{
    
   
    String s = "#INA219,"+String(voltage,3) + "," + String(current,3);
    return s;
}

INA219Handler::ina219Struct INA219Handler::getStruct()
{
    inaStruct.voltage = ina219->getBusVoltage_V();
    inaStruct.current = ina219->getCurrent_mA() / 1000.0;
    inaStruct.power  = ina219->getBusPower()/1000.0;
    return inaStruct;
}

