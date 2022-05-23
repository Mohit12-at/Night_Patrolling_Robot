int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  pinMode(A0, INPUT); // initialize Right sensor as an inut
  pinMode(A1, INPUT); // initialize Left sensor as as input

}

void loop() {
  int LEFT_SENSOR = analogRead(A0);
  int RIGHT_SENSOR = analogRead(A1);
  
  Serial.println("right:");
  Serial.println(RIGHT_SENSOR);
  Serial.println("left:");
  Serial.println(LEFT_SENSOR);
  
if(RIGHT_SENSOR < 500 && LEFT_SENSOR < 500) //FORWARD
{
            digitalWrite(motor1pin1, HIGH);
            digitalWrite(motor1pin2, LOW);
            digitalWrite(motor2pin1, HIGH);
            digitalWrite(motor2pin2, LOW);

}

 else if(RIGHT_SENSOR >500 && LEFT_SENSOR < 500) //LEFT
 {
            digitalWrite(motor1pin1, LOW);
            digitalWrite(motor1pin2, HIGH);
            digitalWrite(motor2pin1, HIGH);
            digitalWrite(motor2pin2, LOW);
            
}

else if(RIGHT_SENSOR <500 && LEFT_SENSOR > 500) //RIGHT
 {
              digitalWrite(motor1pin1, HIGH);
              digitalWrite(motor1pin2, LOW);
              digitalWrite(motor2pin1, LOW);
              digitalWrite(motor2pin2, HIGH);
             

}

else if(RIGHT_SENSOR >500 && LEFT_SENSOR > 500) //BACK
{
              digitalWrite(motor1pin1, LOW);
              digitalWrite(motor1pin2, LOW);
              digitalWrite(motor2pin1, LOW);
              digitalWrite(motor2pin2, LOW);
              delay(1000); 
 }
}
