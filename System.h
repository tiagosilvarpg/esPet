#ifndef SYSTEM_H
  #define SYSTEM_H
  #include <vector>
  #include <string>
  #include <Preferences.h>
  #include "AV.h"
  
  #define uS_TO_S_FACTOR 1000000
  #define sec_to_days 86400
  #define pin_a 25
  #define pin_b 26
  #define pin_c 27
  #define pressed LOW
  #define DEBUG_INPUT false
  enum gamemode { gamemode_idle, gamemode_sleep, gamemode_stats, gamemode_eat,gamemode_clock};

  using namespace std;
  extern bool btn_a,btn_b,btn_c;
  extern bool btn_a_rel,btn_b_rel,btn_c_rel;
  extern bool btn_a_pre,btn_b_pre,btn_c_pre;
  extern int  hh,mm,ss;
  extern Preferences prefs,data;

  void wakeup();
  void hibernate();
  void resetData(const string& slot)  ;
  int  getInt(const string& key,int def );
  void putInt(const string& key,int value);
  int  getString(const string& key,const string& def);
  void putString(const string& key,const string& value);
  
  void setTime(int digit);
  bool updateTime(); // return true if time changed;
  void initButtons();
  void updateButtons();
  // utils
  string doubleDigits(int value);
#endif