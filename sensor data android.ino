#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "esri-eea51.firebaseio.com"
#define FIREBASE_AUTH "qULRQbnuzJ3qkAdYunMasgcLlKtpXic1UQ1FxHvM"
#define WIFI_SSID "kavin"
#define WIFI_PASSWORD "1123581321"
const int trigPin = 15;  //D4
const int echoPin = 12;  //D3
long duration;int distance;
void setup() {
Serial.begin(9600);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(16, OUTPUT); //D0
pinMode(0, INPUT);  //D3
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
Firebase.set("LED_STATUS", 0);
Firebase.setInt("distance", 0);
}
int n = 0;
void loop() {

/*
 * For Utlrasonic sensor distance measurement
 */

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
Firebase.setInt("distance",distance);
delay(2000);
/*
 * Led Control Home Automation
 */

n = Firebase.getInt("LED_STATUS");
// handle error
if (n==1) {
Serial.println("LED ON");
digitalWrite(16,HIGH);  
return;
//delay(10);
}
else {
Serial.println("LED OFF");
digitalWrite(16,LOW);  
}

}

