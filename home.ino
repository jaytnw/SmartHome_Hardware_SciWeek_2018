#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Config Firebase
#define FIREBASE_HOST "home-ac0a7.firebaseio.com"
#define FIREBASE_AUTH "I5ZtvRD4VdoKxjyBgV24UQPieity0ZzxO1GMdMdE"

// Config connect WiFi
#define WIFI_SSID "Sciweek-IT"
#define WIFI_PASSWORD "123456789"


int LivingP = D1;
int Bedroom1P = D2;
int Bedroom2P = D3;

void setup() {
  pinMode(LivingP, OUTPUT);
  pinMode(Bedroom1P, OUTPUT);
  pinMode(Bedroom2P, OUTPUT);
  digitalWrite(LivingP, LOW);
  digitalWrite(Bedroom1P, LOW);
  digitalWrite(Bedroom2P, LOW);

  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop() {

  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());
      return;
    }
  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String Living = event.getString("Living");
    String Bedroom1 = event.getString("Bedroom1");
    String Bedroom2 = event.getString("Bedroom2");
    Serial.println(Living);
    if (Living == "ON") {
      digitalWrite(LivingP, HIGH);
    } else if (Living == "OFF") {
      digitalWrite(LivingP, LOW);

    }
    if (Bedroom1 == "ON") {
      digitalWrite(Bedroom1P, HIGH);
    } else if (Bedroom1 == "OFF") {
      digitalWrite(Bedroom1P, LOW);

    }
    if (Bedroom2 == "ON") {
      digitalWrite(Bedroom2P, HIGH);
    } else if (Bedroom2 == "OFF") {
      digitalWrite(Bedroom2P, LOW);

    }
    
  }
}



