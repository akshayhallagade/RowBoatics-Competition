
/**************************************************************
   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   You can easily build graphic interfaces for all your
   projects by simply dragging and dropping widgets.

     Downloads, docs, tutorials: http://www.blynk.cc
     Blynk community:            http://community.blynk.cc
     Social networks:            http://www.fb.com/blynkapp
                                 http://twitter.com/blynk_app

   Blynk library is licensed under MIT license
   This example code is in public domain.

 **************************************************************
   This example runs directly on ESP8266 chip.

   You need to install this for ESP8266 development:
     https://github.com/esp8266/Arduino

   Please be sure to select the right ESP8266 module
   in the Tools -> Board menu!

   Change WiFi ssid, pass, and Blynk auth token to run :)

 **************************************************************/
#define ENA   14          // Enable/speed motors Right        GPIO14(D5)
#define ENB   12          // Enable/speed motors Left         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
Servo servo;
String command;             //String to store app command state.
int minRange = 312;
int maxRange = 712;
int minSpeed = 450;
int maxSpeed = 1270;
int noSpeed = 0;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "deYyb4d4gVs4YI9HhRZ9lUMdycJqphj-";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Akhil";
char pass[] = "987654321";
void moveControl1(int x, int y)
{

  if(x >= maxRange) //y >= maxRange && x >= minRange && x <= maxRange
  {
    digitalWrite(IN_1,HIGH); 
    digitalWrite(IN_2,LOW);
    analogWrite(ENA,maxSpeed);
  }
  
  // neutral zone
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
     digitalWrite(IN_1,LOW); 
    digitalWrite(IN_2,LOW);
    analogWrite(ENA,noSpeed);
  }

 // move back
  else if(x <= minRange) //y <= minRange && x >= minRange && x <= maxRange
  {
    digitalWrite(IN_1,LOW);
    digitalWrite(IN_2,HIGH);
   analogWrite(ENA,maxSpeed);
  }
}
void moveControl2(int a, int b){
   // move forward right
   if(b >= maxRange && a >= minRange && a <= maxRange)   //a >= maxRange
  {
    servo.write(0);
  }
  // move forward left
  else if(b <= minRange && a>= minRange && a<= maxRange) // a <= minRange
  {
    servo.write(100);
  }
   // neutral zone
  else if(b < maxRange && b > minRange && a < maxRange && a > minRange) 
   { servo.write(55);
  }
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  Serial.begin(115200);
  servo.attach(D2); //D2
  servo.write(0);
}

void loop()
{
  Blynk.run();
}
BLYNK_WRITE(V0)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
 /*
  Serial.print("x value is: ");
  Serial.println(x);
  Serial.print("y value is: ");
  Serial.println(y);
 */
  moveControl1(x,y);
}
/* 
BLYNK_WRITE(V4) {
  servo.write(45);
}
BLYNK_WRITE(V3) {
  servo.write(0);
}
BLYNK_WRITE(V2) {
  servo.write(90);
}*/

BLYNK_WRITE(V5) {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);
}
BLYNK_WRITE(V6){
  int a = param[0].asInt();
  int b = param[1].asInt(); 
  moveControl2(a,b);
}
