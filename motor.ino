   #include <ESP8266WiFi.h>
#include <FirebaseArduino.h> 
#define Wifi_ssid "Rajitha"
#define password "kq3618kq"
int analog_in = A0;
int Wifi_connection = 4;
const int motorPin = D3;
int Speed;

uint8_t mositure; //variables to store  data

void setup() {
  Serial.begin(9600); 
  pinMode(motorPin, OUTPUT); //Set pin 3 as an OUTPUT
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D1, OUTPUT);
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
  delay(1000);//giving time for sensor to get ready
  
}
  
void loop() {
  mositure = analogRead(analog_in); 
  mositure = map(mositure,0,180,0,60);
  Firebase.set("soil",mositure);
  if(Firebase.failed()){
    Serial.println("failed");
    Serial.println(Firebase.error());    
    }
  Serial.print("Mositure : ");
  Serial.print(mositure);
  Serial.println("%");
   int type  =  Firebase.getInt("mode"); 
  if(type == 0){
  int motor = Firebase.getInt("motor"); 
  int hum_con = Firebase.getInt("humCon"); 
  int temp_con = Firebase.getInt("tempCon"); 
  digitalWrite(D7, motor);
  digitalWrite(D1, hum_con);
  digitalWrite(D6, temp_con);
  }
  else{
  uint8_t optimalSoil = Firebase.getInt("optimalsoil");
  uint8_t mositure = Firebase.getInt("soil");
  
    if(mositure <= optimalSoil -3){
      digitalWrite(D7,HIGH);
      }else{
      digitalWrite(D7,LOW);
        }
   uint8_t humidity = Firebase.getInt("hum");
   uint8_t optimalHum = Firebase.getInt("optimalHum");
    if(humidity <= optimalHum + 15 && humidity > optimalHum - 10){
      digitalWrite(D1,LOW);
      }else{
        digitalWrite(D1,HIGH);
        } 
  uint8_t temperature = Firebase.getInt("temp");      
  uint8_t optimalTemp = Firebase.getInt("optimalTemp");       
    if(temperature <= optimalTemp + 5 && temperature > optimalTemp - 3){
      digitalWrite(D6,LOW);
      }else{
        digitalWrite(D6,HIGH);
        }   
  Serial.println(temperature);
  Serial.println(optimalTemp);
  Serial.println(humidity);
  Serial.println(optimalHum);
  Serial.println(mositure);
  Serial.println(optimalSoil);
  Speed = 200;
    analogWrite(motorPin, Speed);   
    
  }
  
  Serial.println(type);
  
  
  delay(1000);//managing the cloud traffic
  
  }
