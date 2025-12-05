#include <Arduino.h>
#include "Arduino_LED_Matrix.h"

struct Snowflake
{
  byte x;
  byte y;
};

ArduinoLEDMatrix matrix;
Snowflake snow1 = {7, 1};
Snowflake snow2 = {11, 6};
byte frame[8][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}};

void setup()
{
  matrix.begin();
}

void drawSnowflake(Snowflake &snow);
void updateSnowflake(Snowflake &snow);
void resetSnowflake(Snowflake &snow);

void loop()
{
  drawSnowflake(snow1);
  drawSnowflake(snow2);
  matrix.renderBitmap(frame, 8, 12);
  updateSnowflake(snow1);
  updateSnowflake(snow2);
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