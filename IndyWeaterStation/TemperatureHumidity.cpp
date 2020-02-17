#include <Adafruit_BME280.h>
#include "TemperatureHumidity.h"

#define SEALEVELPRESSURE_HPA (1013.25)

TemperatureHumidityStruct TempHumidity; //declare structure
//TemperatureHumidityPtr TempHumidity_ptr = &TempHumidity;

Adafruit_BME280 bme; // I2C

bool TemperatureHumidity::initial()
{
    return bme.begin();
}

void TemperatureHumidity::getTemHumiBaro()
{
    TempHumidity.temperatureC = bme.readTemperature();
    TempHumidity.humidity = bme.readHumidity();
    TempHumidity.pressure = bme.readPressure();
}

float TemperatureHumidity::getTemperatureC()
{
    return TempHumidity.temperatureC;
}

float TemperatureHumidity::getHumidity()
{
    return TempHumidity.humidity;
}

float TemperatureHumidity::getPressure()
{
    return TempHumidity.pressure / 100.0F;
}