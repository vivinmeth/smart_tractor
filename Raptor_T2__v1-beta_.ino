/* Smart Tractor */
/* A VivinMeth Product */
// Date:2019-01-03
// version: v1-beta
/* copyright 2019 VivinMeth .Inc All Rights Reserved */
//defines motor driver

int ENA = 10; // MCU PWM Pin 10 to ENA on L298n Board
int IN1 = 9;  // MCU Digital Pin 9 to IN1 on L298n Board 
int IN2 = 8;  // MCU Digital Pin 8 to IN2 on L298n Board
 
int ENB = 5;  // MCU PWM Pin 5 to ENB on L298n Board
int IN3 = 7;  // MCU Digital pin 7 to IN3 on L298n Board
int IN4 = 6;  // MCU Digital pin 6 to IN4 on L298n Board
int rotDirection = 0;
int pressed = false;
  float motorSpeedA,motorSpeedB;


  // defines pins numbers
  #include <Servo.h>
  Servo steer,plough,ultra;
  const int trigPin = 12;
  const int echoPin = 11;
  const int LED_HORNplus=13; 

  const int plough_data=2;
  const int ultra_data=4;
  const int steer_axel_data=3;

  int steer_angle,plough_angle,ultra_angle;
    // defines variables
  long duration;
  float distance;
  int dist_speed=0;
  String lane="RL";

void setup() {
  Serial.begin(9600);// Starts the serial communication
  
  
  Serial.println("Global Scope Setup complete");
  Serial.print("Intialising Ardiuno PinMode Setup.");
  delay(1500);
  steer.attach(steer_axel_data);
  plough.attach(plough_data);
  ultra.attach(ultra_data);
  steer_angle=90;
  steer.write(steer_angle);
  Serial.print(".");
  pinMode(LED_HORNplus,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 delay(1500);
 Serial.println(".");
  
  Serial.println("Ardiuno PinMode Setup complete");
  Serial.print("Intialising MotorDriver PinMode Setup.");
  
  //motor driver
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
   delay(1500);
 Serial.print(".");
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  motorSpeedA = 255;
  motorSpeedB = 255;
  analogWrite(ENA,motorSpeedA);
  analogWrite(ENB,motorSpeedB);
   delay(1500);
 Serial.println(".");
 Serial.println("MotorDriver PinMode Setup complete");
 
}
void loop() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN3, LOW);
if(get_dist()<=35){
  digitalWrite(LED_HORNplus, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
   plough_angle=90;
  plough.write(plough_angle);
  delay(2500);
  digitalWrite(LED_HORNplus, LOW);
  delay(500);
  if(get_dist()<=35){
  digitalWrite(LED_HORNplus, HIGH);
  delay(2000);
  if(get_dist()<=35){
  steer_angle=135;
  steer.write(steer_angle);
  digitalWrite(LED_HORNplus, LOW);
  delay(2000);
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  delay(2000);
  steer_angle=90;
   digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  steer.write(steer_angle);
  delay(1000);
  steer_angle=45;
   digitalWrite(IN2, HIGH);
  digitalWrite(IN4, LOW);
  steer.write(steer_angle);
  delay(2000);
  steer_angle=135;
   digitalWrite(IN2, LOW);
  digitalWrite(IN4, HIGH);
  steer.write(steer_angle);
  delay(1000);
   plough_angle=90;
    digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
   steer_angle=90;
  steer.write(steer_angle);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  delay(500);
  plough.write(plough_angle);
}
}
}
else{
  plough_angle=180;
  plough.write(plough_angle);
  digitalWrite(LED_HORNplus, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN4, HIGH);
  steer_angle=90;
  delay(1000);
  dist_speed+=1;
  if(dist_speed==20){
    if(lane="RL"){
      digitalWrite(IN2, LOW);
      digitalWrite(IN4, LOW);
      
      steer_angle=45;
      steer.write(steer_angle);
      delay(2000);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN4, LOW);
      delay(3000);
      lane="LR";
    }
    else if(lane=="LR"){
      digitalWrite(IN2, LOW);
      digitalWrite(IN4, LOW);
      
      steer_angle=135;
      steer.write(steer_angle);
      delay(2000);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN4, LOW);
      delay(3000);
      lane="RL";
    }
    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
    steer_angle=90;
    steer.write(steer_angle);
    dist_speed=0;
    delay(1000);
    dist_speed=0;
  }
  }


steer.write(steer_angle);
}
float get_dist(){
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

