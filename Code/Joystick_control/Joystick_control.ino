/*//initialization
float set_x,set_y,set_z,set_w;
// robots initial position
float x = 0, y = 0, z = 500, w = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  Serial.begin(9600);
  Serial.println("Set the joystick in zero position !!");
  delay(5000);
  set_x = analogRead(A0);
  set_y = analogRead(A1);
  set_z = analogRead(A8);
  set_w = analogRead(A9);
  Serial.println(String(set_x)+String("\t")+String(set_y)+String("\t")+String(set_z)+String("\t")+String(set_w)+String("\t"));
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  x  = x + (analogRead(A0)-set_x)/100;
  y  = y + (analogRead(A1)-set_y)/100;
  z  = z + (analogRead(A8)-set_z)/100;
  w  = w + (analogRead(A9)-set_w)/100;
  
  Serial.println(String(x,2)+String("a")+String(y,2)+String("a")+String(z,2)+String("a")+String(w,2));
  
}*/
//-----------------------------------------------------------------------
//--------------------------Compass Test --------------------------------
//-----------------------------------------------------------------------

#include <QMC5883LCompass.h>

QMC5883LCompass compass;
float  timeout = 100*100,time_cal =  0.0, start_time = 0.0;
float  min_x = -100000, min_y = -100000, max_x = 100000, max_y = 100000, phi = 0.0;
void setup() {
  Serial.begin(9600);
  
  compass.init();
  compass.setMode(0x01, 0x0C, 0x00, 0x00);                  //Continuos, 200 Hz, 2G, 512 (MODE, ODR, RNG, OSR)
  compass.setCalibration(-1090, 16, -1257, 0, -1, 1183);
  Serial.println("Rotate the sensor from 0 to 360");
  delay(1000);
  float startTime = millis();
  while(timeout > time_cal){
      // Read compass values
       compass.read();
    
      // Return XYZ readings
      float x = compass.getX();
      float y = compass.getY();
      if(x > min_x)
        min_x = x;
      if(x < max_x)
        max_x = x; 
      if(y > min_y)
        min_y = y;
      if(y < max_y)
        max_y = y;
        
     Serial.println(String(max_x)+String("\t")+String(max_y)+String("\t")+String(min_x)+String("\t")+String(min_y)+String("\t"));
     time_cal = millis() - start_time;       
  }
  delay(2000);
}

void loop() {

  // Read compass values

  compass.read();
  
  // Return XYZ readings
  float map_x = map(compass.getX(),min_x,max_x,  255,-255);
  float map_y = map(compass.getY(),min_y,max_y, -255, 255);
  float mag = sqrt(pow(map_x,2) + pow(map_y,2));
  //float theta = radians(90);
  //map_x =  map_x*(0) + map_y*(1);
  //map_y =  map_x*(-1) + map_y*(0);
  
  phi = degrees(acos(abs(map_y)/mag));
  //second quadrant
  if (map_x > 0 && map_y > 0){
     phi = 180.0 - phi;
  }
  //Third quadrant
  else if (map_x < 0 && map_y > 0){
     phi = 180.0 + phi;
  }
  //Fourth Quadrant
  else if (map_x < 0 && map_y < 0){
     phi = 360 - phi;
  }
  Serial.print(map_x);Serial.print("\t");Serial.print(map_y);Serial.print("\t");Serial.println(phi);
  
}
