//Hill Balliet
//26 April 2015

//initialize motor pins
#define PLUS 9
#define MINUS 8
#define EN 6

//magic numbers
#define ANALOGHIGH 255

void initMotors(){
  pinMode(PLUS, OUTPUT);
  pinMode(MINUS, OUTPUT);
  pinMode(EN, OUTPUT);
}

void motorEn(int en){
  analogWrite(EN, en);
}

void halt(){
  digitalWrite(PLUS, LOW);
  digitalWrite(MINUS, LOW);
}

void drive(int enable){
  motorEn(enable);
  digitalWrite(PLUS, HIGH);
  digitalWrite(MINUS, LOW);
}
