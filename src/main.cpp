//based off adafruit library example code

#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;
void reorgRGB(int rgb[]);
void RGB2HSV(int rgb[], double hsv[]);
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
  int RGB[3]={r,g,b};
  reorgRGB(RGB);
    Serial.print("Fixed red: ");
  Serial.print(RGB[0]);
  
  Serial.print(" Fixed green: ");
  Serial.print(RGB[1]);
  
  Serial.print(" Fixed blue: ");
  Serial.print(RGB[2]);
  Serial.println();
  double HSV[3];
  RGB2HSV(RGB,HSV);

  Serial.print("Hue: ");
  Serial.print(HSV[0]);
  
  Serial.print(" Shade: ");
  Serial.print(HSV[1]);
  
  Serial.print(" Value: ");
  Serial.print(HSV[2]);
  Serial.println();
if (HSV[0]>=70&&HSV[0]<=260&&HSV[1]>.25&&HSV[2]>.1)
{
  Serial.println("That's Recycling");
}
else
{
  Serial.println("That's Trash");
}
  Serial.print("Closeness: ");
  Serial.println(apds.readProximity());
  delay(500);
}


void reorgRGB(int rgb[])
 {
    rgb[0]=rgb[0]*3.9584-46.958;
    rgb[0]=min(max(rgb[0],0),255);
    rgb[1]=rgb[1]*2.0098-21.194;
    rgb[1]=min(max(rgb[1],0),255);
    rgb[2]=rgb[2]*3.0622-195.16;
    rgb[2]=min(max(rgb[2],0),255);
}

void RGB2HSV(int rgb[], double hsv[])
{
  //https://math.stackexchange.com/questions/556341/rgb-to-hsv-color-conversion-algorithm
  double R=rgb[0];
  double G=rgb[1];
  double B=rgb[2];
  R=R/255;
  G=G/255;
  B=B/255;
  double cmax=max(max(R,G),B);
  double cmin=min(min(R,G),B);
  double delta=cmax-cmin;
  if (R==G&&R==B)
  {
    hsv[0]=0;
  }
  else if (cmax==R)
  {
    hsv[0]=60*fmod((G-B)/delta,6);//main idea here is to turn negatives into positives that are at 300+ plus degrees, not really readable but whatever
  }
  else if (cmax==G)
  {
    hsv[0]=60*((B-R)/delta+2);
  }
  else
  {
    hsv[0]=60*((R-G)/delta+4);
  }
  if (cmax==0)
  {
    hsv[1]=0;
  }
  else
  {
    hsv[1]=delta/cmax;
  }
  hsv[2]=cmax;
  
}