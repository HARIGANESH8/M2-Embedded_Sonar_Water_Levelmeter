#include <VirtualWire.h>
#include <LiquidCrystal.h>
const int numberOfAnalogPins = 3; // how many analog integer values to receive
int data[numberOfAnalogPins]; // the data buffer
int value[numberOfAnalogPins];// the number of bytes in the data buffer
const int dataBytes = numberOfAnalogPins * sizeof(int);
byte msgLength = dataBytes;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(3,4,5,6,7,8);
int i,count;
char s1[2];
long x;
float y;

void setup() {
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
digitalWrite(12,0);

  // set up the LCD's number of columns and rows: 
vw_set_ptt_inverted(true); // Required for DR3100
vw_setup(2000); // Bits per sec
vw_set_rx_pin(2);
vw_rx_start(); // Start the receiver

  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("level:");
  lcd.setCursor(0,1);    	
  lcd.print("PID:");
}
int j=0;


void loop() {
lcd.setCursor(6,0); 
if (vw_get_message((byte*)data, &msgLength))  {    // Non-blocking
if(msgLength == dataBytes){
for (int i = 0; i < numberOfAnalogPins; i++) {
if (data[0]>=0 && data[1]==7938) {
            y=data[2]*1.0;
 //           dtostrf(y, 2, 0, s1);
            digitalWrite(13,1);  //OK
	    lcd.print(data[0]);
            lcd.print(" ");
            lcd.setCursor(4,1);
            lcd.print(data[1]);
            lcd.setCursor(14,0);
            lcd.print(y);
            
            digitalWrite(13,0);  //OK
            } 
        }} 
 }           

}


