#include <PD443X.h>
#include <Wire.h>
#include "RTClib.h"
PD443X PD443X(4, 5, 6, 7, 8, 9, 10, 13, 12);
RTC_DS3231 rtc;


int bR  = A1;
int bU  = A2;
int bD  = A3;
int bC  = 2;
void setup() {
  
  pinMode(bR, INPUT);
  pinMode(bU, INPUT);
  pinMode(bD, INPUT);
  pinMode(bC, INPUT);
  rtc.begin();
  PD443X.ClrDisp();
    }

char DisplayHour[2] = {' ', ' '};
char DisplayMinute[2] = {' ', ' '};


void loop() {
  
  DateTime now = rtc.now();
  DisplayHour[0]   = DisplayHour[1];
  DisplayHour[1]   = now.hour();
  DisplayMinute[0] = DisplayMinute[1];
  DisplayMinute[1] = now.minute();
  PD443X.SendByte(DisplayHour[0], 0);
  PD443X.SendByte(DisplayHour[1], 1);
  PD443X.SendByte(DisplayMinute[0], 2);
  PD443X.SendByte(DisplayMinute[1], 3);
 
     if(now.second() == 59){
        DispTransition(125,125,0);
        }
      UpdateTime();
     
}

void DispTransition(int in,int out,int Waitbetw){
        PD443X.SendByte('_',3);
        delay(in);
        PD443X.SendByte(' ',3);
        PD443X.SendByte('_',2);
        delay(in);
        PD443X.SendByte(' ',2);
        PD443X.SendByte('_',1);
        delay(in);
        PD443X.SendByte(' ',1);
        PD443X.SendByte('_',0);
        delay(in);
        PD443X.SendByte(' ',0);
        delay(Waitbetw);
        PD443X.SendByte('_',0);
        delay(out);
        PD443X.SendByte(DisplayHour[0],0);
        PD443X.SendByte('_',1);
        delay(out);
        PD443X.SendByte(DisplayHour[1],1);
        PD443X.SendByte('_',2);
        delay(out);
        PD443X.SendByte(DisplayMinute[0],2);
        PD443X.SendByte('_',3);
        delay(out);
        PD443X.SendByte(DisplayMinute[1],3);
}

