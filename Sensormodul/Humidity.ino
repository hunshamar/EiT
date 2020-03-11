#include <Arduino.h>

#define humiditySensorPin A0
#define humitiyDry 549
#define humitiyWet 265


int readHumiditySensor(){
    int read = analogRead(humiditySensorPin);

    // Serial.print("read: (between 262 and 515) ");
    // Serial.print(read);
    // Serial.print(" ");
   


    return (int)(100 - 100*(read - humitiyWet) / (double)(humitiyDry - humitiyWet));


}