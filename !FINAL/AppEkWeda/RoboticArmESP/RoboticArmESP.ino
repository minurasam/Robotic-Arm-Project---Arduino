#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <ArduinoJson.h>

ESP8266WebServer server(80);
#define CLAW_MAX 50
#define ELBOW_MAX 75
#define BASE_MAX 180

#define DELAY 20

#define PIN_CLAW 5 //D1
#define PIN_ELBOW 4 //D2
#define PIN_BASE 0 //D3

char* wifi_ssid = "RoboticArm";
char* wifi_pwd = "robotikka";
char* username = "bartso";
char* password = "letmein";

Servo sClaw, sElbow, sBase;
int clawPos, elbowPos, basePos;

void handleAPI() {
  if (!server.authenticate(username, password)) {
    return server.requestAuthentication(DIGEST_AUTH);
  }
  server.send(200, "text/plain");
  Serial.println(server.arg(0));
  
  const char s[2] = "\n";
  char * cstr = new char[server.arg(0).length() + 1];
  strcpy(cstr, server.arg(0).c_str());

  char *token = strtok(cstr, s);

  while (token != NULL) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& node = jsonBuffer.parseObject(token);

    if (node.containsKey("Delay")) {
      rotateAutomatic(node["Claw"], node["Elbow"], node["Base"]);
      delay(node["Delay"]);
    } else {
      rotateAutomatic(node["Claw"], node["Elbow"], node["Base"]);
      delay(DELAY);
    }

    token = strtok(NULL, s);
  }
}

void rotateAutomatic(int clawVAL, int elbowVAL, int baseVAL) {
  Serial.println(clawVAL);
  Serial.println(elbowVAL);
  Serial.println(baseVAL);

  ClawRot(clawVAL);
  ElbowRot(elbowVAL);
  BaseRot(baseVAL);
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
  sElbow.write(elbowPos);
  sBase.write(basePos);
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_pwd);

  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi failed. Rebooting...");
    delay(1000);
    ESP.restart();
  }

  ArduinoOTA.begin();

  server.on("/api", handleAPI);
  server.begin();

  Serial.print("WiFi connected. IP Address: ");
  Serial.println(WiFi.localIP());
  
  sClaw.attach(PIN_CLAW);
  sElbow.attach(PIN_ELBOW);
  sBase.attach(PIN_BASE);
  resetAll();
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}
