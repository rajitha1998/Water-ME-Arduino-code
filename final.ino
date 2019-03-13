#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#define DHTTYPE DHT11
#include <FirebaseArduino.h> 
int analog_in = A0;
int indicator = 12;
int LED = 13;
DHT dht(14,DHTTYPE);
WiFiClient client;
uint8_t temperature, humidity,mositure; //variables to store sensor data

void setup() {
  Serial.begin(9600); //board rate
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  digitalWrite(D1, 0);
  digitalWrite(D2, 0);
  digitalWrite(D3, 0);
  pinMode(LED, OUTPUT);
  pinMode(indicator, OUTPUT);
  //connect wifi
  Serial.println();
  Serial.println();
  Serial.print("connecting ");
  WiFi.begin("Rajitha","kq3618kq");// wifi SSID and the Password
  while(WiFi.status() != WL_CONNECTED){//making sure the device is connected to wifi
    digitalWrite(LED, HIGH);
    delay(200);
    Serial.print(".");
    digitalWrite(LED, LOW);
    delay(300);
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  digitalWrite(LED, HIGH);
  Serial.println(WiFi.localIP());
  //ThingSpeak.begin(client);//starting the cloud
  dht.begin(); // start the DHT11 sensor
  delay(10);//giving time for sensor to get ready
}

void loop() {
  mositure = analogRead(analog_in); //670 is 0 295 is 100
  mositure = map(mositure,0,180,0,60);
  Firebase.set("soil",mositure);
  if(Firebase.failed()){
    Serial.println("failed");
    Serial.println(Firebase.error());    
    }
  //ThingSpeak.writeField(486795,1,mositure,"AP7JLTCP8SUI9SVK");//sending data to cloud
  Serial.print("Mositure : ");
  Serial.print(mositure);
  Serial.println("%");
  if(mositure < 40){
       digitalWrite(indicator, HIGH);
   } else {
       digitalWrite(indicator, LOW);
     }
  temperature = dht.readTemperature();// reading temperature from the sensor and storing in to a variable
  humidity = dht.readHumidity();// reading humidity from the sensor and storing in to a variable
  Serial.print("Temperature ");
  Serial.print(temperature);// displaying temperature
  Serial.println("C");
  Serial.println("Humidity ");// displaying humidity
  Serial.print(humidity);
  Serial.println("%");
  Firebase.set("temp",temperature);
  Firebase.set("hum",humidity);
  //ThingSpeak.writeField(481891,1,temperature,"TD1JL1XCE8QN6M3J");//sending data to cloud
  //ThingSpeak.writeField(486792,1,humidity,"ISAIGT2RM05QMJUP");//sending data to cloud
  
  int type  =  Firebase.getInt("mode"); //ThingSpeak.readFloatField(486797,1);
  if(type == 0){
  int motor = Firebase.getInt("motor"); //ThingSpeak.readFloatField(486797,1);
  int hum_con = Firebase.getInt("humCon"); //ThingSpeak.readFloatField(486797,2);
  int temp_con = Firebase.getInt("tempCon"); //ThingSpeak.readFloatField(486797,3);
  

  if(motor == 1){
    digitalWrite(D1, 1);
  }
  else {
    digitalWrite(D1, 0);
  }

  if(hum_con == 1){
    digitalWrite(D2, 1);
  }
  else {
    digitalWrite(D2, 0);
  }

  if(temp_con == 1){
    digitalWrite(D3, 1);
  }
  else {
    digitalWrite(D3, 0);
  }
  }
  else{
    
    }
  
  
    
    delay(12000);//managing the cloud traffic
  
  }
