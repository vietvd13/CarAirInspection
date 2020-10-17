//Import libary
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial bluetooth(D6, D5);
//Define Firebase
#define FIREBASE_HOST "https://project-demo-e0f9a.firebaseio.com/"
#define FIREBASE_AUTH "SYE0NrsPDGNsCYKeLAvpCsxhiaQ8Vic6kgkAOYkD"
#define WIFI_SSID "Minh Quan"
#define WIFI_PASSWORD "13102020"
//Define motor
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

String myString;
int MQ = A0;
int dataMQ = 0;
int speeds = 255;
char key;

void setup(){
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(MQ, INPUT);
  //Connect to Wifi
  pinMode(D0, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  //pinMode for Motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop(){
  //Send data MQ to Firebase
  dataMQ = analogRead(MQ);
  myString = String(dataMQ);
  Firebase.setString("MQ Value", myString);
  delay(500);
  
  //Control car
  if(bluetooth.available()){
    key = bluetooth.read();
    Serial.println(key);
  }

  if(key == 'R'){
    goTop();
  } else if(key == 'G'){
    goBack();
  } else if(key == 'Y'){
    goLeft();
  } else if(key == 'B'){
    goRight();
  } else {
    goStop();
  }
}

void goTop(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
}

void goBack(){
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
}

void goLeft(){
  digitalWrite(IN3, HIGH);
}

void goRight(){
  digitalWrite(IN1, HIGH);
}

void goStop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
