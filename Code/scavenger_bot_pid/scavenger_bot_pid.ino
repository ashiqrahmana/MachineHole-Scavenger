#include <PID_v1.h>

const uint16_t PWMA = 19;         
const uint16_t AIN2 = 4;         
const uint16_t AIN1 = 2;         


const uint16_t ENCA = 5;        
const uint16_t ANALOG_WRITE_BITS = 10;  
const uint16_t MAX_PWM = pow(2, ANALOG_WRITE_BITS)-1;  
const uint16_t MIN_PWM = 118;    

unsigned long nowTime = 0;       // updated on every loop  
unsigned long startTimeA = 0;    // start timing A interrupts  
String spulses;

unsigned long countIntA = 0;     // count the A interrupts  
 
double periodA = 0;              // motor A period  
       // motor B period  
// PID   
const unsigned long SAMPLE_TIME = 1;  // time between PID updates  
//const unsigned long INT_COUNT = 20;     // sufficient interrupts for accurate timing  
double setpointA =8344;      // setpoint is rotational speed in Hz  
double inputA = 0;              // input is PWM to motors  
double outputA = 0;             // output is rotational speed in Hz  
      // output is rotational speed in Hz  
double KpA = 0.201, KiA = 0.00, KdA = 0.2;  

PID motorA(&inputA, &outputA, &setpointA, KpA, KiA, KdA, DIRECT);  

void setup(){  
 initMotors();  
 initEncoders();  
 initPWM();  
 Serial.begin(115200);  
   ledcSetup(0, 5000, 10);
  ledcAttachPin(PWMA, 0);
// while(Serial.available()==0)
//  {
//  
//}  
//  spulses=Serial.readStringUntil('\n');
//  setpointA=spulses.toInt();
}
void loop(){  
  motorA.Compute();  
  //motorB.Compute();  
  forwardA((int)outputA);  
  Serial.println(outputA);
 // forwardB((int)outputB);  
    

}  
void forwardA(uint16_t pwm){  
  digitalWrite(AIN1, LOW);  
  digitalWrite(AIN2, HIGH);  
  ledcWrite(0,pwm);
}  
//void forwardB(uint16_t pwm){  
//  digitalWrite(BIN1, LOW);  
//  digitalWrite(BIN2, HIGH);  
//  analogWrite(PWMB, pwm);  
//}  
void reverseA(uint16_t pwm){  
  digitalWrite(AIN1, HIGH);  
  digitalWrite(AIN2, LOW);  
  ledcWrite(0,pwm);
}  
//void reverseB(uint16_t pwm){  
//  digitalWrite(BIN1, HIGH);  
//  digitalWrite(BIN2, LOW);    
//  analogWrite(PWMB, pwm);  
//}  
void brakeA(){  
  digitalWrite(AIN1, LOW);  
  digitalWrite(AIN2, LOW);  
}  
//void brakeB(){  
//  digitalWrite(BIN1, LOW);  
//  digitalWrite(BIN2, LOW);  
//}  
  
void initMotors(){  
  pinMode(AIN1, OUTPUT);  
  pinMode(AIN2, OUTPUT);  
  pinMode(PWMA, OUTPUT);  
//  pinMode(BIN1, OUTPUT);  
//  pinMode(BIN2, OUTPUT);  
//  pinMode(PWMB, OUTPUT);  
  

}  
void IRAM_ATTR  isr_A(){  

  countIntA++;  
inputA=countIntA;
//if (countIntA==setpointA)
//countIntA=0;
}  
void initEncoders(){  
  pinMode(ENCA,INPUT);  
  attachInterrupt(digitalPinToInterrupt(ENCA),isr_A, RISING);  
  //attachInterrupt(digitalPinToInterrupt(ENCB),isr_B, RISING);  
}  
void initPWM(){    
  motorA.SetOutputLimits(MIN_PWM, MAX_PWM);  
  //motorB.SetOutputLimits(MIN_PWM, MAX_PWM);  
  motorA.SetSampleTime(SAMPLE_TIME);  
  //motorB.SetSampleTime(SAMPLE_TIME);  
  motorA.SetMode(AUTOMATIC);  
  //motorB.SetMode(AUTOMATIC);  
}  

//void isr_B(){  
//  // count sufficient interrupts to get accurate timing  
//  // inputX is the encoder frequency in Hz  
//  countIntB++;  
//  if (countIntB == INT_COUNT){  
//    inputB = (float) INT_COUNT * 1000 / (float)(nowTime - startTimeB);  
//    startTimeB = nowTime;  
//    countIntB = 0;  
//  }  
//}  