void UpdateTime(){
DateTime now = rtc.now();
int UTyear = now.year();
int UTmonth = now.month();
int UTday = now.day();
int UThour = now.hour();
int UTminute = now.minute();
int UTsecond = now.second();
int Syear = 0;
int Smonth = 0;
int Sday = 0;
int Shour = 0;
int Sminute = 0;
int Ssecond = 0;
int pU =0;
int pD =0;
int pR =0;
int pC =0;
char Disyear[4] ={' ',' ',' ',' '};
char Dismonth[2] ={' ',' '};
char Disday[2] ={' ',' '};
char Dishour[2] ={' ',' '};
char Disminute[2] ={' ',' '};
char Dissec[2]    ={' ',' '};
if(bC == HIGH){
   pC=pC+1;
}
if (pC == 1){
    pR=pR+1;
}
if (pR == 1){
    if(bU == HIGH){
       PD443X.ClrDisp();
       UTyear=UTyear+1;
       Syear=UTyear;
       Disyear[0]=Disyear[1];
       Disyear[1]=Disyear[2];
       Disyear[2]=Disyear[3];
       Disyear[3]=Syear;
       PD443X.SendByte(Disyear[0],0);
       PD443X.SendByte(Disyear[1],1);
       PD443X.SendByte(Disyear[2],2);
       PD443X.SendByte(Disyear[3],3);
    }
    if(bD == HIGH){
       PD443X.ClrDisp();
       UTyear=UTyear-1;
       Syear=UTyear;
       Disyear[0]=Disyear[1];
       Disyear[1]=Disyear[2];
       Disyear[2]=Disyear[3];
       Disyear[3]=Syear;
       PD443X.SendByte(Disyear[0],0);
       PD443X.SendByte(Disyear[1],1);
       PD443X.SendByte(Disyear[2],2);
       PD443X.SendByte(Disyear[3],3);
    }
if (bR == HIGH){
    pR=pR+1;
}
if (pR ==2){
    if(bU == HIGH){
       PD443X.ClrDisp();
       UTmonth=UTmonth+1;
       Smonth=UTmonth;
       Dismonth[0]=Dismonth[1];
       Dismonth[1]=Smonth;
       PD443X.SendByte(Disyear[0],2);
       PD443X.SendByte(Dismonth[1],3);
    }
    if(bD == HIGH){
       PD443X.ClrDisp();
       UTmonth=UTmonth-1;
       Smonth=UTmonth;
       Dismonth[0]=Dismonth[1];
       Dismonth[1]=Smonth;
       PD443X.SendByte(Dismonth[0],2);
       PD443X.SendByte(Dismonth[1],3);
  }
    if(Smonth >12){
       Smonth=1;
    }else if(Smonth <1){
       Smonth=12;
    }else {}
if (pR == 3){
    if(bU == HIGH){
       PD443X.ClrDisp();
       UTday=UTday+1;
       Sday=UTday;
       Disday[0]=Disday[1];
       Disday[1]=Sday;
       PD443X.SendByte(Disday[0],2);
       PD443X.SendByte(Disday[1],3);
    }
    if(bD == HIGH){
       PD443X.ClrDisp();
       UTday=UTday-1;
       Sday=UTday;
       Disday[0]=Disday[1];
       Disday[1]=Sday;
       PD443X.SendByte(Disday[0],2);
       PD443X.SendByte(Disday[1],3);
    }
     if(Smonth == 4 || 6 || 9|| 11){
       if (Sday >30){
           Sday=1;
       }else if(Smonth < 1){
           Sday=30;
       }
      }else if (Smonth == 1 || 3 || 5 || 7 || 8 || 10 || 12){
       if (Sday >31){
           Sday=1;
       }else if (Sday <1){
           Sday=31;
       }
      }else if (Smonth == 2){
       if (Syear%4 == 0){
          if (Sday >29){
             Sday=1;
          }else if (Sday <1){
              Sday=29;
          }
      }else if(Syear%4 != 0){
          if (Sday >28){
             Sday=1;
          }else if (Sday <1){
             Sday=28;
          }
      }
if (pR == 4){
    if(bU == HIGH){
      PD443X.ClrDisp();
      UThour=UThour+1;
      Shour=UThour;
      Dishour[0]=Dishour[1];
      Dishour[1]=Shour;
      PD443X.SendByte(Dishour[0],2);
      PD443X.SendByte(Dishour[1],3);
    }
    if(bD == HIGH){
      PD443X.ClrDisp();
      UThour=UThour-1;
      Shour=UThour;
      Dishour[0]=Dishour[1];
      Dishour[1]=Shour;
      PD443X.SendByte(Dishour[0],2);
      PD443X.SendByte(Dishour[1],3);
    }
      if(Shour >24){
        Shour=0;
      }else if (Shour <0){
        Shour=24;
      }
if (pR == 5){
    if(bU == HIGH){
      PD443X.ClrDisp();
      UTminute=UTminute+1;
      Sminute=UTminute;
      Disminute[0]=Disminute[1];
      Disminute[1]=Sminute;
      PD443X.SendByte(Disminute[0],2);
      PD443X.SendByte(Disminute[1],3);
    }
    if(bD == HIGH){
      PD443X.ClrDisp();
      UTminute=UTminute-1;
      Sminute=UTminute;
      Disminute[0]=Disminute[1];
      Disminute[1]=Sminute;
      PD443X.SendByte(Disminute[0],2);
      PD443X.SendByte(Disminute[1],3);
    }
      if(Sminute>59){
        Sminute=0;
    }else if (Sminute<0){
        Sminute=59;
    }
if (pR == 6){
    if(bU == HIGH){
       PD443X.ClrDisp();
       UTsecond=UTsecond+1;
       Ssecond=UTsecond;
       Dissec[0]=Dissec[1];
       Dissec[1]=Ssecond;
       PD443X.SendByte(Dissec[0],2);
       PD443X.SendByte(Dissec[1],3);
    }
    if(bD == HIGH){
       PD443X.ClrDisp();
       UTsecond=UTsecond-1;
       Ssecond=UTsecond;
       Dissec[0]=Dissec[1];
       Dissec[1]=Ssecond;
       PD443X.SendByte(Dissec[0],2);
       PD443X.SendByte(Dissec[1],3);
    }
      if(Ssecond >59){
         Ssecond=0;
    }else if (Ssecond <1){
         Ssecond=59;
    }
if (pC == 2){
pC=0;
rtc.adjust(DateTime(Syear, Smonth, Sday, Shour, Sminute, Ssecond));
}
}}}}}}}
    pR=0;
    pC=0;
    pU=0;
    pD=0;
    
    }
