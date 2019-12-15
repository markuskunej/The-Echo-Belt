//include NewPing Library
#include "NewPing.h"
//define constants
#define TRIG_PIN_1 2
#define ECHO_PIN_1 2 
#define TRIG_PIN_2 4
#define ECHO_PIN_2 4
#define TRIG_PIN_3 7
#define ECHO_PIN_3 7
#define TRIG_PIN_4 8
#define ECHO_PIN_4 8
#define TRIG_PIN_5 12
#define ECHO_PIN_5 12
#define TRIG_PIN_6 13
#define ECHO_PIN_6 13
#define SONAR_NUM 6
#define MAX_DISTANCE 500
#define MOTOR_PIN_1 3
#define MOTOR_PIN_2 5
#define MOTOR_PIN_3 6
#define MOTOR_PIN_4 9
#define MOTOR_PIN_5 10
#define MOTOR_PIN_6 11

NewPing sonar[SONAR_NUM] = {
  NewPing(TRIG_PIN_1, ECHO_PIN_1, MAX_DISTANCE),
  NewPing(TRIG_PIN_2, ECHO_PIN_2, MAX_DISTANCE),
  NewPing(TRIG_PIN_3, ECHO_PIN_3, MAX_DISTANCE),
  NewPing(TRIG_PIN_4, ECHO_PIN_4, MAX_DISTANCE),
  NewPing(TRIG_PIN_5, ECHO_PIN_5, MAX_DISTANCE),
  NewPing(TRIG_PIN_6, ECHO_PIN_6, MAX_DISTANCE)
};

int motor[6] = {MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4, MOTOR_PIN_5, MOTOR_PIN_6};
long duration;
int cm;
double range = 100.0;
double intensity = 1.0;
int strength;

/*// Array of Ultrasonic sensor pins
int sensors[] = {3, 2};

//create array for 8 ultrasonic sensors*/

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int prev =0;
  int prevprev = 0;
  for(int i = 0; i < SONAR_NUM; i++){
    duration = sonar[i].ping();
    cm = microsecondsToCentimeters(duration);
    Serial.print(i);
    Serial.print(": "); 
    Serial.print(cm);
    Serial.print("cm   ");

    //change motor speed
    if (cm > 0 && cm < range)
    {
        strength = 40 + 110*((range-cm)/range*intensity); 
        analogWrite(motor[i], strength);
        Serial.print(strength); 
        Serial.print("str    ");
    }
    else
    {
        analogWrite(motor[i], 0);
    } 

    //allow for sound to dissipate
    delay(50);
  /*for (int i = 0; i<2; i++){
    //Ping(sensors[i], i);*/
    
  }
  
  Serial.println("");
}

/*
void Ping(int pinNumber, int j){
  //Trigger sensor to send a pulse
  pinMode(pinNumber, OUTPUT);
  //Clear pin to ensure a clean pulse
  digitalWrite(pinNumber, LOW);
  delayMicroseconds(2);
  digitalWrite(pinNumber, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinNumber, LOW);
  
  // The same pin is used to read the signal, 
  // which counts the difference in microseconds
  pinMode(pinNumber, INPUT);
  duration = pulseIn(pinNumber, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  // print distance in serial monitor
  Serial.print(j);
  Serial.print(": ");
  Serial.println(cm);

  // Delay to avoid interference between sensors
  delay(50);
}*/

int microsecondsToCentimeters(long duration){
  // Distance = Time * Velocity
  // The speed of sound is 340 m/s
  // Divide by 2 because the sounds must travel there and back
  return duration*0.034/2; 
}

