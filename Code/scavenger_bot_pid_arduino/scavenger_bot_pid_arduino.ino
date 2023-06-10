#include <PID_v1.h>

const uint16_t PWMA = 8;         
const uint16_t AIN2 = 10;         
const uint16_t AIN1 = 11;  

const uint16_t PWMB = 9;         
const uint16_t BIN2 = 7;         
const uint16_t BIN1 = 6; 
 
const uint16_t PWMC = 48;         
const uint16_t CIN2 = 50;         
const uint16_t CIN1 = 52;  

const uint16_t PWMD = 48;         
const uint16_t DIN2 = 50;         
const uint16_t DIN1 = 52;  

// THEY ARE DEFINED!!
const uint16_t ENCA1=40;      //encoder pin  
const uint16_t ENCA2=41;

const uint16_t ENCB1=42;      //encoder pin  
const uint16_t ENCB2=43;

const uint16_t ENCC1=44;      //encoder pin  
const uint16_t ENCC2=45;

const uint16_t ENCD1=46;      //encoder pin  
const uint16_t ENCD2=47;
//---------------

const uint16_t ANALOG_WRITE_BITS = 8;  
const uint16_t MAX_PWM = pow(2, ANALOG_WRITE_BITS)-1;  
const uint16_t MIN_PWM = 0;    

//String spulses;

unsigned long countIntA = 0;     
unsigned long countIntB = 0;     
unsigned long countIntC = 0;     
unsigned long countIntD = 0;     


// PID   
const unsigned long SAMPLE_TIME = 1;  // time between PID updates  

double setpointA = 0;     
double inputA = 0;              
double outputA = 0;        

double setpointB = 0;      
double inputB = 0;              
double outputB = 0;

double setpointC = 0;      
double inputC = 0;              
double outputC = 0;

double setpointD = 0;      
double inputD = 0;              
double outputD = 0;

double KpA = 0.2, KiA = 0.00, KdA = 0.2;  

PID motorA(&inputA, &outputA, &setpointA, KpA, KiA, KdA, DIRECT);  
PID motorB(&inputB, &outputB, &setpointB, KpA, KiA, KdA, DIRECT);  
PID motorC(&inputC, &outputC, &setpointC, KpA, KiA, KdA, DIRECT);  
PID motorD(&inputD, &outputD, &setpointD, KpA, KiA, KdA, DIRECT);  

void setup(){  
 initMotors();  
 initEncoders();  
 initPWM();  
 Serial.begin(115200);  

// while(Serial.available()==0)
//  {
//  
//}  
//  spulses=Serial.readStringUntil('\n');
//  setpointA=spulses.toInt();
}
void loop(){  
  motorA.Compute();  
  motorB.Compute(); 
  motorC.Compute();
  motorD.Compute();
   
  //motorB.Compute();  
  forwardA((int)outputA);  
  forwardB((int)outputB);  
  forwardC((int)outputC);  
  forwardD((int)outputD);
    
  Serial.println(outputC);
  Serial.println(inputC);
 // forwardB((int)outputB);  
}  

void forwardA(uint16_t pwm_a){  
  digitalWrite(AIN1, LOW);  
  digitalWrite(AIN2, HIGH);  
  analogWrite(PWMA,pwm_a);
}  
void forwardB(uint16_t pwm_b){  
  digitalWrite(BIN1, LOW);  
  digitalWrite(BIN2, HIGH);  
  analogWrite(PWMB,pwm_b);
}  
void forwardC(uint16_t pwm_c){  
  digitalWrite(CIN1, LOW);  
  digitalWrite(CIN2, HIGH);  
  analogWrite(PWMC,pwm_c);
}  

void forwardD(uint16_t pwm_c){  
  digitalWrite(CIN1, LOW);  
  digitalWrite(CIN2, HIGH);  
  analogWrite(PWMC,pwm_c);
}  

