
typedef struct
{
  float temperatureC;
  float pressure;
  float humidity;
} TemperatureHumidityStruct, *TemperatureHumidityPtr;

class TemperatureHumidity
{
public:
  bool initial();
  void getTemHumiBaro();
  float getTemperatureC();
  float getPressure();
  float getHumidity();
};
