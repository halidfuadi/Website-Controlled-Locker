#include <Servo.h>
#include <ESP8266WiFi.h>   
#include <ESP8266HTTPClient.h>

#define WIFI_SSID "SandangBiz Lt.1_plus"        
#define WIFI_PSWD "kostsandang18970"     
#define serverAddress "http://192.168.29.8:6969"
#define LED D0

Servo myservo;
int val = 1;
int led = 13;
WiFiClient client;  // Use WiFiClient instead of HTTPClient
HTTPClient http;

void setup() {
  Serial.begin(9600);
  myservo.attach(5);
  pinMode(LED, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  
  Serial.print(" Connecting to ");
  Serial.print(WIFI_SSID);
  Serial.println(" .....");

  int i = 0;
  while(WiFi.status() != WL_CONNECTED){
    delay(600);
    i++;
    Serial.print(i);
    Serial.print(" ");
  }
  
  Serial.println(" ");
  Serial.println("Connected: ");
  Serial.print("Ip Address:  ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  kirimRequestToggleLocker();
}

void close(){
  myservo.write(180);
  // delay(15);
}

void open(){
  myservo.write(0);
  // delay(15);
}

void kirimRequestToggleLocker() {
  http.begin(client, String(serverAddress) + "/locker/" + String(1));  // Use the updated begin method

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(response);

    if (response.equals("1")) {
      close();
      digitalWrite(led, LOW);
    } else{
      open();
      digitalWrite(led, HIGH);
    }
  } else {
    Serial.print("HTTP Request failed. Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}