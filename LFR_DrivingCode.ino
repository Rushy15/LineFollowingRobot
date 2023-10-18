
#define MOTOR1 12
#define MOTOR2 13

#define SENSOR1 14
#define SENSOR2 15
#define SENSOR3 16
#define SENSOR4 17
#define SENSOR5 18

#define LED_BLUE 2
#define LED_RED 4

#define L 30
#define M 50
#define H 90
#define ADD_L 0
#define ADD_R 10

static bool sensors[] = {SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5};


void setup() {
  // put your setup code here, to run once:
  // Motor Initialisation
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);

  // Sensor Initialisation
  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(SENSOR3, INPUT);
  pinMode(SENSOR4, INPUT);
  pinMode(SENSOR5, INPUT);

  // LED Initialisation
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  //Serial.begin(9600);
}


void loop(void) {
  // put your main code here, to run repeatedly:
  // for (int i = 0; i < 5; i++) {
  //   int data = digitalRead(sensors[i]);
  //   Serial.print(data);
  //   Serial.print("\t");
  // }

  // int data = digitalRead(sensors[3]);
  // Serial.print(data);
  // Serial.print("\t");


  // Motor Driving
//----------------------------------
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_RED, LOW);

  int s1 = digitalRead(SENSOR1);
  int s2 = digitalRead(SENSOR2);
  int s3 = digitalRead(SENSOR3);
  int s4 = digitalRead(SENSOR4);
  int s5 = digitalRead(SENSOR5);

  if (!s2 && !s3) {
    // Middle and Left Inner
    analogWrite(MOTOR1, H + ADD_L);
    analogWrite(MOTOR2, M + ADD_R);
  } else if (!s3 && !s4) {
    // Middle and Right Inner
    analogWrite(MOTOR1, M + ADD_L);
    analogWrite(MOTOR2, H + + ADD_R);
  }  else if (!s1 && !s2) {
    // Far Left and Inner Left
    analogWrite(MOTOR1, M + ADD_L);
    analogWrite(MOTOR2, L + ADD_R);
  }  else if (!s4 && !s5) {
    // Far Right and Inner Right
    analogWrite(MOTOR1, L + ADD_L);
    analogWrite(MOTOR2, M + ADD_R);
  }  else if (!s1) {
    // Far Left Only
    analogWrite(MOTOR1, H + ADD_L);
    analogWrite(MOTOR2, L + ADD_R);
  }  else if (!s5) {
    // Far Right Only
    analogWrite(MOTOR1, L + ADD_L);
    analogWrite(MOTOR2, H + ADD_R);
  }   else if (!s3) {
    // Middle Sensor Only
    analogWrite(MOTOR1, H + ADD_L);
    analogWrite(MOTOR2, H + ADD_R);    
  } else {
    // No Line Detected
    analogWrite(MOTOR1, H + ADD_L);
    analogWrite(MOTOR2, H + ADD_R);
  }
  
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, HIGH);
}
