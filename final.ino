/*
  *University of Computer Studies, Mandalay(UCSM)
  *2023-2024 Acmadic year
  *Second year second semester project
  *Obstacle avoiding and line followinf car usind arduino
*/

//Define motor
#define enA 5
#define in1 6
#define in2 7
#define in3 8
#define in4 9
#define enB 10

//Define ultrasonic sensor
#define trig A2
#define echo 3

//Define ir sensor
#define ir_left A0 //Left
#define ir_right A1 //Right

//For ultrasonic sensor
long duration;
int distance;

//For motor
int wait_millis=500;

//Set motor speed
int speed=255;
int r_speed=200;

/*
  *int light_threshold=650;
  *int line_number;
*/

//Read distance
int ultrasonic()
{
  //This function will return distance
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  //Active trig for 10 microsecond
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  //Read the echo pin,return soundwave travel time in microseconds
  duration=pulseIn(echo, HIGH);
  //Calculate distance
  distance=duration * 0.034 / 2;
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");
  return distance;
}

//Read left sensor value
int r_left()
{
  int r_left=digitalRead(ir_left);
  //Serial.print(r_left);
  return r_left;
}

//Read right sensor value
int r_right()
{
  int r_right=digitalRead(ir_right);
  //Serial.print(r_right);
  return r_right;
}

void setup() {
  // put your setup code here, to run once:
  //Setup motor
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  //Setup ultrasonic
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //Setup ir sensor
  pinMode(ir_left, INPUT);
  pinMode(ir_right, INPUT);

  //Set motor forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //Set motor speed
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  //Wait a second
  delay(wait_millis);
  //Break
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //while(true){
    int dist = ultrasonic();
    //Serial.printf("Distance is %s cm\n",dist);
    if(dist < 30)
    {
      //Serial.print("Avoid!");
      //backward();
      //turnLeft();
      //turnLeft();
       avoid();
    }
    else
    {
      int v_left = r_left();
      int v_right = r_right();
      //Both 
      if(v_left == LOW && v_right == LOW) forward();
      //
      else if(v_left == LOW && v_right == HIGH) turn_left();
      //
      else if(v_left == HIGH && v_right == LOW) turn_right();
      //
      else if(v_left == HIGH && v_right == HIGH) stop();
      else stop();
    }
  //}

  //Testing
  /*while(Serial.available())
  {
    char c=Serial.read();
    switch(c)
    {
      case 'w':forward();break;
      case 's':backward();break;
      case 'a':turn_left();break;
      case 'd':turn_right();break;
      default:stop();
    }
  }*/

}

//Turn forward
void forward()
{
  //Serial.print("Move forward");
  //Set motor forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //Set motor speed
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  //Wait a second
  delay(wait_millis);
  //Break
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

//Turn left
void turn_left()
{
  //Serial.print("Adjust to left");
  //Set motor to left
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  //Set speed
  //analogWrite(enA, speed);
  analogWrite(enB, r_speed);
  //Wait a second
  delay(wait_millis);
  //Break
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

//Turn right
void turn_right()
{
  //Serial.print("Adjust to right");
  //Set motor to right
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  //Set speed
  analogWrite(enA, r_speed);
  //analogWrite(enB, speed);
  //Wait a second
  delay(wait_millis);
  //Break
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

//Set backward
void backward()
{
  //Serial.print("MOve backward");
  //Set motor to backward
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);
  //Set speed
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  //Wait a second
  delay(wait_millis);
  //Break
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

//Set stop
void stop()
{
  //Serial.print("Stop");
  //Set motor STOP
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
}

//
void stop(int time){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  delay(time);
}
//Avoid
/*void avoid()
{
  digitalWrite(in2, LOW);
}*/

void avoid() {
  stop(wait_millis);
  //180 De
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 255);
  delay(1000);
  stop(wait_millis);
  //forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2 ,LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(1000);
  stop(wait_millis);
  //Turn right 90 De
  digitalWrite(in1, HIGH);
  digitalWrite(in2 ,LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4 ,LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 0);
  delay(1000);
  stop(wait_millis);
  //forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2 ,LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(1000);
  stop(wait_millis);
  //Turn right
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3 ,LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 0);
  delay(1000);
  stop(wait_millis);
  //forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2 ,LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(1000);
  stop(wait_millis);
  //Turn left
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA,0);
  analogWrite(enB,255);
  delay(1000);
  stop(wait_millis);
}
