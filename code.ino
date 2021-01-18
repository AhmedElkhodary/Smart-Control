//Arduino NodeMCU Blynk LEDS and DHT11
/*
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.
*/


#define BLYNK_PRINT Serial

//Include Library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"


//Auth Token
// You should get Auth Token in the Blynk App.
char auth[] = "";


//Your WiFi credentials
char ssid[] = "";
char pass[] = "";


//DHT11 Sensor Configuration
#define DHTPIN D1              //DHT11 sensor output is connected to PIN D1 on NodeMCU   
#define DHTTYPE DHT11          //DHT sensor type declaration     
DHT dht(DHTPIN, DHTTYPE);  

// Pins Define
#define LEDPin1 D8
#define LEDPin2 D7
#define LEDPin3 D6
#define LEDPin4 D5
#define PUZZER  D4


int trg1;
int trg2;
int trg3;
int trg4;

int LEDState1;
int LEDState2;
int LEDState3;
int LEDState4;

//Initialize the BlynkTimer
BlynkTimer timer;


//Subroutine for sending data from DHT11 sensors to Blynk Server
void sendDHT11SensorVal() {
  //----------------------------------------Get data from sensor and display on serial monitor
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read data from DHT sensor!");
    delay(500);
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("% | Temperature: "));
  Serial.print(t);
  Serial.println(F("C"));
 

  //Sending data from DHT11 sensors to Blynk Server
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  String Hum = String(h);
  String Tem = String(t);
  Blynk.virtualWrite(V0, Hum);
  Blynk.virtualWrite(V1, Tem);

  //check temp if above 30 deg
  if (t > 35){
      digitalWrite(PUZZER, HIGH);
    }
  else{
      digitalWrite(PUZZER, LOW);
    }  

  //Check the status of the LEDS
  if (LEDState1 == 1) {
    Serial.println("LED State1 : ON");
  } else {
    Serial.println("LED State1 : OFF");
  }

  if (LEDState2 == 1) {
    Serial.println("LED State2 : ON");
  } else {
    Serial.println("LED State2 : OFF");
  }

  if (LEDState3 == 1) {
    Serial.println("LED State3 : ON");
  } else {
    Serial.println("LED State3 : OFF");
  }

  if (LEDState4 == 1) {
    Serial.println("LED State4 : ON");
  } else {
    Serial.println("LED State4 : OFF");
  }
}

//===================================================================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass); 
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  dht.begin(); 
  timer.setInterval(5000L, sendDHT11SensorVal); 

  trg1= digitalRead(LEDPin1);
  trg2= digitalRead(LEDPin2);
  trg3= digitalRead(LEDPin3);
  trg4= digitalRead(LEDPin4);
  pinMode(PUZZER, OUTPUT);
}



void loop() {
  Blynk.run();
  timer.run();

  //Check the status of the LEDS
  LEDState1 = digitalRead(LEDPin1);
  if (LEDState1 == 1 && trg1 == 1) {
    Serial.println("LED State1 : ON");
    trg1 = 0;
  }
  if (LEDState1 == 0 && trg1 == 0) {
    Serial.println("LED State1 : OFF");
    trg1 = 1;
  }

  LEDState2 = digitalRead(LEDPin2);
  if (LEDState2 == 1 && trg2 == 1) {
    Serial.println("LED State2 : ON");
    trg2 = 0;
  }
  if (LEDState2 == 0 && trg2 == 0) {
    Serial.println("LED State2 : OFF");
    trg2 = 1;
  }

  LEDState3 = digitalRead(LEDPin3);
  if (LEDState3 == 1 && trg3 == 1) {
    Serial.println("LED State3 : ON");
    trg3 = 0;
  }
  if (LEDState3 == 0 && trg3 == 0) {
    Serial.println("LED State3 : OFF");
    trg3 = 1;
  }

  LEDState4 = digitalRead(LEDPin4);
  if (LEDState4 == 1 && trg4 == 1) {
    Serial.println("LED State4 : ON");
    trg4 = 0;
  }
  if (LEDState4 == 0 && trg4 == 0) {
    Serial.println("LED State4 : OFF");
    trg4 = 1;
  }
}
