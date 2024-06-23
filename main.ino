#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "mp3tf16p.h"
#include "RTClib.h"
// #include <DHT.h>
// #include <DHT_U.h>
// #define DHT_PIN 8 

// DHT dht(DHT_PIN, DHT22);

RTC_DS1307 rtc;

LiquidCrystal_I2C myLCD(0x27, 16, 2);

MP3Player mp3(10, 11); 

char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char timeArr[][6] = {"18:21", "18:22", "18:23", "18:24", "18:25", "18:26", "18:27"};

byte customChar[] = {
  B01010,
  B10100,
  B10000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000
};

String lastTime;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  myLCD.init();
  // dht.begin();
  myLCD.backlight();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  mp3.initialize();
}

void loop() {

  DateTime now = rtc.now();

  displayTime();

    for(int i = 0; i < 7; i++){ 

      String hours;
      String minutes;
      if(now.hour() < 10) {
        hours = "0" + String(now.hour());
      } else {
        hours = now.hour();
      }
      if(now.minute() < 10) {
        minutes = "0" + String(now.minute());
      } else {
        minutes = now.minute();
      }
      String dro = hours + ":" + minutes;


        if(String(timeArr[i]) == dro) {
          if(dro == timeArr[0] && String(timeArr[0]) != lastTime){
            play_and_display("darcha 5 wuti", 1);
            // myLCD.clear();
            // myLCD.print("matematika");
            // mp3.playTrackNumber(1, 30);
            // delay(5000);
            // Serial.println("zd");
            lastTime = String(timeArr[0]); 
          } 
          else if(dro == timeArr[1] && String(timeArr[1]) != lastTime){
            play_and_display("darcha 5 wuti", 0);
            // Serial.print(lastTime);
            lastTime = String(timeArr[1]); 
            // Serial.print("    ");
            // Serial.println(lastTime);
          }
          else if(dro == timeArr[2] && String(timeArr[2]) != lastTime){
            play_and_display("qartuli", 3);
            lastTime = String(timeArr[2]); 
          }
          else if(dro == timeArr[3] && String(timeArr[3]) != lastTime){
            play_and_display("musika", 4);
            lastTime = String(timeArr[3]); 
          }
          else if(dro == timeArr[4] && String(timeArr[4]) != lastTime){
            play_and_display("biologia", 5);
            lastTime = String(timeArr[4]); 
          }
          else if(dro == timeArr[5] && String(timeArr[5]) != lastTime){
            play_and_display("qimia", 6);
            lastTime = String(timeArr[5]); 
          }
          else if(dro == timeArr[6] && String(timeArr[6]) != lastTime){
            play_and_display("fizika", 7);
            lastTime = String(timeArr[6]); 
          } 
        }
      else {
        continue;
      }
      myLCD.clear();
    }  

}

void displayTH(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  myLCD.createChar(0, customChar);
  myLCD.setCursor(0, 1);
  myLCD.print(0);
  delay(2000);
}


void play_and_display(String x, int y){
  myLCD.clear();
  myLCD.print(x);
  Serial.println("axla gawedavs mara mushaa");
  mp3.playTrackNumber(y, 30);
  delay(5000);
}

void displayTime() {
  DateTime now = rtc.now();
  myLCD.setCursor(0, 0);
  myLCD.print(now.year());
  myLCD.setCursor(4, 0);
  myLCD.print("/");
  myLCD.setCursor(5, 0);
  toDigits(now.month(), 6, 0);
  myLCD.setCursor(7, 0);
  myLCD.print("/");
  myLCD.setCursor(8,0);
  toDigits(now.day(), 9, 0);
  myLCD.setCursor(11, 0);

  myLCD.print(daysOfTheWeek[now.dayOfTheWeek()]);
  
  myLCD.setCursor(0, 1);

  // displayTH();

  // myLCD.setCursor(0,1);

  toDigits(now.hour(), 1, 1);
  myLCD.setCursor(2, 1);

  myLCD.print(":");
  myLCD.setCursor(3, 1);

  toDigits(now.minute(), 4, 1);
  myLCD.setCursor(5, 1);

  myLCD.print(":");
  myLCD.setCursor(6, 1);

  toDigits(now.second(), 7, 1);
  myLCD.setCursor(0,0);
  delay(1000);

}


void toDigits(int x, int y, int z) {
  if(x < 10) {
    myLCD.print(0);
    myLCD.setCursor(y, z);
    myLCD.print(x);
  }
  else {
    myLCD.print(x);
  }
}
