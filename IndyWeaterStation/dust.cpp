#include <dust.h>
#include <SoftwareSerial.h>

SoftwareSerial pmsSerial(10, 11);
struct pms5003data data;
struct dustStruct dust_data;


bool Dust::initial()
{
    pmsSerial.begin(9600);
    delay(1000);
    uint32_t start = millis();
    do
    {
        if (readPMSdata(&pmsSerial) == true)
        {
            return true;
        }
    } while (millis() - start < 200);
    
    return false;
}

uint16_t Dust::getPm25()
{
    savePMSdata(); // make sure data evailable every request by save previous data
    return dust_data.pm25;
}

void Dust::savePMSdata()
{
    uint32_t start = millis();
    do
    {
        if (readPMSdata(&pmsSerial) == true)
        {
            dust_data.pm25 = data.pm25_env;
            return;
        }
    } while (millis() - start < 200);
}

bool Dust::readPMSdata(Stream *s)
{
    if (!s->available())
    {
        return false;
    }

    // Read a byte at a time until we get to the special '0x42' start-byte
    if (s->peek() != 0x42)
    {
        s->read();
        return false;
    }

    // Now read all 32 bytes
    if (s->available() < 32)
    {
        return false;
    }

    uint8_t buffer[32];
    uint16_t sum = 0;
    s->readBytes(buffer, 32);

    // get checksum ready
    for (uint8_t i = 0; i < 30; i++)
    {
        sum += buffer[i];
    }

    /* debugging
  for (uint8_t i=2; i<32; i++) {
    Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
  }
  Serial.println();
  */

    // The data comes in endian'd, this solves it so it works on all platforms
    uint16_t buffer_u16[15];
    for (uint8_t i = 0; i < 15; i++)
    {
        buffer_u16[i] = buffer[2 + i * 2 + 1];
        buffer_u16[i] += (buffer[2 + i * 2] << 8);
    }

    // put it into a nice struct :)
    memcpy((void *)&data, (void *)buffer_u16, 30);

    if (sum != data.checksum)
    {
        return false;
    }
    // success!
    return true;
}
