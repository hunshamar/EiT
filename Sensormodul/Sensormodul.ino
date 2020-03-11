/*
  ccs811basic.ino - Demo sketch printing results of the CCS811 digital gas sensor for monitoring indoor air quality from ams.
  Created by Maarten Pennings 2017 Dec 11
*/
#include <MicroLCD.h>






LCD_SH1106 lcd; /* for SSD1306 OLED module */

#include <Wire.h>    // I2C library



// Wiring for Nano: VDD to 3v3, GND to GND, SDA to A4, SCL to A5, nWAKE to 13
//CCS811 ccs811(13); 

// nWAKE not controlled via Arduino host, so connect CCS811.nWAKE to GND
//CCS811 ccs811; 

// Wiring for ESP32 NodeMCU boards: VDD to 3V3, GND to GND, SDA to 21, SCL to 22, nWAKE to D3 (or GND)
//CCS811 ccs811(23); // nWAKE on 23


void setup() {
  //LCDinit();
  
  lcd.begin();
  // Enable serial
  Serial.begin(9600);

  //CO2init();

  Wire.begin(); 

  AirQualitySensorInit();
 
}


  int counter = 0;
int dotIndex = 0;


void loop() {


char* strArr  [4];
strArr[0] = "   ";
strArr[1] = ".  ";
strArr[2] = ".. ";
strArr[3] = "...";
  // Read
  
  int eco2; 
  int etvoc;
  int humidity = readHumiditySensor();

  AirQualitySensorReadCO2(&eco2, &etvoc);
  
  char* printString = "reading sensor";



  // Wait
  
    //lcd.clear();
    
    
    lcd.setCursor(0, 1);
    lcd.print("co2      : ");
    lcd.print(eco2);
    lcd.println(" ppm");
    
    lcd.print("etvoc    : ");
    lcd.print(etvoc);
    lcd.println(" ppm");
    lcd.print("humidity : ");
    lcd.print(humidity);
    lcd.println(" %");
    lcd.println();
    
    lcd.print(printString);


    lcd.print(strArr[dotIndex++]);

    if (dotIndex == 4){
      dotIndex = 0;
    }


    if(counter++ >= 4) {
      counter = 0;
      Serial.print("begin|");
      Serial.print("CO2:");
      Serial.print(eco2);
      Serial.print("|VOC:");
      Serial.print(etvoc);    
      Serial.print("|HM:");
      Serial.print(humidity);    
      Serial.println("|end");
    }

    delay(500); 
}



