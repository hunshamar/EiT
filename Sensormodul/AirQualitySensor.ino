
#include "ccs811.h"  // CCS811 library



// Wiring for ESP8266 NodeMCU boards: VDD to 3V3, GND to GND, SDA to D2, SCL to D1, nWAKE to D3 (or GND)
CCS811 ccs811(A5); // nWAKE on D3


void AirQualitySensorInit(){
     Serial.println("");
  Serial.println("setup: Starting CCS811 basic demo");
  Serial.print("setup: ccs811 lib  version: "); Serial.println(CCS811_VERSION);

  // Enable I2C
  
  // Enable CCS811
  ccs811.set_i2cdelay(50); // Needed for ESP8266 because it doesn't handle I2C clock stretch correctly
  bool ok= ccs811.begin();
  if( !ok ) Serial.println("setup: CCS811 begin FAILED");

  // Print CCS811 versions
  Serial.print("setup: hardware    version: "); Serial.println(ccs811.hardware_version(),HEX);
  Serial.print("setup: bootloader  version: "); Serial.println(ccs811.bootloader_version(),HEX);
  Serial.print("setup: application version: "); Serial.println(ccs811.application_version(),HEX);
  
  // Start measuring
  ok= ccs811.start(CCS811_MODE_1SEC);
  if( !ok ) Serial.println("setup: CCS811 start FAILED");
}



void AirQualitySensorReadCO2(int* co2, int* voc){
  


  uint16_t eco2, etvoc, errstat, raw;
  ccs811.read(&eco2,&etvoc,&errstat,&raw); 
  
  // Print measurement results based on status
  // if( errstat==CCS811_ERRSTAT_OK ) { 
    // Serial.print("CCS811: ");
    // Serial.print("eco2=");  Serial.print(eco2);     Serial.print(" ppm  ");
    // Serial.print("etvoc="); Serial.print(etvoc);    Serial.print(" ppb  ");
    //Serial.print("raw6=");  Serial.print(raw/1024); Serial.print(" uA  "); 
    //Serial.print("raw10="); Serial.print(raw%1024); Serial.print(" ADC  ");
    //Serial.print("R="); Serial.print((1650*1000L/1023)*(raw%1024)/(raw/1024)); Serial.print(" ohm");
  //   Serial.println();
  // } else if( errstat==CCS811_ERRSTAT_OK_NODATA ) {
  //   Serial.println("CCS811: waiting for (new) data");
  // } else if( errstat & CCS811_ERRSTAT_I2CFAIL ) { 
  //   Serial.println("CCS811: I2C error");
  // } else {
  //   Serial.print("CCS811: errstat="); Serial.print(errstat,HEX); 
  //   Serial.print("="); Serial.println( ccs811.errstat_str(errstat) ); 
  // }


  *co2 = eco2;
  *voc = etvoc;
   
}
