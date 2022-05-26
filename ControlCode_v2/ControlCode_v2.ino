#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "mani"
#define WIFI_PASSWORD "12345678"

// Insert Firebase project API Key
#define API_KEY "AIzaSyArWtqhQpSI9ZZVcxOLXg8Mu3SWMyLWl2A"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://control-app-9077c-default-rtdb.firebaseio.com" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;
int det1=12;
int det2=13;
int buzz=25;
int led1=21;
int arr[]={4,2};
void setup(){
  Serial.begin(9600);
  pinMode(det1,INPUT);
  pinMode(det2,INPUT);
  pinMode(buzz,OUTPUT);
  pinMode(led1,OUTPUT);
  for(int i=0;i<2;i++){
    pinMode(arr[i],OUTPUT);
  }
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  //Setting To Initial State
  Firebase.RTDB.setInt(&fbdo, "sensing",1);
 
}
int buzzing=0;
int sensing=1;
void loop(){
     if (Firebase.ready()){
  if (Firebase.RTDB.getInt(&fbdo, "buzzing")) {
      if (fbdo.dataType() == "int") {
        buzzing = fbdo.intData();
      }
    }
    }
        if (Firebase.ready()){
  if (Firebase.RTDB.getInt(&fbdo, "sensing")) {
      if (fbdo.dataType() == "int") {
        sensing = fbdo.intData();
      }
    }
    }
  int out1=digitalRead(det1);
  int out2=digitalRead(det2);
  Serial.println(out1);
  Serial.println(out2);
  for(int i=0;i<2;i++){
    digitalWrite(arr[i],OUTPUT);
  }
  if(buzzing==1){
     digitalWrite(led1,HIGH);
    digitalWrite(buzz,HIGH);
  }
  else{
    digitalWrite(buzz,LOW);
    digitalWrite(led1,LOW);
  }
  if((out1==LOW || out2==LOW) && sensing==1){
     digitalWrite(led1,HIGH);
    digitalWrite(buzz,HIGH);
    Firebase.RTDB.setInt(&fbdo, "buzzing",1);
  }
}
