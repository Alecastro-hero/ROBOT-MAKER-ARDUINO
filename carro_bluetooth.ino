#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <Ultrasonic.h>
#include <Servo.h>

#define SERVO1 2 // Porta Digital 2 PWM
#define SERVO2 3 // Porta Digital 3 PWM


Servo servo1; // Variável Servo
Servo servo2;

#define INT1 10
#define INT2 11
#define INT3 12
#define INT4 13

#define pino_trigger 8
#define pino_echo 9

Ultrasonic ultrasonic(pino_trigger, pino_echo);
 boolean automatico=false;
   
void setup()
{
 
  Serial.begin(250000);
  Dabble.begin(9600,5,4);  
  pinMode(INT1,OUTPUT);
  pinMode(INT2,OUTPUT);
  pinMode(INT3,OUTPUT);                                                                    
  pinMode(INT4,OUTPUT);
   pinMode(7, OUTPUT);
 pinMode(6, OUTPUT);
  Stop();
}
   
   
void loop() {
  digitalWrite(6,HIGH);//led verde
   
   
  Dabble.processInput();

   
   if(GamePad.isUpPressed()){
      forward(); 
   }
   else if(GamePad.isDownPressed()){
     backward(); 
   }
   else if(GamePad.isLeftPressed()){
      left(); 
    }
    else if(GamePad.isRightPressed()){
      right(); 
    }
    else if(GamePad.isStartPressed()){
      automatico=true;

      while(automatico==true){
        float CM;
        long microsec = ultrasonic.timing();
        CM = ultrasonic.convert(microsec, Ultrasonic::CM);
        Dabble.processInput();

        if(CM <=30){//o número corresponde a distância desejada
          digitalWrite(7,HIGH);
          Stop();
          left();
          delay(1300);
          Stop();
        }
        else{
            Dabble.processInput();
            if(GamePad.isSelectPressed()){
              automatico=false;
            }
            else{
              Dabble.processInput();
              digitalWrite(7, LOW);
              forward();
           }
        }
      }
    }
    else if(GamePad.isSelectPressed()){
      automatico=false;
      
    }
    else{
      Stop(); 
    }
   
}


void forward() {
   digitalWrite(INT1, HIGH);
  digitalWrite(INT2, LOW);
  digitalWrite(INT3, HIGH);
  digitalWrite(INT4, LOW);
  digitalWrite(7,HIGH);
}
      
void backward() {
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, HIGH);
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, HIGH);
  digitalWrite(7,LOW);
}
      
void left() {
  digitalWrite(INT1, HIGH);
  digitalWrite(INT2, LOW);
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, HIGH);
  digitalWrite(7,LOW);  
}
      
void right() {
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, HIGH);
  digitalWrite(INT3, HIGH);
  digitalWrite(INT4, LOW);
  digitalWrite(7,LOW);
}
      
void Stop() {
  digitalWrite(INT1,LOW);
  digitalWrite(INT2,LOW);
  digitalWrite(INT3,LOW);
  digitalWrite(INT4,LOW); 
  digitalWrite(7,LOW); 
}
