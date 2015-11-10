/*********************************************************************************************

  Tutorial: Robot 4x4 con Arduino
  Autor: Oscar Gonzalez - 16 Octubre 2010
  http://blog.bricogeek.com/noticias/tutoriales/tutorial-robot-4x4-con-arduino/

 ********************************************************************************************/
#define MOTOR1_CTL1  8  // I1
#define MOTOR1_CTL2  9  // I2
#define MOTOR1_PWM   11 // EA

#define MOTOR2_CTL1  6  // I3
#define MOTOR2_CTL2  7  // I4
#define MOTOR2_PWM   10 // EB

#define MOTOR_DIR_FORWARD  0
#define MOTOR_DIR_BACKWARD   1

#define trigpin  5
#define echopin 4
#define dangerThresh  10 //threshold for obstacles (in cm)
#define cautionThresh  20 //threshold for obstacles (in cm)

long duration; //time it takes to recieve PING))) signal

void setup()
{
  Serial.begin(9600);
  // Setup pins for motor 1
   pinMode(MOTOR1_CTL1,OUTPUT);
   pinMode(MOTOR1_CTL2,OUTPUT);
   pinMode(MOTOR1_PWM,OUTPUT);
   
  // Setup pins for motor 2
   pinMode(MOTOR2_CTL1,OUTPUT);
   pinMode(MOTOR2_CTL2,OUTPUT);
   pinMode(MOTOR2_PWM,OUTPUT);
   
  //Setup pins for distance sensor
  pinMode(trigpin,OUTPUT);
  pinMode(echopin, INPUT);   
}

void setSpeed(char motor_num, char motor_speed)
{
   if (motor_num == 1)
   {
      analogWrite(MOTOR1_PWM, motor_speed);
   }   
   else
   {
      analogWrite(MOTOR2_PWM, motor_speed);
   }
}

void motorStart(char motor_num, byte direction)
{
  
   char pin_ctl1;
   char pin_ctl2;
   
   if (motor_num == 1)
   {
      pin_ctl1 = MOTOR1_CTL1;
      pin_ctl2 = MOTOR1_CTL2;
   }   
   else
   {
      pin_ctl1 = MOTOR2_CTL1;
      pin_ctl2 = MOTOR2_CTL2;     
   }
  
   switch (direction)
   {
     case MOTOR_DIR_FORWARD:
     {
       digitalWrite(pin_ctl1,LOW);
       digitalWrite(pin_ctl2,HIGH);          
     }
     break; 
          
     case MOTOR_DIR_BACKWARD:
     {
        digitalWrite(pin_ctl1,HIGH);
        digitalWrite(pin_ctl2,LOW);          
     }
     break;         
   }
}

void motorStop(char motor_num)
{
   setSpeed(motor_num, 0);
   if (motor_num == 1)
   {
     digitalWrite(MOTOR1_CTL1,HIGH);
     digitalWrite(MOTOR1_CTL2,HIGH);     
   }
   else
   {
     digitalWrite(MOTOR2_CTL1,HIGH);
     digitalWrite(MOTOR2_CTL2,HIGH);     
   }
}

void loop()
{
  
  int distanceFwd = ping();
  Serial.println(distanceFwd);
  if (distanceFwd>cautionThresh) //if path is clear
  {
    motorStart(1, MOTOR_DIR_FORWARD);  
    setSpeed(1, 200);
    motorStart(2, MOTOR_DIR_FORWARD);      
    setSpeed(2, 200);
  }
  else if (distanceFwd>dangerThresh)
  {
    motorStart(1, MOTOR_DIR_FORWARD);  
    setSpeed(1, 140);
    motorStart(2, MOTOR_DIR_BACKWARD);      
    setSpeed(2, 140);  
  }
  else //if path is blocked
  {
    motorStart(1, MOTOR_DIR_BACKWARD);
    setSpeed(1, 200);
    motorStart(2, MOTOR_DIR_BACKWARD);      
    setSpeed(2, 200);
  }
  delay(50);

}

long ping()
{
// Send out PING))) signal pulse
  pinMode(trigpin, OUTPUT);
  pinMode(echopin,INPUT);
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  //Get duration it takes to receive echo
  duration = pulseIn(echopin, HIGH);
  //Convert duration into distance
  //return duration;
  return duration / 29 / 2;
}



