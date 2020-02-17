#include <Arduino.h>
#include "TemperatureHumidity.h"
#include "dust.h"
#include "uv.h"

struct WeatherStruct
{
  float temperatureC;
  float pressure;
  float humidity;
  uint16_t pm25;
  float uvIndex;
};

WeatherStruct wx;

TemperatureHumidity TempHumiBaro;
bool TempHumiBaroStatus;

Dust dust;
bool dustStatus;

Uv uvIndex;
bool uvStatus;

char sentence[150];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");

  TempHumiBaroStatus = TempHumiBaro.initial();
  dustStatus = dust.initial();
  uvStatus = uvIndex.initial();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (TempHumiBaroStatus == true)
  {
    TempHumiBaro.getTemHumiBaro();

    wx.temperatureC = TempHumiBaro.getTemperatureC();
    wx.humidity = TempHumiBaro.getHumidity();
    wx.pressure = TempHumiBaro.getPressure();
  }

  if (dustStatus == true)
  {
    wx.pm25 = dust.getPm25();
  }

  if (uvStatus == true)
  {
    wx.uvIndex = uvIndex.getUvIndex();
  }

  sprintf(sentence, "{Temp\":\"%d.%d\",\"Humi\":\"%d\",\"Prss\":\"%d\",\"PM25\":\"%u\",\"UvIx\",\"%d.%d\"}", (int)wx.temperatureC, (int)(wx.temperatureC*100)%100, (int)wx.humidity, (int)wx.pressure, wx.pm25, (int)wx.uvIndex, (int)(wx.uvIndex*100)%100);
  Serial.println(sentence);

  delay(1000);
}