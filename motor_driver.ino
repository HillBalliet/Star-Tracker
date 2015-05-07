//Hill Balliet
//26 April 2015

//Fundamental constants

//This is the earth's rotational velocity in radians per second
float EARTHROTATION = -0.00007292115;
#define SECINMIN 60.0
#define METERSTOINCHES 39.3701

//These are the characteristics of the apparatus

//This is the initial angle of the apparatus at the sighted hinge in radians
float INITANGLE = 0.621044;
//This is the initial distance of the base of the dynamic triangle in meters
float INITDISTANCE = 0.130;
//This is the length of the board that the camera mounts to in meters
float LENGTHA = 0.135;
//This is the length of the board that attaches to the block on the screw in meters
float LENGTHB = 0.0825;
//This is the number of threads per inch on your screw
#define THREADDENSITY 20.0



//These are the characteristics of the motor

//The motor's max torque in Nm
float TORQUE = 3.8245935;
//The motor's efficiency
#define EFFICIENCY 0.5
//This is the maximum number of revolutions per second of your motor
float MAXRPM = 0.015625;
//This is the efficiency of your motor (the ratio of the power output in watts to the power input in watts)
#define EFFICIENCY 0.7
//The motor's resistance in Ohms
#define RESISTANCE 10



//These are characteristics of the arduino

//This is the max output voltage of the arduino
#define MAXVOLTAGE 4.2
//This is fully "on" for pulse width modulation
#define PWMON 255

//The program needs to remember the configuration of the apparatus at a given time
float currentAngle = INITANGLE;
float currentDistance = INITDISTANCE;

//currentSpeed is in revolutions per second
float currentSpeed = 0;
unsigned long startTime;

void setup() {
  Serial.begin(9600);
  
  initMotors();
    
  startTime = millis();
}

void loop() {
  
  //set elapsed time
  //reset the start time
  unsigned long elapsedTime = millis() - startTime;
  startTime = millis();
  
  //Calculate the appropriate speed
  calcSpeed(elapsedTime);
  //Drive the motor at that speed
  drive(speedToPower());
}

//Takes the current speed and turns it into an argument for pulse width
//modulation that will drive the motor at that speed
int speedToPower(){
  
  float secondsPerRevolution = 1/currentSpeed;
  
  float outputVoltage = 0.0002f*secondsPerRevolution*secondsPerRevolution - 0.0528f*secondsPerRevolution + 6.7595f;
    
  if(outputVoltage <= 4.2){
    return ceil(outputVoltage/4.2f*255.0f);
  }
  else{
    return PWMON;
  }
}

//Calculates the angular velocity of the motor that is necessary to keep
//Constant angular velocity
void calcSpeed(float deltaT){
  
  //Find the approximate change in distance over the past cycle
  float deltaX = currentSpeed*deltaT/1000;
  
  //Update the current distance and angle
  currentDistance += deltaX;
  currentAngle -= EARTHROTATION*deltaT/1000;
  
  //Find the necessary linear velocity for the current position
  float linearVelocity = (-currentDistance * LENGTHA * sin(currentAngle))/(currentDistance - cos(currentAngle)) * EARTHROTATION;
   
  //Outputs currentSpeed in revolutions per second 
  currentSpeed = linearVelocity * THREADDENSITY * METERSTOINCHES;
 }

