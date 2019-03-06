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
  Modified ggSpread Sheet
  
  by Lecturer:Jukrapun Chitpong

  
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
const char* SSID1     = "YOUR SSID1";
const char* PASSWORD1 = "YOUR PASSWORD1";
const char* SSID2     = "YOUR SSID2";
const char* PASSWORD2 = "YOUR PASSWORD2";

int A = 0;

void setup(){
  Serial.begin(115200);  
  Serial.print("Electricl Engineering Enterprise Group\n");

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

}

void loop(){
  CheckWiFi_Status();
  GG_ScriptSheet();
  delay(10000);
}

void CheckWiFi_Status(){
  if(wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(500);
  }  
}


void GG_ScriptSheet(){
  WiFiClientSecure client;
  // YOUR SCRIPT = https://script.google.com/macros/s/AKfycbzPYa_qeKlwdgJi9ZlkGEX-Fnz2t26hh_S-rlotnULNABCDEFG/exec
  // YOUR GScriptId = "AKfycbzPYa_qeKlwdgJi9ZlkGEX-Fnz2t26hh_S-rlotnULNABCDEFG"
  const char* HOST = "script.google.com";
  const char* GScriptId = "YOUR GScriptId";  
  
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



