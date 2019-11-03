#include <LiquidCrystal_I2C.h>
#include <ThingSpeak.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
String apiWritekey = "H0ZM9A5VB2I1XUS5";
char auth[] = "9f1accc018f94d14a3fefb797e02ab98";
char ssid[] = "Gopal";
char pass[] = "123456788";
const char* server = "api.thingspeak.com";
unsigned long myChannelNumber = 842529;
WiFiClient client;
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
void setup()
{
  Serial.begin(115200);
  lcd.begin(16,2);
  lcd.clear();
  Blynk.begin(auth, ssid, pass);
  pinMode(D3,INPUT);
  pinMode(D4,OUTPUT);
  pinMode(A0,INPUT);
  
}

void loop()
{
  Blynk.run();

  float temp=analogRead(A0);
  temp=temp*0.48828125;
  Serial.println("Temp:");
  Serial.println(temp);
  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temp);

  

 
  Blynk.virtualWrite(V1,temp);
//     ThingSpeak.setField(1,temp);
  //delay(15000);
  int a=digitalRead(D3);
  if(a==1)
  {
    Serial.println("Tiffin Opened");
    Blynk.virtualWrite(V0,"Tiffin Opened");
  // ThingSpeak.setField(2,"tiffin OPened");

    delay(100);
  }
  if(a==0)
  {
      Serial.println("Tiffin Closed");
      Blynk.virtualWrite(V0,"Tiffin Closed");
     //   ThingSpeak.setField(2,"tiffin Closed");

    delay(100);  
  }
/*
  
      if (client.connect(server,80))
      {  
           String tsData = apiWritekey;
              tsData +="&field1=";
              tsData += String(temp);
              tsData += "\r\n\r\n";
 
              client.print("POST /update HTTP/1.1\n");
              client.print("Host: api.thingspeak.com\n");
              client.print("Connection: close\n");
              client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
              client.print("Content-Type: application/x-www-form-urlencoded\n");
              client.print("Content-Length: ");
              client.print(tsData.length());
              client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
              client.print(tsData);
 
            //  Serial.print("Temperature: ");
            //Serial.print(temp);
            //Serial.println("uploaded to Thingspeak server....");
  }
        client.stop();
 
        Serial.println("Waiting to upload next reading...");
        Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
        delay(15000);
*/
}
