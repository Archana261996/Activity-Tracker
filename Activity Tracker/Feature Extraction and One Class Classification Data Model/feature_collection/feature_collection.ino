#include "Arduino_LSM9DS1.h"

float aX = 0, aY = 0, aZ = 0;
float gX = 0, gY = 0, gZ = 0;
String delim = "," ;
int i=0, j=0;
const int numSamples = 119;
char output[9];
char class0[] = "Dancing";
char class1[] = "Walking";
char class2[] = "Ascending";
char class3[] = "Descending";
char class4[] = "Sitting";
char class5[] = "Jumping";
char class6[] = "Standing";

double RMS_x = 0, std_X=0.0, std_Z=0.0, min_X=0.0, min_Z =0.0, deviation_x=0.0;
double sumX=0.0, avgX=0.0, sum1=0.0, medianZ = 0;
double x[numSamples]={0.0,}, y[numSamples]={0.0,}, z[numSamples]={0.0,};

void setup() {
  Serial.begin(9600);
  delay(3000);
 // startMillis = millis();  //initial start time

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1) delay(1000);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");

  Serial.println("Features Example Code");
}

void loop() {
      
     //Get all the sensor data
     for (int p=0; p<numSamples;p++) {

      IMU.readAcceleration(aX, aY, aZ);
    //  IMU.readGyroscope (gX, gY, gZ);
     x[p] = aX;
     y[p] = aY;
     z[p] = aZ;
     }

      sumX = 0;

      //calculate mean_x (Feature 2)
      for (j = 0; j < numSamples; j++)
      {
          sumX +=x[j];
      }
      avgX = sumX / numSamples;
      sumX = 0;
      
      //calculate standard deviation _x axis (Feature 6)
      sum1=0;
      for (j = 0; j < numSamples; j++)
      {
       deviation_x = x[j] - avgX;
       sum1+= pow(deviation_x, 2);
      }
      std_X = sqrt(sum1 / numSamples);

      //RMS _X axis (Feature 7)
      RMS_x = 0;
      for (j = 0; j < numSamples; j++)
      {
          sumX +=pow (x[j],2);
      }
      RMS_x = sumX / numSamples;
      RMS_x = sqrt(RMS_x);
      
      
      //Calculate Median _Z axis (Feature 19)

      medianZ = 0;
      for(j = 0; j < numSamples; j++)
      {
         for (int k = 1 ; k <= numSamples-j ; k++){
          if (z[k] <= z[k+1]){
          double t = z[k];
         z[k] = z[k+1];
         z[k+1] = t;
      } else
      continue ;
   }
}
if ( numSamples % 2 == 0)
   medianZ = (z[numSamples/2] + z[numSamples/2+1])/2.0 ;
else
   medianZ = z[numSamples/2 + 1];

      Serial.println(avgX + delim +std_X + delim + RMS_x+ delim + medianZ);

 // Decison Tree

 if(medianZ <= 0.79)
 {
  if(std_X<=0.05)
  {
    if(avgX<= -0.46)
    {
      output = class6;
    }
    else
    {
      output = class1;
    }
    
  }
    else
    {
     if(RMS_x <= 0.61){
      if(RMS_x <= 0.39)
      {
        output = class1; 
      }
      else
      output = class0;
     }
     else
     if(avgX <= -0.63)
     output = class5;
     else
     output = class4;
     
  }
 }
 else
 output = class3;
 
 }
