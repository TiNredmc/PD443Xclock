#include <PD443X.h>
#include <Wire.h>
#include "RTClib.h"
PD443X PD443X(4, 5, 6, 7, 8, 9, 10, 13, 12);
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup() {
  rtc.begin();
  PD443X.ClrDisp();
}
char DisplayHour[2] = {' ', ' '};
char DisplayMinute[2] = {' ', ' '};
int yea  = 0;
int mon  = 0;
int days = 0;
void loop() {
  DateTime now = rtc.now();
  DisplayHour[0]   = DisplayHour[1];
  DisplayHour[1]   = now.hour();
  DisplayMinute[0] = DisplayMinute[1];
  DisplayMinute[1] = now.minute();
  days = now.day();
  mon  = now.month();
  yea  = now.year();
  String dayS = String(days);
  String monS = String(mon);
  String yeaS = String(yea);
  PD443X.SendByte(DisplayHour[0], 0);
  PD443X.SendByte(DisplayHour[1], 1);
  PD443X.SendByte(DisplayMinute[0], 2);
  PD443X.SendByte(DisplayMinute[1], 3);
  delay(250);
  PD443X.SendStringScroll(daysOfTheWeek[now.dayOfTheWeek()], 120);
  PD443X.SendStringScroll(dayS, 120);
  PD443X.SendStringScroll(monS, 120);
  PD443X.SendStringScroll(yeaS, 120);
}

