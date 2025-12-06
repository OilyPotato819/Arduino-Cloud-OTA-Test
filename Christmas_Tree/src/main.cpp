#include "Arduino_LED_Matrix.h"
#include <ArduinoIoTCloud.h>

struct Snowflake
{
  byte x;
  byte y;
};

KVStore kvStore;
WiFiConnectionHandler ArduinoIoTPreferredConnection;
NetworkConfiguratorClass NetworkConfigurator(ArduinoIoTPreferredConnection);

ArduinoLEDMatrix matrix;
const byte SNOWFLAKE_NUM = 3;
Snowflake snow[SNOWFLAKE_NUM] = {{7, 1}, {11, 6}, {10, 3}};
byte frame[8][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}};

void drawSnowflake(Snowflake &snow);
void updateSnowflake(Snowflake &snow);
void resetSnowflake(Snowflake &snow);

void setup()
{
  NetworkConfigurator.setStorage(kvStore);
  ArduinoCloud.setConfigurator(NetworkConfigurator);
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  randomSeed(analogRead(0));
  matrix.begin();
}

void loop()
{
  ArduinoCloud.update();

  for (int i = 0; i < SNOWFLAKE_NUM; i++)
  {
    drawSnowflake(snow[i]);
  }

  matrix.renderBitmap(frame, 8, 12);

  for (int i = 0; i < SNOWFLAKE_NUM; i++)
  {
    updateSnowflake(snow[i]);
  }

  delay(100);
}

void drawSnowflake(Snowflake &snow)
{
  if (frame[snow.y][snow.x] == 1)
  {
    resetSnowflake(snow);
  }
  frame[snow.y][snow.x] = 1;
}

void updateSnowflake(Snowflake &snow)
{
  frame[snow.y][snow.x] = 0;

  if (snow.x == 0)
  {
    resetSnowflake(snow);
  }
  else
  {
    snow.x--;
  }
}

void resetSnowflake(Snowflake &snow)
{
  snow.x = 11;
  snow.y = random(8);
}
