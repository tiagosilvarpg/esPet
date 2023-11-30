#include <TFT_eSPI.h>
#include <Arduino.h>
#include <vector>
#include <string>
#include "Av.h"
#include "Tileset.h"
TFT_eSPI tft = TFT_eSPI();

void screenInit(){
  backlight(3);
  displayOn(true);
}
void displayOn(bool on){
  pinMode(DISPLAY_PIN,OUTPUT);
  digitalWrite(DISPLAY_PIN,on?HIGH:LOW);
  delay(10);
  tft.setRotation(SCREEN_ROTATION);
  tft.init();
}
void backlight(int power){
  int scale = 64;
  int resolution = 10;
  int frequency = 1000;

  ledcAttachPin(LED_PIN, LED_CHANNEL);
  ledcSetup(LED_CHANNEL, frequency, resolution);
  ledcWrite(LED_CHANNEL, power*scale);
}
void drawText(const std::string& text,int x,int y){
  drawText(text,x,y,TFT_BLACK,TFT_WHITE);
}
void drawText(const std::string& text,int x,int y,int colora, int colorb){
  tft.setTextColor(colora,colorb);
  tft.drawString(text.c_str(),x,y);
}
void fillRect(int x,int y, int w,int h,int color){
  tft.fillRect(x,y,w,h,color);
}
void playSong(int song)
{
  if (song==1) { playNote(NOTE_C,250);  playNote(NOTE_G,250);  playNote(NOTE_G,250);}

  muteSong();
}
void playNote(note_t note,int duration){
  ledcAttachPin(BUZZ_PIN, BUZZ_CHANNEL);
  ledcWriteNote(BUZZ_CHANNEL,note,4);
  delay(duration+10);
  muteSong();
}
void muteSong(){
  ledcDetachPin(BUZZ_PIN);
}
void textFormat(int DATUM,int textSize){
  tft.setTextSize(textSize);
  tft.setTextDatum(DATUM);
}
void drawTile(int x,int y,int row, int col, bool flip){
  for (int l=0;l<32;l++)
  for (int c=0;c<32;c++)
  {
    int index = l*(tileset_w + c);
    tft.fillRect(x,y,tileset_scale,tileset_scale,tileset[index]);
  }
}
/*
int getSpriteLenght();
std::vector<int> getSprite();
std::vector<int> getSprite(int col,int row);
void drawText(const std::string& text,int x,int y)
void drawRect(int x,int y, int w,int h,std::vector<int> background);
*/