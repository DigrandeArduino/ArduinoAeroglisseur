#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Servo.h>
Servo servoLev;
Servo servoAv;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int const Lev=6;
int const Vol=11;
int const Av=9;
int const On=10;
float IsOn;
int val; 

int const MLevA=0;
int const MLevD=1;
int const MAvG=5;
int const MAvD=3;

float tempsLev;
float tempsVol;
float tempsAv;
float dir;

float SortieLev1;
float SortieLev2;
float SortieVol;
float SortieAv1;
float SortieAv2;

void setup() {
  Serial.begin(9600);
  Serial.println("enmarche");
  pinMode(Lev, INPUT);
  pinMode(Av, INPUT);
  pinMode(Vol, INPUT);
  pinMode(On, INPUT);
  Serial.println("ok");
  pwm.begin();
  pwm.setPWMFreq(60);  

}

void loop() {
  IsOn= pulseIn(On, HIGH);
  IsOn+=-995;
  //Serial.println(IsOn);
  if(IsOn>500){
  tempsLev= pulseIn(Lev, HIGH);
  //Serial.println("temps Levitation");
  //Serial.println(tempsLev);
  
  tempsVol= pulseIn(Vol, HIGH );
  //Serial.println("temps volets");
  //Serial.println(tempsVol);
  
  tempsAv= pulseIn(Av, HIGH);
  //Serial.println("temps Avancer");
  //Serial.println(tempsAv-1070);

  tempsLev+=-1000;
  SortieLev1=165+(tempsLev/800)*395;
  SortieLev2=255+(tempsLev/800)*180;
  //Serial.println(SortieLev1);
  //Serial.println(SortieLev2);
  pwm.setPWM(MLevA, 0, SortieLev2);
  pwm.setPWM(MLevD, 0, SortieLev1);

  tempsVol+=-1065;
  tempsAv+=-1000;
  dir=(tempsVol/800)-0.51;
  SortieAv1=415-((tempsAv/800)*300)+(dir)*300;
  SortieAv2=415-((tempsAv/800)*300)+(-dir)*300;
  //Serial.println(SortieAv1);
  Serial.println(SortieAv2);
  //Serial.println(dir);
  pwm.setPWM(MAvG, 0, SortieAv1);
  pwm.setPWM(MAvD, 0, SortieAv2);
  }
  else{
    pwm.setPWM(MLevA, 0, 0);
    pwm.setPWM(MLevD, 0, 0);
    pwm.setPWM(MAvG, 0, 0);
    pwm.setPWM(MAvD, 0, 0);    
  }
  
  delay(10);
}
