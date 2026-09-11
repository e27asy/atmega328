#include <Arduino.h>

#include <Wire.h> 
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(-1); 


#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT11  // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  OLED.begin(SSD1306_SWITCHCAPVCC,0x3C);
  Serial.println("DHTxx test!");

  dht.begin();



  
  // ล้างหน้าจอ
  OLED.clearDisplay(); 
// กำหนดสีตัวอักษร
  OLED.setTextColor(WHITE,BLACK);   //Text is white ,background is black
  OLED.setTextSize(2); 
  // ตำแหน่ง
  // OLED.setCursor(5, 0);
  // OLED.print( "temperature" );
  
  // ส่งข้อมูลไป OLED
  OLED.display();

}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);


  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
 

  OLED.clearDisplay();
  OLED.setTextColor(WHITE,BLACK);   //Text is white ,background is black
  OLED.setCursor(20, 0);
  OLED.setTextSize(1); 
  OLED.println("DHT11 Sensor");

  // กำหนดสีตัวอักษร
  OLED.setTextColor( SSD1306_WHITE );
  // ขนาดตัวอักษร
  OLED.setTextSize(2);
  // ตำแหน่ง
  OLED.setCursor(5, 20);
  OLED.print( "T:" );
  OLED.print(t);
  OLED.print( " *C" );
  OLED.setCursor(5, 45);
  OLED.print( "H:" );
  OLED.print(h);
  OLED.println( " %" );
  // ส่งข้อมูลไป OLED
  OLED.display();



}


