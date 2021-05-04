#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#define CLAW_PIN 5 //D1
#define ELBOW_PIN 4 //D2
#define BASE_PIN 0 //D3

#define CLAW_MAX 50
#define ELBOW_MAX 90
#define BASE_MAX 180

#define DELAY 20

int clawPos;
int elbowPos;
int basePos;

const char * wifi_ssid = "RoboticArm"; //"Dialog 4G F54";
const char * wifi_password = "robotikka"; //"B@nchi123456";
const char * username = "user";
const char * password = "letmein";

ESP8266WebServer server(80);
Servo sClaw, sElbow, sBase;

void handleNotFound() {
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleAPI() {
  if (!server.authenticate(username, password)) {
    return server.requestAuthentication(DIGEST_AUTH);
  }

  server.send(200, "text/plain");
  
  for (uint8_t i = 0; i < server.args(); i++) {
      Serial.println(server.argName(i) + ":" + server.arg(i));
      
      if (server.argName(i) == "Claw") {
        ClawRot(server.arg(i).toInt());
      }
      else if(server.argName(i) == "Elbow"){
        ElbowRot(server.arg(i).toInt());
      }
      else if(server.argName(i) == "Base"){
        BaseRot(server.arg(i).toInt());
      }
  }
}

void handleRoot() {
  server.send(200, "text/html", "<html><body><h3>/api</h3></body></html>");
}

void ClawRot(int pos){
  if(pos > CLAW_MAX) pos = CLAW_MAX;
  else if(pos < 0) pos = 0;

  if(pos > clawPos){
    for(int i = clawPos; i <= pos; i++){
        sClaw.write(i);
        delay(DELAY);
    }
  }
  else if(pos < clawPos){
    for(int i = clawPos; i >= pos; i--){
        sClaw.write(i);
        delay(DELAY);
    }
  }
  clawPos=pos;
}

void ElbowRot(int pos){
  if(pos > ELBOW_MAX) pos = ELBOW_MAX;
  else if(pos < 0) pos = 0;

  if(pos > elbowPos){
    for(int i = elbowPos; i <= pos; i++){
        sElbow.write(i);
        delay(DELAY);
    }
  }
  else if(pos < elbowPos){
    for(int i = elbowPos; i >= pos; i--){
        sElbow.write(i);
        delay(DELAY);
    }
  }
  elbowPos=pos;
}

void BaseRot(int pos){
  if(pos > BASE_MAX) pos = BASE_MAX;
  else if(pos < 0) pos = 0;

  if(pos > basePos){
    for(int i = basePos; i <= pos; i++){
        sBase.write(i);
        delay(DELAY);
    }
  }
  else if(pos < basePos){
    for(int i = basePos; i >= pos; i--){
        sBase.write(i);
        delay(DELAY);
    }
  }
  basePos=pos;
}

void resetAll(){
  clawPos = 0;
  elbowPos = 0;
  basePos = 0;
  
  sClaw.write(clawPos);
}

void setup() {
  Serial.begin(115200);

  sClaw.attach(CLAW_PIN);
  sElbow.attach(ELBOW_PIN);
  sBase.attach(BASE_PIN);
  
  resetAll();

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);

  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting to Wifi failed. Rebooting...");
    delay(1000);
    ESP.restart();
  }

  ArduinoOTA.begin();

  server.on("/", handleRoot);
  server.on("/api", handleAPI);
  server.onNotFound(handleNotFound);

  server.begin();

  Serial.print("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}
