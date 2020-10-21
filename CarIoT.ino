//Import libary
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial bluetooth(D6, D5);
//Define Firebase
#define FIREBASE_HOST "project-demo-e0f9a.firebaseio.com"
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
  //pinMode MQ
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

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop(){
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
  } else if(key == 'L'){
    goTopgg();
  } else if(key == 'X'){
    goBackgg();
  } else if(key == 'T'){
    goLeftgg();
  } else if(key == 'P'){
    goRightgg();
  } else {
    goStop();
  }
  
  //Send data MQ to Firebase
  sendDataMQ();
}
// Run when command is Top
void goTop(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
}
// Run when command is Back
void goBack(){
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
}
// Run when command is Left
void goLeft(){
  digitalWrite(IN3, HIGH);
}
// Run when command is Right
void goRight(){
  digitalWrite(IN1, HIGH);
}
// Run when key is not equals with command
void goStop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  key = 's';
}
// Run when Google A -> call Top
void goTopgg() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
  delay(1000);
  goStop();
}
// Run when Google A -> call Back
void goBackgg() {
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  delay(1000);
  goStop();
}
// Run when Google A -> call Left
void goLeftgg() {
  digitalWrite(IN3, HIGH);
  delay(500);
  goStop();
}
// Run when Google A -> call Right
void goRightgg() {
  digitalWrite(IN1, HIGH);
  delay(500);
  goStop();
}
// Send data read in MQ to Firebase
void sendDataMQ(){
  dataMQ = analogRead(MQ);
  myString = String(dataMQ);
  Serial.print(myString);
  Firebase.setString("MQ Value", myString);
}
