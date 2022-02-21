/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID   "TMPLCtWzZ7yA"


#include <SPI.h>
#include <WiFi101.h>
#include <BlynkSimpleMKR1000.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "XvjWuyxhETkiGm83NYTwfqJa_pDAfTNz";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jah";
char pass[] = "jstar777";

BlynkTimer timer; //timer for BLYNK functions
int sensorData;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  digitalWrite(0, pinValue);
}

//function to read sensor data at timer interval specified
void myTimerEvent(){
  sensorData = analogRead(A0);
  sensorData /= 15;
  Blynk.virtualWrite(V1, sensorData);
}


void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(0, OUTPUT);
  pinMode(A0, INPUT);
  
  //set Timer event to run every 1000ms (1s)
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();  //running timer every second
  Serial.println(sensorData);
}
