/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

int humidity[20];
int cH = 0;
int ledPin = 4;


Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));
    pinMode (ledPin, OUTPUT);

    bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();


}


void loop() { 
     
    for (cH=0; cH<20; cH++) //for loop counting up from 0-20, corresponding to elements in humidity array
    {
        humidity[cH] = (bme.readHumidity());  //add the current humidity to the humidity array at value cH
        delay 4000;  //wait four seconds
        if humidity[cH] - humidity[cH-1] > 4  //if the humidity has increased by more than 4%  
        {
          digitalWrite(ledPin, HIGH);  //turn on the LED
          delay 600000; //leave the LED on for 10 mins
          digitalWrite(ledPin, LOW);  //turn off the LED
        }
    }
    for (cH=20; cH>0; cH--) //same loop as above, now counting down from 20-0
        {
        humidity[cH] = (bme.readHumidity());  //add the current humidity to the humidity array at value cH
        delay 4000;  //wait four seconds
        if humidity[cH] - humidity[cH+1] > 4  //if the humidity has increased by more than 4% (minus in above loop changed to plus) 
        {
          digitalWrite(ledPin, HIGH);  //turn on the LED
          delay 600000; //leave the LED on for 10 mins
          digitalWrite(ledPin, LOW);  //turn off the LED
        }
}
