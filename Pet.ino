#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Av.h"
#include "System.h"

void setup()
{
  Serial.begin(115200);
  initButtons();
  delay(10);
  screenInit();
  playSong(1);
}
void loop()
{
  //textFormat(CC_DATUM,4);
  //fillRect(0,0,240,240,TFT_GREEN);
  //drawText("Hello world",120,120);
  //drawTile(10,10,0,0,false);
  delay(100);
}