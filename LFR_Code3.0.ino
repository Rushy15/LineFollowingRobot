
#define MOTOR1 12
#define MOTOR2 13

#define SENSOR1 14
#define SENSOR2 15
#define SENSOR3 16
#define SENSOR4 17
#define SENSOR5 18

#define LED_BLUE 2
#define LED_RED 4

#define H 200

#define M  H
#define A  H * 0.95
#define MI H * 0.70                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
#define I  H * 0.30
#define FI H * 0.20
#define F  H * 0.10

#define kd 0.00012
//#define ki

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

  Serial.begin(9600);
}


void loop(void) {
  // Motor Driving
//----------------------------------
  // digitalWrite(LED_BLUE, HIGH);
  // digitalWrite(LED_RED, LOW);
  int s1 = !digitalRead(SENSOR1);
  int s2 = !digitalRead(SENSOR2);
  int s3 = !digitalRead(SENSOR3);
  int s4 = !digitalRead(SENSOR4);
  int s5 = !digitalRead(SENSOR5);

  int effortLeft;
  int effortRight;

  int effortLeft_d; 
  int effortRight_d;

  int startTime = millis();

  if (s1 && s2 && s3) {
    // all left
    effortLeft = A;
    effortRight = M;
  } else if (s3 && s4 && s5) {
    // all right
    effortLeft = M;
    effortRight = A;
  } else if (s2 && s3) {
    // middle and inner left
    effortLeft = MI;
    effortRight = M;   
  } else if (s3 && s4) {
    // middle and inner right
    effortLeft = M;
    effortRight = MI;
  } else if (s1 && s2) {
    // inner left and far left
    effortLeft = FI;
    effortRight = M;
    direction = 0;
  } else if (s4 && s5) {
    // inner right and far right
    effortLeft = M;
    effortRight = FI;
    direction = 0;
  } else if (s3) {
    // middle only
    effortLeft = M;
    effortRight = M;
  } else if (s2) {
    // inner left only
    effortLeft = I;
    effortRight = M;
    direction = 1;
  } else if (s4) {
    // inner right only
    effortLeft = M;
    effortRight = I;
    direction = 0;
  } else if (s1) {
    // far left only
    effortLeft = F;
    effortRight = M;
    direction = 1;
  } else if (s5) {
    // far right only
    startTime = millis();
    effortLeft = M;
    effortRight = F;
    direction = 0;
  } else {
    // No line detection
    if (direction) {
      effortLeft = 0;
      effortRight = M;
    } else if (!direction) {
      effortLeft = M;
      effortRight = 0;
    }
  }
  int endTime = millis();


  if (effortLeft == M || effortRight == M) {
    effortLeft_d = (effortLeft / (endTime - startTime)) * kd;
    effortRight_d = (effortRight / (endTime - startTime)) * kd; 
  } else {
    effortLeft_d = 0;
    effortRight_d = 0; 
  }
  
  analogWrite(MOTOR1, effortLeft + effortLeft_d);
  analogWrite(MOTOR2, effortRight + effortRight_d);
  
  // digitalWrite(LED_BLUE, LOW);
  // digitalWrite(LED_RED, HIGH);
}
