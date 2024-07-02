#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define MAX_DISTANCE 7 

#define FIREBASE_HOST "smart-home-224ab-default-rtdb.firebaseio.com" // Firebase host
#define FIREBASE_AUTH "MzOWnrdK46mPPYAS5AfDF40u9Tol7TaHr2m5LHbd" // Firebase Auth code
#define WIFI_SSID "DD" // Enter your WiFi name
#define WIFI_PASSWORD "23456789" // Enter your WiFi password

#define TRIG_PIN D1 // GPIO 5 (D1)
#define ECHO_PIN D2 // GPIO 4 (D2)

int fireStatus = 0;

void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600); // Ensure this baud rate matches the Serial Monitor's baud rate

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected.");
  Serial.println(WiFi.localIP());
  
  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Initialize the sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
}

void loop() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.034 / 2;

  // Map the distance to a percentage value (0 to 100)
  int percentage = map(distance, 0, MAX_DISTANCE, 100, 0);
  if (percentage > 100) {
    percentage = 100;
  } else if (percentage < 0) {
    percentage = 0;
  }


  Serial.print("Percentage: ");
  Serial.print(percentage);
  Serial.println(" %");

  Firebase.setInt("/percentage", percentage);
    
}

