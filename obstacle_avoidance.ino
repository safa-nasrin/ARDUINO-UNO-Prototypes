// --- Ultrasonic sensor pins ---
#define S1Trig 2   // Front
#define S1Echo 3
#define S2Trig 7   // Right
#define S2Echo 8
#define S3Trig 9   // Left
#define S3Echo 10

// --- Motor control pins ---
#define LEFT_MOTOR_PIN1 11   // IN1
#define LEFT_MOTOR_PIN2 12   // IN2
#define RIGHT_MOTOR_PIN1 13  // IN3
#define RIGHT_MOTOR_PIN2 4   // IN4
#define ENA 5   // PWM Left Motor
#define ENB 6   // PWM Right Motor

// --- Parameters ---
#define MAX_DISTANCE 40       // Obstacle detection range in cm
#define MAX_SPEED 255         // Motor speed (0-255)

void setup() {
  // Motor pins
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic pins
  pinMode(S1Trig, OUTPUT);
  pinMode(S1Echo, INPUT);
  pinMode(S2Trig, OUTPUT);
  pinMode(S2Echo, INPUT);
  pinMode(S3Trig, OUTPUT);
  pinMode(S3Echo, INPUT);

  Serial.begin(9600);
}

void loop() {
  int frontDistance = sensorOne();
  int rightDistance = sensorTwo();   
  int leftDistance = sensorThree();  

  Serial.print("Front: "); Serial.print(frontDistance);
  Serial.print(" cm, Left: "); Serial.print(leftDistance);
  Serial.print(" cm, Right: "); Serial.print(rightDistance);
  Serial.println(" cm");

  // --- Continuous Obstacle Avoidance Logic ---
  if (frontDistance > 0 && frontDistance < MAX_DISTANCE) {
    // Obstacle ahead → check which side is clearer
    if (leftDistance > rightDistance) {
      moveLeft();
      Serial.println("Obstacle ahead → turning LEFT");
    } else if (rightDistance > leftDistance) {
      moveRight();
      Serial.println("Obstacle ahead → turning RIGHT");
    } else {
      moveBackward();
      Serial.println("All sides blocked → moving BACKWARD");
      delay(300);
    }
  }
  else if (leftDistance > 0 && leftDistance < MAX_DISTANCE) {
    moveRight();
    Serial.println("Obstacle on LEFT → turning RIGHT");
  }
  else if (rightDistance > 0 && rightDistance < MAX_DISTANCE) {
    moveLeft();
    Serial.println("Obstacle on RIGHT → turning LEFT");
  }
  else {
    moveForward();
    Serial.println("Path clear → moving FORWARD");
  }

  delay(100);
}

// --- Ultrasonic sensor functions ---
int sensorOne() {
  digitalWrite(S1Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(S1Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S1Trig, LOW);
  long t = pulseIn(S1Echo, HIGH, 20000);
  if (t == 0) return -1;
  return t / 29 / 2;
}

int sensorTwo() {   
  digitalWrite(S2Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(S2Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S2Trig, LOW);
  long t = pulseIn(S2Echo, HIGH, 20000);
  if (t == 0) return -1;
  return t / 29 / 2;
}

int sensorThree() { 
  digitalWrite(S3Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(S3Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(S3Trig, LOW);
  long t = pulseIn(S3Echo, HIGH, 20000);
  if (t == 0) return -1;
  return t / 29 / 2;
}

// --- Motor control functions ---
void moveForward() {
  analogWrite(ENA, MAX_SPEED);
  analogWrite(ENB, MAX_SPEED);
  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  digitalWrite(LEFT_MOTOR_PIN2, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN1, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
}

void moveLeft() {
  analogWrite(ENA, MAX_SPEED/2);  
  analogWrite(ENB, MAX_SPEED);    
  digitalWrite(LEFT_MOTOR_PIN1, HIGH);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN2, HIGH);
}

void moveRight() {
  analogWrite(ENA, MAX_SPEED);     
  analogWrite(ENB, MAX_SPEED/2);   
  digitalWrite(LEFT_MOTOR_PIN1, HIGH);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN2, HIGH);
}

void moveBackward() {
  analogWrite(ENA, MAX_SPEED);
  analogWrite(ENB, MAX_SPEED);
  digitalWrite(LEFT_MOTOR_PIN1, HIGH);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, HIGH);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
}

void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
}