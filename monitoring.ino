#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define  trig  4
#define  echo  5
#define buzzerPin 16 
long duration;
int distance;

// You should get Auth Token in the Blynk App.

char auth[] = "TFkj_65skBZmD4Mig6gdd6CjxM4FEn1_";
char ssid[] = "Redmi";
char pass[] = "12345678";   

BlynkTimer timer;

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH);   
  distance = 18-(duration * 0.034 / 2);

  Serial.print("Distance = ");      
  Serial.println(distance);
  
  if(distance >= 15)
  {
    Blynk.tweet("My Arduino project is tweeting using @blynk_app and it’s awesome!\n #arduino #IoT #blynk");
    Blynk.notify("Post has been twitted");
    tone(buzzerPin,9,400);  
  }
  Blynk.virtualWrite(V0, distance);
  delay(1000);                      
}
void setup()
{
  // Debug console
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(buzzerPin,OUTPUT);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