//void reverseA(uint16_t pwm){  
//  digitalWrite(AIN1, HIGH);  
//  digitalWrite(AIN2, LOW);  
//  analogWrite(PWMB,pwm);
//}  
//void reverseB(uint16_t pwm){  
//  digitalWrite(BIN1, HIGH);  
//  digitalWrite(BIN2, LOW);    
//  analogWrite(PWMB, pwm);  
//}  

void brakeA(){  
  digitalWrite(AIN1, LOW);  
  digitalWrite(AIN2, LOW);  
}  

void brakeB(){  
  digitalWrite(BIN1, LOW);  
  digitalWrite(BIN2, LOW);  
}
  
void brakeC(){  
  digitalWrite(CIN1, LOW);  
  digitalWrite(CIN2, LOW);  
}  

void brakeD(){  
  digitalWrite(DIN1, LOW);  
  digitalWrite(DIN2, LOW);  
}  
//void brakeB(){  
//  digitalWrite(BIN1, LOW);  
//  digitalWrite(BIN2, LOW);  
//}  
  
void initMotors(){  
  pinMode(AIN1, OUTPUT);  
  pinMode(AIN2, OUTPUT);  
  pinMode(PWMA, OUTPUT);  
  pinMode(BIN1, OUTPUT);  
  pinMode(BIN2, OUTPUT);  
  pinMode(PWMB, OUTPUT);  
  pinMode(CIN1, OUTPUT);  
  pinMode(CIN2, OUTPUT);  
  pinMode(PWMC, OUTPUT);  
    
  pinMode(DIN1, OUTPUT);  
  pinMode(DIN2, OUTPUT);  
  pinMode(PWMD, OUTPUT);

}  
void isr_A(){  

  countIntA++;  
inputA=countIntA;

}  
void isr_B(){  

  countIntB++;  
inputB=countIntB;

}  
void isr_C(){  

  countIntC++;  
inputC=countIntC;

}  

void isr_D(){  

  countIntD++;  
inputD = countIntD;

}  
void initEncoders(){  
  pinMode(ENCA1,INPUT);  
  pinMode(ENCA2,INPUT);  
  attachInterrupt(digitalPinToInterrupt(ENCA1),isr_A, RISING);  
  attachInterrupt(digitalPinToInterrupt(ENCA2),isr_A, RISING);  
  pinMode(ENCB1,INPUT);  
  pinMode(ENCB2,INPUT);  
  attachInterrupt(digitalPinToInterrupt(ENCB1),isr_B, RISING);  
  attachInterrupt(digitalPinToInterrupt(ENCB2),isr_B, RISING); 
  pinMode(ENCC1,INPUT); 
  pinMode(ENCC2,INPUT);   
  attachInterrupt(digitalPinToInterrupt(ENCC1),isr_C, RISING);  
  attachInterrupt(digitalPinToInterrupt(ENCC2),isr_C, RISING);   
  pinMode(ENCD1,INPUT); 
  pinMode(ENCD2,INPUT);   
  attachInterrupt(digitalPinToInterrupt(ENCD1),isr_D, RISING);  
  attachInterrupt(digitalPinToInterrupt(ENCD2),isr_D, RISING);   
}  

void initPWM(){    
  motorA.SetOutputLimits(MIN_PWM, MAX_PWM);  
  motorA.SetSampleTime(SAMPLE_TIME);  
  motorA.SetMode(AUTOMATIC);  
  
  motorB.SetOutputLimits(MIN_PWM, MAX_PWM);  
  motorB.SetSampleTime(SAMPLE_TIME);  
  motorB.SetMode(AUTOMATIC);  
  
  motorC.SetOutputLimits(MIN_PWM, MAX_PWM);  
  motorC.SetSampleTime(SAMPLE_TIME);  
  motorC.SetMode(AUTOMATIC);  

  motorD.SetOutputLimits(MIN_PWM, MAX_PWM);  
  motorD.SetSampleTime(SAMPLE_TIME);  
  motorD.SetMode(AUTOMATIC);  
}  
