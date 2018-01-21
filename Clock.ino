#include <PD443X.h>
#include <Wire.h>
#include "RTClib.h"
PD443X PD443X(4, 5, 6, 7, 8, 9, 10, 13, 12);
int Bu = 2;
int Button = 1;
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void setup() {
  pinMode(Bu, INPUT);
  rtc.begin();
  PD443X.ClrDisp();

}

char DisplayHour[2] = {' ', ' '};
char DisplayMinute[2] = {' ', ' '};
char DOTW[3] = {' ', ' ', ' '};
char Days[2] = {' ', ' '};
char Months[2] = {' ', ' '};
char Years[4] = {' ', ' ', ' ', ' '};
void loop() {

  DateTime now = rtc.now();
  if (Bu == HIGH) {
    Button = Button + 1;
    DisplayHour[0]   = DisplayHour[1];
    DisplayHour[1]   = now.hour();
    DisplayMinute[0] = DisplayMinute[1];
    DisplayMinute[1] = now.minute();
    PD443X.SendByte(DisplayHour[0], 0);
    PD443X.SendByte(DisplayHour[1], 1);
    PD443X.SendByte(DisplayMinute[0], 2);
    PD443X.SendByte(DisplayMinute[1], 3);
    Button = Button + 1;
  } else if (Button == 1) {
    Button = Button + 1;
    DOTW[0] = DOTW[1];
    DOTW[1] = DOTW[2];
    DOTW[2] = daysOfTheWeek[now.dayOfTheWeek()];
    PD443X.SendByte(DOTW[0], 0);
    PD443X.SendByte(DOTW[1], 1);
    PD443X.SendByte(DOTW[2], 2);
  } else if (Button == 2) {
    Button = Button + 1;
    Days[0] = Days[1];
    Days[1] = now.day();
  } else if (Button == 3) {
    Button = Button + 1;
    Months[0] = Months[1];
    Months[1] = now.month();
  } else if (Button == 4) {
    Years[0] = Years[1];
    Years[1] = Years[2];
    Years[2] = Years[3];
    Years[3] = now.year();
    Button = 0;
  }

  if (now.second() == 59) {
    Transition(125, 125, 0);
  }

}

void Transition(int in, int out, int Waitbetw) {
  PD443X.SendByte('_', 3);
  delay(in);
  PD443X.SendByte(' ', 3);
  PD443X.SendByte('_', 2);
  delay(in);
  PD443X.SendByte(' ', 2);
  PD443X.SendByte('_', 1);
  delay(in);
  PD443X.SendByte(' ', 1);
  PD443X.SendByte('_', 0);
  delay(in);
  PD443X.SendByte(' ', 0);
  delay(Waitbetw);
  PD443X.SendByte('_', 0);
  delay(out);
  PD443X.SendByte(DisplayHour[0], 0);
  PD443X.SendByte('_', 1);
  delay(out);
  PD443X.SendByte(DisplayHour[1], 1);
  PD443X.SendByte('_', 2);
  delay(out);
  PD443X.SendByte(DisplayMinute[0], 2);
  PD443X.SendByte('_', 3);
  delay(out);
  PD443X.SendByte(DisplayMinute[1], 3);
}
