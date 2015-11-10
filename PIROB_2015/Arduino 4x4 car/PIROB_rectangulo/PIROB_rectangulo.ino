/*********************************************************************************************

  Tutorial: Robot 4x4 con Arduino
  Autor: Luis Sanchez 
  Partiendo de:
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

void setup()
{
  // Setup pins for motor 1
   pinMode(MOTOR1_CTL1,OUTPUT);
   pinMode(MOTOR1_CTL2,OUTPUT);
   pinMode(MOTOR1_PWM,OUTPUT);
   
  // Setup pins for motor 2
   pinMode(MOTOR2_CTL1,OUTPUT);
   pinMode(MOTOR2_CTL2,OUTPUT);
   pinMode(MOTOR2_PWM,OUTPUT);   
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
  // Start motors!
  motorStart(1, MOTOR_DIR_FORWARD);  
  setSpeed(1, 200);
  motorStart(2, MOTOR_DIR_FORWARD);      
  setSpeed(2, 200);
  
  delay(2000);
  
  motorStart(1, MOTOR_DIR_FORWARD);  
  setSpeed(1, 140);
  motorStart(2, MOTOR_DIR_BACKWARD);      
  setSpeed(2, 140);  
  
  delay(1200);

  motorStart(1, MOTOR_DIR_FORWARD);  
  setSpeed(1, 200);
  motorStart(2, MOTOR_DIR_FORWARD);      
  setSpeed(2, 200);
  
  delay(1000);
  
  motorStart(1, MOTOR_DIR_FORWARD);  
  setSpeed(1, 140);
  motorStart(2, MOTOR_DIR_BACKWARD);      
  setSpeed(2, 140);  
  
  delay(1200);
  
   
}


