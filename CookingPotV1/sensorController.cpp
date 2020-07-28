#include "sensorController.h"
#include "HX711.h"
#include <Arduino.h>
#include <Adafruit_MAX31865.h>


float sensorController::getWeight(){
   
    return this->scaleInterface.get_units();
}
void sensorController::setScaleCalibrate_(int calibrationFactor){
    this->scaleCalibrationfactor= calibrationFactor;
}
Adafruit_MAX31865 &sensorController::prodTempSensor()
{
    static Adafruit_MAX31865 sensor{10, 11, 12, 13}; // ss, mosi, miso, sck
    return sensor;
}

void sensorController::initThermo(Adafruit_MAX31865 thermo)
{
    thermo.begin(MAX31865_2WIRE);
    Serial.println("Init Sensors");
    Serial.println(thermo.temperature(100.0, 430.0));
}
float sensorController::readTemp(Adafruit_MAX31865 thermo)
{
    return thermo.temperature(100.0, 430.0);
}

void sensorController::initScale(int DOUT, int CLK){
    this->scaleInterface.begin(DOUT, CLK);
}

void sensorController::calibrateScale()
{
    
    this->scaleInterface.set_scale(this->scaleCalibrationfactor);
    this->scaleInterface.tare(); //Reset the scale to 0
    Serial.println("Scale Calibrated");
    
    Serial.println(this->scaleInterface.get_units(), 3);
}
