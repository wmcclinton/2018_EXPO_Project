/* Read Jostick
  * ------------
  *
  * Reads two analog pins that are supposed to be
  * connected to a jostick made of two potentiometers
  *
  * We send three bytes back to the comp: one header and two
  * with data as signed bytes, this will take the form:
  *     Jxy\r\n
  *
  * x and y are integers and sent in ASCII 
  * 
  * http://www.0j0.org | http://arduino.berlios.de
  * copyleft 2005 DojoDave for DojoCorp
  */

 String readString;

 #include <SoftwareSerial.h>
 SoftwareSerial BT(10, 9); 

 int ledPin = 13;
 int joyPin1 = 0;                 // slider variable connecetd to analog pin 0
 int joyPin2 = 1;                 // slider variable connecetd to analog pin 1
 int value1 = 0;                  // variable to read the value from the analog pin 0
 int value2 = 0;                  // variable to read the value from the analog pin 1

 void setup() {
  pinMode(ledPin, OUTPUT);              // initializes digital pins 0 to 7 as outputs
  Serial.begin(9600);

  delay(2000);
  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
  // Send test message to other device
  BT.println("Hello from Arduino");
 }

 int treatValue(int data) {
  return (data * 9 / 1024 - 4);
 }

 void loop() {
  if (BT.available())
  // if text arrived in from BT serial...
  {
    BT.read();
    // reads the value of the variable resistor 
    value1 = analogRead(joyPin1);   
    // this small pause is needed between reading
    // analog pins, otherwise we get the same value twice
    delay(100);             
    // reads the value of the variable resistor 
    value2 = analogRead(joyPin2);   
  
    digitalWrite(ledPin, HIGH);           
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
    //Serial.print("\nJoystick:\t");
    //Serial.print(treatValue(value1));
    //Serial.print("\t|\t");
    //Serial.println(treatValue(value2));
    BT.println("X");
    BT.println(treatValue(value1));
    BT.println("Y");
    BT.println(treatValue(value2));
}
 }
