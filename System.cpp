#include <SPI.h>
#include <Arduino.h>
#include <map>
#include <string>
#include <vector>
#include <esp32-hal.h>
#include <esp_sleep.h>
#include <Preferences.h>
#include "AV.h"
#include "System.h"

Preferences prefs;
Preferences data;
using namespace std;

RTC_DATA_ATTR unsigned long int targetTime;
RTC_DATA_ATTR int bootCount;

int hh,mm,ss;

bool btn_a,btn_b,btn_c;
bool btn_a_rel,btn_b_rel,btn_c_rel;
bool btn_a_pre,btn_b_pre,btn_c_pre;

// methods
void initButtons()
{
  int INPUT_PULLMODE = pressed==HIGH?INPUT_PULLDOWN:INPUT_PULLUP;
  pinMode( pin_a, INPUT_PULLMODE);
  pinMode( pin_b, INPUT_PULLMODE);
  pinMode( pin_c, INPUT_PULLMODE);
}
void updateButtons(){
  btn_a = (digitalRead(pin_a)==pressed);
  btn_b = (digitalRead(pin_b)==pressed);
  btn_c = (digitalRead(pin_c)==pressed);

  btn_a_pre = btn_a && btn_a_rel;
  btn_b_pre = btn_b && btn_b_rel;
  btn_c_pre = btn_c && btn_c_rel;

  btn_a_rel = (!btn_a);
  btn_b_rel = (!btn_b);
  btn_c_rel = (!btn_c);
  if (DEBUG_INPUT)
  {
    Serial.print("down[");
    Serial.print(btn_a);
    Serial.print(btn_b);
    Serial.print(btn_c);
    Serial.print("] pressed[");
    Serial.print(btn_a_pre);
    Serial.print(btn_b_pre);
    Serial.print(btn_c_pre);
    Serial.print("] released[");
    Serial.print(btn_a_rel);
    Serial.print(btn_b_rel);
    Serial.print(btn_c_rel);
    Serial.println("]");
  }
}
/**
int global_get_int(const string& key,int def){
  return preferences.getInt(key.c_str(),0);
}
void global_set_int(const string& key,int value){
  preferences.putInt(key.c_str(),value);
}
void esp_wake_deep_sleep(){
  Serial.print("millis: ");
  Serial.println(millis());
}
void resetData(const string& slot){
  const char* _slot = slot.c_str();
  data.begin(_slot,false);
  data.putInt("form",0);
  data.putInt("days",0);
  data.putInt("hunger",1);
  data.putInt("secondsAlive",0);
  data.putInt("weight",1);
  data.putInt("power",1);
  
  Serial.println(_slot);
  Serial.println(" restored to default");
}
void wakeup(){
  preferences.begin("data",false);
  data.begin("slot_0",false);
  screenInit();  
  targetTime=millis()+1000;
  hh=preferences.getInt("hh",0);
  mm=preferences.getInt("mm",0);
  ss=preferences.getInt("ss",0);
  
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause(); 
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0)
  {
    Serial.println("Wakeup caused by external signal using RTC_IO");
  }
  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void hibernate(){
  //esp_sleep_enable_timer_wakeup(20 * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_27,0);
  esp_light_sleep_start();
}



void setTime(int digit){
  if (digit==1)
    hh=(hh+1)%24;
  else if (digit==2)
    mm=(mm+1)%60;
  else if (digit==3)
    ss=(ss+1)%60;
  else
    return;
}
string doubleDigits(int value){
  if (value<10)
    return '0'+to_string(value);
  else return to_string(value);
}
bool updateTime(){
  int elapsedSeconds = 0;
  int secondsAlive = preferences.getInt("secondsAlive",0);
  while (targetTime<millis()){
    elapsedSeconds += 1;
    targetTime+=1000;
    secondsAlive+=1;
    ss+=1;
    if (ss==60){
      ss=0;
      mm+=1;
    }
    if (mm==60){
      mm=0;
      hh+=1;
    }
    if (hh==24){
      hh=0;
    }
  }
  if (elapsedSeconds>0){
    preferences.putInt("hh",hh);
    preferences.putInt("mm",mm);
    preferences.putInt("ss",ss);
    preferences.putInt("secondsAlive",secondsAlive);
  }
  if (elapsedSeconds>1){
    Serial.print(elapsedSeconds);
    Serial.println(" seconds has passed");
  }
  return elapsedSeconds>0;
}
*/