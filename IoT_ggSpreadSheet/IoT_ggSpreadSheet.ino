/*  Copyright 2018 Electrical Engineering Enterprise Group.
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
  
      http://www.apache.org/licenses/LICENSE-2.0
  
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
  -----------------------------------------------
  Modified ggSpread Sheet for Train the Trainer
  
  by Lecturer Jukrapun Chitpong /Date Mar28-29, 2019

  
  //Up to date
    Mar10, 2018
    Feb25, 2019 +Google Script[GoogleSheet]
    Feb26, 2019 +PZEM
*/
    
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;

//------ Config WiFi ------
const char* SSID1     = "HUAWEI";
const char* PASSWORD1 = "12345678";
const char* SSID2     = "Android";
const char* PASSWORD2 = "12345678";

//------ Config LINE Notify ------
//  YOUR TOKEN FROM LINE Notify
#define LINE_TOKEN "FiXvMZBaEwGuzjNTuT4MsbiYm4OHTJllnxTAwq2Lt7z" 
//#define LINE_TOKEN "ZXVm291s1laNAUcZovvCmH1C6fYkobanrElfZTRTIoT"

//------ Config time ------
#include <time.h>
int timezone = 7;       // Zone +7 for Thailand
char ntp_server1[20] = "time.navy.mi.th";
char ntp_server2[20] = "time.nist.gov";
char ntp_server3[20] = "time.uni.net.th";
int dst = 0;
int Minute, old_Minute, Count, Sencond, old_Sencond, A = 0;

void setup(){
  Serial.begin(115200);  
  Serial.print("Electricl Engineering Enterprise Group\n");
  Serial.println("Google Spread Sheet for Train the Trainer\nby Lecturer Jukrapun Chitpong /Date Mar28-29, 2019");
  
  /* ------------------------------ pinMode Setting ------------------------------
    Serial.print("PINMODE Seting.......");
      for(int i = 0; i < 4; i++){
        pinMode(D[i],INPUT);  
        Serial.print(".");
      }
    Serial.println("Done");*/

  /* --------------- wifiMulti Setting ---------------*/  
  wifiMulti.addAP("AndroidAP", "ifmd0883");
  wifiMulti.addAP(SSID1, PASSWORD1);
  wifiMulti.addAP(SSID2, PASSWORD2);
  wifiMulti.run();
  Serial.println("Connecting Wifi");
  
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".!");
    delay(1000);
  }
  Serial.println("WiFi connected");
  Serial.print("IP address : ");
  Serial.print(WiFi.localIP());
  Serial.println();


  /*---- Config Time ----*/
  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
//  while (!time(nullptr)) {
//   Serial.print(".");
//   delay(500);
//  }  
}

void loop(){
  CheckWiFi_Status();
  NowString();
  //GG_ScriptSheet();
  delay(500);
}

void CheckWiFi_Status(){
  if(wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(500);
  }  
}

String NowString() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);

  String tmpNow = "";
  tmpNow += String(newtime->tm_year + 1900);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mday);
  tmpNow += " ";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec);
  Serial.print(tmpNow);
  Serial.print("\t\n");
  //  return tmpNow;

  Minute = String(newtime->tm_min).toInt();
  Sencond = String(newtime->tm_sec).toInt();
  if(Minute!= old_Minute){
    GG_ScriptSheet();
//    LINEnotify("Some Things");
    old_Minute = Minute;
  }
  return tmpNow;
}

void GG_ScriptSheet(){
  WiFiClientSecure client;
  // YOUR SCRIPT = https://script.google.com/macros/s/AKfycbzPYa_qeKlwdgJi9ZlkGEX-Fnz2t26hh_S-rlotnULN2P2gU_U/exec?&FIELD1=16&FIELD2=18  
  const char* HOST = "script.google.com";
  const char* GScriptId = "AKfycbzPYa_qeKlwdgJi9ZlkGEX-Fnz2t26hh_S-rlotnULN2P2gU_U";  
  
  String url32 = String("/macros/s/") + GScriptId + "/exec?&FIELD1="+(String)A + "&FIELD2="+(String) ++A;
  Serial.print("Client.Connecting...");
  //Serial.println(url32);
  if (client.connect(HOST, 443)) {
    client.println("GET " + String(url32) + " HTTP/1.0"); //HTTP/1.0 OK sent LINEnotify and GoogleSheet
    client.println("Host: " + String(HOST));
    client.println("User-Agent: ESP8266\r\n");
    client.println("Connection: close\r\n\r\n");
    //client.println(true ? "" : "Connection: close\r\n");
    //client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Type: application/json");    
    //2client.println("Connection: close");    
    client.println("Content-Length: " + String(url32.length()));
    client.println();
    //client.println(postData);
    client.print("\r\n\r\n");
    Serial.print("Response...");  
  }
  Serial.println("OK !!!");  
}

void LINEnotify(String message){
  WiFiClientSecure client;

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }else{}

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;

  client.print(req);
  delay(20);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  Serial.println("Send Successfully");
}


