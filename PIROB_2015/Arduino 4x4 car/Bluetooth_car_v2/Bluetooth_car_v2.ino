#include <SoftwareSerial.h> //Librería que permite establecer comunicación serie en otros pins

#define MOTOR1_CTL1  8  // I1
#define MOTOR1_CTL2  9  // I2
#define MOTOR1_PWM   11 // EA

#define MOTOR2_CTL1  6  // I3
#define MOTOR2_CTL2  7  // I4
#define MOTOR2_PWM   10 // EB

#define MOTOR_DIR_FORWARD  0
#define MOTOR_DIR_BACKWARD   1

 
//Aquí conectamos los pins RXD,TDX del módulo Bluetooth.
SoftwareSerial BT(12,13); //12 RX, 13 TX.
 
//char cadena[255]; //Creamos un array de caracteres de 256 cposiciones
int i=0; //Tamaño actual del array
char command ='S'; 
void setup()
{
  BT.begin(9600);
  Serial.begin(9600);

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
 if(BT.available() > 0){
    command = BT.read();
    Serial.println(command);
    //Change pin mode only if new command is different from previous.  
    //Serial.println(command);
    switch(command){
    case 'S': 
        motorStop(1);
        motorStop(2);
        break;
    case 'F': 
          motorStart(1, MOTOR_DIR_FORWARD);  
          setSpeed(1, 200);
          motorStart(2, MOTOR_DIR_FORWARD);      
          setSpeed(2, 200);
          break;
     case 'B':
          motorStart(1, MOTOR_DIR_BACKWARD);  
          setSpeed(1, 200);
          motorStart(2, MOTOR_DIR_BACKWARD);      
          setSpeed(2, 200);
          break;
      case 'R':
          motorStart(1, MOTOR_DIR_FORWARD);  
          setSpeed(1, 200);
          motorStart(2, MOTOR_DIR_BACKWARD);      
          setSpeed(2, 200);
          break;
   case 'L':
         motorStart(2, MOTOR_DIR_FORWARD);  
          setSpeed(2, 200);
          motorStart(1, MOTOR_DIR_BACKWARD);      
          setSpeed(1, 200);
          break;
   case 'G':
         motorStart(2, MOTOR_DIR_FORWARD);  
          setSpeed(2, 255);
          motorStart(1, MOTOR_DIR_FORWARD);      
          setSpeed(1, 50);
          break;
   case 'I':
         motorStart(1, MOTOR_DIR_FORWARD);  
          setSpeed(1, 255);
          motorStart(2, MOTOR_DIR_FORWARD);      
          setSpeed(2, 50);
          break;
     default:  //Get velocity
      if(command=='q'){
        int velocity = 255;//Full velocity
        
      }
    }
  }
}
 
