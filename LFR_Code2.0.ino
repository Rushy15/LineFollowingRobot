
#define MOTOR1 12
#define MOTOR2 13

#define SENSOR1 14
#define SENSOR2 15
#define SENSOR3 16
#define SENSOR4 17
#define SENSOR5 18

#define LED_BLUE 2
#define LED_RED 4

#define H 65

#define M  H
#define A  H * 0.90
#define MI H * 0.80
#define I  H * 0.50
#define FI H * 0.35
#define F  H * 0.20

// left = 1, right = 0
static bool direction = NULL;

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

  int s1 = !digitalRead(SENSOR1);
  int s2 = !digitalRead(SENSOR2);
  int s3 = !digitalRead(SENSOR3);
  int s4 = !digitalRead(SENSOR4);
  int s5 = !digitalRead(SENSOR5);

  if (s1 && s2 && s3) {
    // all left
    analogWrite(MOTOR1, A);
    analogWrite(MOTOR2, M);
  } else if (s3 && s4 && s5) {
    // all right
    analogWrite(MOTOR1, M);
    analogWrite(MOTOR2, A);
  } else if (s2 && s3) {
    // middle and inner left
    analogWrite(MOTOR1, MI);
    analogWrite(MOTOR2, M);    
  } else if (s3 && s4) {
    // middle and inner right
    analogWrite(MOTOR1, M);
    analogWrite(MOTOR2, MI);
  } else if (s1 && s2) {
    // inner left and far left
    analogWrite(MOTOR1, FI);
    analogWrite(MOTOR2, M);
  } else if (s4 && s5) {
    // inner right and far right
    analogWrite(MOTOR1, M);
    analogWrite(MOTOR2, FI);
  } else if (s3) {
    // middle only
    analogWrite(MOTOR1, M);
    analogWrite(MOTOR2, M);    
  } else if (s2) {
    // inner left only
    analogWrite(MOTOR1, I);
    analogWrite(MOTOR2, M);
  } else if (s4) {
    // inner right only
    analogWrite(MOTOR1, M);
    analogWrite(MOTOR2, I);
  } else if (s1) {
    // far left only
    analogWrite(MOTOR1, F);
    analogWrite(MOTOR2, M);
    direction = 1;
    
  } else if (s5) {
    // far right only
    analogWrite(MOTOR1, M);
    analogWrite(MOTOR2, F);
    direction = 0;
  } else {
    // No line detection
    // analogWrite(MOTOR1, 0);
    // analogWrite(MOTOR2, 0); 
    if (direction) {
      analogWrite(MOTOR1, 0);
      analogWrite(MOTOR2, M);
    } else if (!direction) {
      analogWrite(MOTOR1, M);
      analogWrite(MOTOR2, 0);
    }
  }
  
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, HIGH);
}





