//based off adafruit library example code

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;
void reorgRGB(uint16_t rgb[]);
void setup() {
  Serial.begin(115200);

  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable color sensing mode
  apds.enableColor(true);
  apds.enableProximity();
}

void loop() {
  //create some variables to store the color data in
  uint16_t r, g, b, c;
  
  //wait for color data to be ready
  while(!apds.colorDataReady()){
    delay(5);
  }

  //get the data and print the different channels
  apds.getColorData(&r, &g, &b, &c);
  Serial.print("red: ");
  Serial.print(r);
  
  Serial.print(" green: ");
  Serial.print(g);
  
  Serial.print(" blue: ");
  Serial.print(b);
  Serial.println();
  uint16_t RGB[3]={r,g,b};
  reorgRGB(RGB);
    Serial.print("Fixed red: ");
  Serial.print(RGB[0]);
  
  Serial.print(" Fixed green: ");
  Serial.print(RGB[1]);
  
  Serial.print(" Fixed blue: ");
  Serial.print(RGB[2]);
  Serial.println();
  /* Serial.print(" clear: ");
  Serial.println(c);
  Serial.println(); */
  Serial.print("Closeness: ");
  Serial.println(apds.readProximity());
  delay(500);
}


void reorgRGB(uint16_t rgb[])
 {
    rgb[0]=rgb[0]*3.9584-46.958;
    rgb[1]=rgb[1]*2.0098-21.194;
    rgb[2]=rgb[2]*3.0622-195.16;
}