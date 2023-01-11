#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

#define FIREBASE_HOST "url"
#define FIREBASE_AUTH "auth token"
#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "wifi password"
#define Relay1 D1
int relay1;
String strRelay1 = "";
FirebaseData firebaseData;
void setup() {
  Serial.begin(115200);
  //------------------------------------
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  pinMode(Relay1, OUTPUT);
  digitalWrite(Relay1, HIGH);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setInt(firebaseData, "/FB1", 0); // diisi tag ranger
}

void loop() {
  Firebase.getString(firebaseData, "/FB1");
  strRelay1 = firebaseData.stringData();
  relay1 = strRelay1.toInt();
  Serial.print("relay1 = ");
  Serial.println(relay1);
  if (relay1 == 1)
  {
    digitalWrite(Relay1, LOW);
    Serial.println("Relay 1 ON");
  }
  if (relay1 == 0)
  {
    digitalWrite(Relay1, HIGH);
    Serial.println("Relay 1 OFF");
  }
}
