#include "Time.h"
#include "NewPing.h"
#include <VirtualWire.h>

const int numberOfAnalogPins = 3; 
int data[numberOfAnalogPins];
const int dataBytes = numberOfAnalogPins * sizeof(int); 

#define AVG_NUM 8    // number of iterations of the adc routine to average the adc readings
#define TRIGGER_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 2000 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define tank_height 400

//I2C_graphical_LCD_display lcd;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
float x;
int i,j,k,p,q;
char s,s1;
int id1=7938;
int chk=0;
void setup () 
{
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(7,1);
  vw_setup(2000); // Bits per sec
}  // end of setup



void loop () 
{  
 data[0]=read_sonar();
 data[1]=id1;
 data[2]=chk;
 chk=chk+1;
 if(chk>60) chk=0;
 digitalWrite(13,0);
 send((byte*)data, dataBytes);
 delay(1000);
 digitalWrite(13,1);
//chk=chk+1;
 }

int read_sonar()
  {
  int sum = 0;
  int sample ;
  for (int i=0; i<AVG_NUM; i++)   
  { 
    sample = sonar.ping()/US_ROUNDTRIP_CM; // Send ping, get ping time in microseconds (uS).
    delay(105);   //give some time to chill Arduino
    sonar.timer_stop();
    sum += sample;      
  }
  return(sum / AVG_NUM);
} 

void send (byte *data, int nbrOfBytes) 
{
//vw_setup(2000); // Bits per sec
vw_send(data, nbrOfBytes);
vw_wait_tx(); // Wait until the whole message is gone
}
