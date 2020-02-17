#include <uv.h>
#include <Adafruit_SI1145.h>

Adafruit_SI1145 uv = Adafruit_SI1145();


bool Uv::initial()
{
    return uv.begin();
}

float Uv::getUvIndex()
{
    return uv.readUV()/100.0;
}