#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Av.h"
#include "System.h"

void setup(){
  Serial.begin(115200);
  initButtons();
  screenInit();
}
void loop(){
  textFormat(CC_DATUM,4);
  fillRect(0,0,240,240,TFT_RED);
  drawText("Hello world",120,120);
  //drawTile(10,10,0,0,false);
  while (true)
  {
    updateButtons();
    if (btn_a)
      playNote(NOTE_A,250);
    if (btn_b)
      playNote(NOTE_C,250);
    if (btn_c)
      playNote(NOTE_G,250);
  }
  delay(1);
}