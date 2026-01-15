
// --- Ultrasonic sensor pins ---
#define S1Trig 2   // Rear-Center (main sensor for following)
#define S1Echo 3
#define S2Trig 7   // Rear-Right
#define S2Echo 8
#define S3Trig 9   // Rear-Left
#define S3Echo 10

// --- Motor control pins ---
#define LEFT_MOTOR_PIN1 11
#define LEFT_MOTOR_PIN2 12
#define RIGHT_MOTOR_PIN1 13
#define RIGHT_MOTOR_PIN2 4
#define ENA 5
#define ENB 6

// --- Parameters ---
#define MAX_DISTANCE 50
#define BASE_SPEED 200
#define MIN_CURVE 20
#define MAX_CURVE 100

void setup() {
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(S1Trig, OUTPUT); pinMode(S1Echo, INPUT);
  pinMode(S2Trig, OUTPUT); pinMode(S2Echo, INPUT);
  pinMode(S3Trig, OUTPUT); pinMode(S3Echo, INPUT);

  Serial.begin(9600);
}

// --- Read distance ---
int readDistance(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 20000);
  if(duration==0) return 999;
  return duration / 29 / 2;
}

// --- Stop ---
void stopMotors() {
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  digitalWrite(LEFT_MOTOR_PIN1,LOW);
  digitalWrite(LEFT_MOTOR_PIN2,LOW);
  digitalWrite(RIGHT_MOTOR_PIN1,LOW);
  digitalWrite(RIGHT_MOTOR_PIN2,LOW);
}

// --- Move forward with optional curve ---
void moveForward(int leftSpeed, int rightSpeed){
  digitalWrite(LEFT_MOTOR_PIN1,LOW);
  digitalWrite(LEFT_MOTOR_PIN2,HIGH);
  digitalWrite(RIGHT_MOTOR_PIN1,HIGH);
  digitalWrite(RIGHT_MOTOR_PIN2,LOW);

  analogWrite(ENA,leftSpeed);
  analogWrite(ENB,rightSpeed);
}

void loop() {
  int front  = readDistance(S1Trig,S1Echo);
  int right  = readDistance(S2Trig,S2Echo);
  int left   = readDistance(S3Trig,S3Echo);

  Serial.print("Front:"); Serial.print(front);
  Serial.print(" Left:"); Serial.print(left);
  Serial.print(" Right:"); Serial.println(right);

  // No object detected
  if(front>MAX_DISTANCE && left>MAX_DISTANCE && right>MAX_DISTANCE){
    stopMotors();
    Serial.println("No object → Stop");
    return;
  }

  // Object detected by front sensor → move straight
  if(front <= MAX_DISTANCE){
    moveForward(BASE_SPEED, BASE_SPEED);
    Serial.println("Front aligned → Straight");
    return;
  }

  // Object on left only → curve left until front sees it
  if(left <= MAX_DISTANCE && left < right){
    int diff = right - left;
    int adjust = map(diff, 0, MAX_DISTANCE, MIN_CURVE, MAX_CURVE);
    adjust = constrain(adjust, MIN_CURVE, BASE_SPEED-50);
    moveForward(BASE_SPEED, BASE_SPEED - adjust);  // **slow right motor to curve left**
    Serial.println("Object left → Dynamic curve left");
    return;
  }

  // Object on right only → curve right until front sees it
  if(right <= MAX_DISTANCE && right < left){
    int diff = left - right;
    int adjust = map(diff, 0, MAX_DISTANCE, MIN_CURVE, MAX_CURVE);
    adjust = constrain(adjust, MIN_CURVE, BASE_SPEED-50);
    moveForward(BASE_SPEED - adjust, BASE_SPEED); // **slow left motor to curve right**
    Serial.println("Object right → Dynamic curve right");
    return;
  }

  // Safety fallback
  moveForward(BASE_SPEED, BASE_SPEED);
  Serial.println("Fallback → Move forward");
}