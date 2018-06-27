#include "VirtualWire.h"

#include <Grove_I2C_Motor_Driver.h>

#define I2C_ADDRESS 0x0f

#define IR_PROXIMITY_SENSOR A2 // Analog input pin that  is attached to the sensor
    #define ADC_REF 5//reference voltage of ADC is 5v.If the Vcc switch on the Seeeduino
                     //board switches to 3V3, the ADC_REF should be 3.3
    float voltage;//the sensor voltage, you can calculate or find the distance
                    // to the reflective object according to the figures
                    //on page 4 or page 5 of the datasheet of the GP2Y0A21YK.
float timeDebut;
float timeFin;
float temps;
int distance; 
float espace_vide;
boolean rd;

int IRleft=4; //digital 4
int IRcenter=3; //digital 3
int IRright=2;  //digital 2 

int l1=1;
int l2=1;
int l3=1;

void setup()
{
  Motor.begin(I2C_ADDRESS);
  pinMode(IRleft,INPUT);
  pinMode(IRcenter,INPUT);
  pinMode(IRright,INPUT);
  Serial.begin(9600);
  Serial.println("setup tuture");
  vw_set_tx_pin(8);
  vw_setup(2000);
}
void loop()
{
   l1=digitalRead(IRleft);
   l2=digitalRead(IRcenter);
   l3=digitalRead(IRright);
    
    if(l1==0&&l2==1&&l3==1 ) //Turn Right
  {
    TurnRight1();
  }
  else if (l1==0&&l2==0&&l3==1) //Turn Right
  { 
     TurnRight2();
  }
     
  else if( l1==1&&l2==1&&l3==0 )  //Turn Left 
  {
    TurnLeft1();
  }
  else if (l1==1&&l2==0&&l3==0) //Turn Left
  { 
    TurnLeft2();
  }
  else if(l1==0 && l2==1 && l3==0) //Go Forward
  { 
    GoForward();
  }
  else if(l1==0 && l2==0&& l3==0) //  Repositioning
  { 
    repositioning();
  }
  else if(l1==1 && l2== 1 && l3==1 ) // Intersection for go Left
  { 
    intersection();
  } 
   getDistance();
   //Serial.println(distance);
    
   if(distance > 12) 
   {
     timeDebut = millis();
     Serial.print("Temps au debut: ");
     Serial.println(timeDebut);
     while (distance > 12)
     {
        getDistance();
        timeFin = millis();
        Serial.print("Temps a la fin: ");
        Serial.println(timeFin);
      }
      temps = timeFin - timeDebut;
                    
      Serial.print("Temps : ");
      Serial.println(temps);

      espace_vide = 0.315 * (temps/10); // distance en cm
      Serial.print("Distance entre les 2 : ");
      Serial.println(espace_vide);
      const char *msg = "tuture : ";
      vw_send((uint8_t*) msg, strlen(msg));
      vw_wait_tx();
      float dist = espace_vide;
      //float dist = 10.0;
     char toSent[5];
     char s[5];
     memset(s, '\0', 5);
     dtostrf(dist, 5, 3, s); 
  int i;

  Serial.println("\n"); //saut de ligne
  Serial.println("valeur de s ");
  Serial.println(s); //affiche le vrai char
  for (i = 0; s[i] != '\0'; i++) {
    Serial.println(s[i] + 1); //cryptage
    toSent[i] = s[i] + 1;
    Serial.println(toSent[i]);
  }
  Serial.println(toSent);
  Serial.println("\n");
      vw_send((byte*)&toSent, sizeof(toSent));
      vw_wait_tx();
    }
 }
    /****************************************************************************/
    /*Function: Get voltage from the sensor pin that is connected with analog pin*/
float getVoltage()
{
    int sensor_value;
    int sum;  
        // read the analog in value:
    for (int i = 0;i < 20;i ++)//Continuous sampling 20 times
    {
       sensor_value = analogRead(IR_PROXIMITY_SENSOR);
       sum += sensor_value;
     }
     sensor_value = sum / 20;
     float voltage;
     voltage = (float)sensor_value*ADC_REF/1024;
     return voltage;
}

void TurnRight1()
  {
   delay(50);
    Motor.speed(MOTOR1,-75);
    Motor.speed(MOTOR2,75);
    delay(200);
  }
  void TurnRight2()
  {
    Motor.speed(MOTOR1,-65);
    Motor.speed(MOTOR2,85);
  }
  void TurnLeft1()
  {
    Motor.speed(MOTOR1,75);
    Motor.speed(MOTOR2,-75);
    delay(300);
  }
  void TurnLeft2()
  {
     Motor.speed(MOTOR1,75);
     Motor.speed(MOTOR2,-85);
  }
  void GoForward()
  {
    Motor.speed(MOTOR1,35);
    Motor.speed(MOTOR2,35);
  }
  void  repositioning()
  {
    delay (50);
    Motor.speed(MOTOR1,-30);
    Motor.speed(MOTOR2,50);
  }
  void intersection()
  {
     if(rd = true)
    {
     delay(500);
     Motor.speed(MOTOR1,50);
     Motor.speed(MOTOR2,-20);
     rd = false;
    } 
    else 
    {
      Motor.speed(MOTOR1,-20);
      Motor.speed(MOTOR2,50);
      rd = true;
    }
  }

float getDistance(){
  voltage = getVoltage();
  distance = 29.988 * pow(voltage , -1.173);  
  return distance;
}

