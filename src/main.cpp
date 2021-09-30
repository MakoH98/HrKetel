//**
// author: Marko Held 
// sources
//**

#include <Arduino.h>


int TEMP_PIN_A = 14;
int TEMP_PIN_B = 15;

unsigned long CURRENTMILLIS;
unsigned long PREVIOUSMILLIS;
unsigned int tempratureInterval = 500; //ms
unsigned long ntc1LastCheck;
unsigned long ntc2LastCheck;
float tempA;
float tempB;
float array{0};
float temprature(int pin);
void log();

void setup() {
  Serial.begin (9600);
  

}

void loop() {
  CURRENTMILLIS = millis();
  if (CURRENTMILLIS - ntc1LastCheck>= tempratureInterval){      //reading NTC TEMP
    tempA = temprature(TEMP_PIN_A);
    tempB = temprature(TEMP_PIN_B);

    ntc1LastCheck = CURRENTMILLIS;

    log();              //## log temprature values in CSV Format for excel Data stream plugin

  }

}


float temprature(int pin){   //## function to convert voltage to temprature //##
  int _pin = pin;
  int Vo;
  float logR2, R2, T;
  float R1 = 10000; 
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; //constants for ntc

  
    Vo = analogRead(_pin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
    T = T - 273.15;
    
    return T;

}

void log(){ //designed for excel data stream AKA CSV
    Serial.print("tempratureA");
    Serial.print(",");
    Serial.print(tempA);
    Serial.print(",");
    Serial.print("tempratureB");
    Serial.print(",");
    Serial.print(tempB);
    Serial.print(",");
    Serial.println();     //#very important to start new line For excel Data Stream //##
  return;
}