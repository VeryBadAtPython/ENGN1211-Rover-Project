// C++ code
//

#include <Servo.h> //Import servo package
Servo myservo;  // create servo object to control a servo

// H-bridge Pins
const int pin7  = 4;
const int pin2  = 3;
const int pin14 = 6;
const int pin11 = 5;

// Sonar Pins
const int trig  = 8;
const int echo  = 9;

// Servo Pins
const int serv  = 10;
int pos         = 90;

// Variable Speed Motor Pins
// TODO

void setup(){
  Serial.begin(9600);
    pinMode(pin7, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin14, OUTPUT);
    pinMode(pin11, OUTPUT);
    
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);

    myservo.attach(serv);
}

// ================ H-Bridge Setup ================
// Drive Direction H-Bridge Control Functions

int lFull = 200;
int rFull = 245;

void leftForwards(){
  analogWrite(pin7,lFull);
  digitalWrite(pin2,LOW);
}
void rightForwards(){
  analogWrite(pin14,rFull);
  digitalWrite(pin11,LOW);
}
void leftBackwards(){
  digitalWrite(pin7,LOW);
  analogWrite(pin2,lFull);
}
void rightBackwards(){
  digitalWrite(pin14,LOW);
  analogWrite(pin11,rFull);
}
void leftStop(){
  digitalWrite(pin7,LOW);
  digitalWrite(pin2,LOW);
}
void rightStop(){
  digitalWrite(pin14,LOW);
  digitalWrite(pin11,LOW);
}

void lft(){
  rightForwards();
  leftBackwards();
  }

void rht(){
  rightBackwards();
  leftForwards();
  }

void fwd(){
  rightForwards();
  leftForwards();
  }

void bwd(){
  rightBackwards();
  leftBackwards();
  }

void stp(){
  rightStop();
  leftStop();
  }

// ================= Specified radius turn functions
int rturn = 1300;
int lturn = 1550;


void r90(){
  rht();
  delay(rturn);
  stp();
  }

void l90(){
  lft();
  delay(lturn);
  stp();
  }


// ================= Sonar Distance to pingtime function
// Returns the pulse duration for distances in (cm) from either side.

int sPing(long sdist){
  long sTime = 57.873*(sdist) + 252.66;
  return round(sTime);
  }

int fPing(long fdist){
  long fTime = 57.873*(fdist-2.5) + 252.66;
  return round(fTime);
  }
  

// ================= Sonar Return Function ================
// Returns the pingtime for a single sonar measurement

long pulseRet(){
  long duration;
  
  //Trigger a pulse on the sonar module
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  //measure the duration of the echo
  duration = pulseIn(echo, HIGH);
  return duration;
  }


// ================= Specified radius turn functions
int rturnc = 0.75*rturn;
int lturnc = 0.75*lturn;

long ping;

void r90c(){
  rht();
  delay(rturnc);
  stp();
  myservo.write(180);
  delay(500);
  ping = pulseRet();  
    while( ping > sPing(3.5) ){
      rht();
      delay(100);
      ping = pulseRet();
  }
  stp();
  myservo.write(75);
  delay(500);
}

void l90c(){
  lft();
  delay(rturnc);
  stp();
  myservo.write(180);
  delay(500);
  ping = pulseRet();  
    while( ping > sPing(3.5) ){
      lft();
      delay(100);
      ping = pulseRet();
  }
  stp();
  myservo.write(75);
  delay(500);
  }

// ================= fwdL / fwdR ==================



void fwdL(){
  ping = pulseRet();  
    while( ping > fPing(3.5) ){
      fwd();
      ping = pulseRet();
   };
   l90();
}

void fwdR(){
  ping = pulseRet();  
    while( ping > fPing(3.5) ){
      fwd();
      ping = pulseRet();
   };
   r90();
}

// ================= Maze Solver ==================

void loop(){
   // Drive to first wall and turn
  myservo.write(75);
  delay(1000);
  fwd();
  delay(4000);
  ping = pulseRet();
  fwdR();
  
  // Keep going forward untill right pos
  fwd();
  delay(8250);
  r90();
  
  stp();
  delay(1000);

  fwdL();

   fwd();
   delay(1000);


   // Keep going to wall then right
  fwdR();
  stp();
  delay(500);
  fwdR();
  stp();
  delay(500);
  fwdL();

   fwd();
   delay(500);
   stp();
}
