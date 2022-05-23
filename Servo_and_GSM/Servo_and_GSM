#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial SIM900A(10,11);
Servo myservo;  // create servo object to control a servo

int pos = 90;    // variable to store the servo position
int inPin = 7; 
int val=LOW;
boolean forward = true;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(inPin, INPUT);
  SIM900A.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println ("SIM900A Ready");
  delay(100);
}

void loop() {
  if(forward == true)
  { 
    pos+=3;
    myservo.write(pos);   
    if(pos == 165)
    {
      forward = false;          
    }

    val = digitalRead(inPin);
    
    Serial.println (val);
    Serial.println ("\t");
    if(val==HIGH)
    {
      SendMessage();
      val=LOW;
      delay(11000);
    }
    delay(1000);
  }
  else
  { 
    pos-=3;
    myservo.write(pos);
    if(pos == 15)
    {
      forward = true;          
    } 

    val = digitalRead(inPin);
    
    Serial.println (val);
    Serial.println ("\t");
    if(val==HIGH)
    {
      SendMessage();
      val=LOW;
      delay(11000);
    }
    delay(1000);
  }
}

 void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+917668198550\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println("Alert There is a stanger in your home");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent ");
}
