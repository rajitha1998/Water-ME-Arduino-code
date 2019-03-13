#define DHTTYPE DHT11
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h> 
#define Wifi_ssid "IIT Student WIFI"
#define password "#1234@abcd"
int Wifi_connection = 4;
DHT dht(D7,DHTTYPE);

uint8_t temperature,humidity;
void setup() {

  Serial.begin(9600); //Init serial communication
  // put your setup code here, to run once:
    pinMode(Wifi_connection, OUTPUT);
  //connect wifi
  Serial.println();
  Serial.println();
  Serial.print("connecting ");
  WiFi.begin(Wifi_ssid,password);// wifi SSID and the Password
  while(WiFi.status() != WL_CONNECTED){//making sure the device is connected to wifi
    digitalWrite(Wifi_connection, HIGH);
    delay(300);
    Serial.print(".");
    digitalWrite(Wifi_connection, LOW);
    delay(300);
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  digitalWrite(Wifi_connection, HIGH);
  Serial.println(WiFi.localIP());
  Firebase.begin("soilwateriit.firebaseio.com", "1DNvjjVMfsJXOoPpXHdmaGTp98EcpbYfHpsD8tlw");
  dht.begin(); // start the DHT11 sensor
  delay(1000);//giving time for sensor to get ready

}

void loop() {
  temperature = 1;
  humidity = dht.readHumidity();// reading humidity from the sensor and storing in to a variable
  Serial.print("Temperature ");
  Serial.print(temperature);// displaying temperature
  Serial.println("C");
  Serial.print("Humidity ");// displaying humidity
  Serial.print(humidity);
  Serial.println("%");
  Firebase.set("temp",temperature);
  Firebase.set("hum",humidity);
   if (Firebase.failed()) // Check for errors {

Serial.print("setting /number failed:");

Serial.println(Firebase.error()); 
 return;

  delay(1000);//managing the cloud traffic
} 


