#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <string.h>

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

const char * wifi_ssid = "Dialog 4G F54";
const char * wifi_password = "B@nchi123456";
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
  const char s[2] = "\n";
  char * token;

  char * cstr = new char[server.arg(0).length() + 1];
  strcpy(cstr, server.arg(0).c_str());

  token = strtok(cstr, s);
  while (token != NULL) {
    StaticJsonBuffer < 200 > jsonBuffer;
    JsonObject & node = jsonBuffer.parseObject(token);

    int k1 = node["Claw"];
    int k2 = node["Elbow"];
    int k3 = node["Base"];
    if (node.containsKey("Delay")) {
      Serial.println("Automatic");
      Serial.println(k1);
      Serial.println(k2);
      Serial.println(k3);
      int dd = node["Delay"];
      Serial.println(dd);

      manual(node["Claw"], node["Elbow"], node["Base"]);
      delay(node["Delay"]);
    } else {
      Serial.println("Manual");
      Serial.println(k1);
      Serial.println(k2);
      Serial.println(k3);

      manual(node["Claw"], node["Elbow"], node["Base"]);
      delay(DELAY);
    }
    token = strtok(NULL, s);
  }

  //check if json is post or get. If get make to post
  // make get request to getPos()

  //manual(Json Object)
  //auto(Json array) <- call resetAll before executing JSON (Steps)
  //getPos(??) <- get values before starting the main activity
}

void manual(int clawValue, int elbowValue, int baseValue) {
  ClawRot(clawValue);
  ElbowRot(elbowValue);
  BaseRot(baseValue);
}

void handleRoot() {
  server.send(200, "text/html", "<html><body><h3>Welcome to RoboticArm Controller</h3></body></html>");
}

void ClawRot(int pos) {
  if (pos > CLAW_MAX) pos = CLAW_MAX;
  else if (pos < 0) pos = 0;

  if (pos > clawPos) {
    for (int i = clawPos; i <= pos; i++) {
      sClaw.write(i);
      delay(DELAY);
    }
  } else if (pos < clawPos) {
    for (int i = clawPos; i >= pos; i--) {
      sClaw.write(i);
      delay(DELAY);
    }
  }
  clawPos = pos;
}

void ElbowRot(int pos) {
  if (pos > ELBOW_MAX) pos = ELBOW_MAX;
  else if (pos < 0) pos = 0;

  if (pos > elbowPos) {
    for (int i = elbowPos; i <= pos; i++) {
      sElbow.write(i);
      delay(DELAY);
    }
  } else if (pos < elbowPos) {
    for (int i = elbowPos; i >= pos; i--) {
      sElbow.write(i);
      delay(DELAY);
    }
  }
  elbowPos = pos;
}

void BaseRot(int pos) {
  if (pos > BASE_MAX) pos = BASE_MAX;
  else if (pos < 0) pos = 0;

  if (pos > basePos) {
    for (int i = basePos; i <= pos; i++) {
      sBase.write(i);
      delay(DELAY);
    }
  } else if (pos < basePos) {
    for (int i = basePos; i >= pos; i--) {
      sBase.write(i);
      delay(DELAY);
    }
  }
  basePos = pos;
}

void resetAll() {
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