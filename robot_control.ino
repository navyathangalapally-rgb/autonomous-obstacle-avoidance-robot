// Motor and control pin definitions
int speed_A = 6;   // enA
int in_A1 = 5;     // in1
int in_A2 = 4;     // in2
int in_B1 = 7;     // in3
int in_B2 = 8;     // in4
int speed_B = 3;   // enB

// Speed sensor analog inputs
const int IN_A0 = A2; // Speed sensor analog input for motor A
const int IN_D0 = A1; // Speed sensor digital input
const int IN_A1 = A5; // Speed sensor analog input for motor B
const int IN_D1 = A4; // Speed sensor digital input

// Ultrasonic sensor pins
const int trigPin1 = 9;  // Trigger pin for ultrasonic sensor 1
const int echoPin1 = 10;  // Echo pin for ultrasonic sensor 1
const int trigPin2 = 13; // Trigger pin for ultrasonic sensor 2
const int echoPin2 = 12; // Echo pin for ultrasonic sensor 2

// IR Sensor Pin
const int IR_SENSOR = A0; // Analog input pin for IR sensor

// Variables for speed calculation
int speedpin1 = A1;
int speedpin2 = A3;
float turntime_A;            // Time for one turning step for Motor A
float turntime_B;            // Time for one turning step for Motor B
float speedleft1;            // Speed in RPM for Motor A
float speedleft2;            // Speed in RPM for Motor B

// Ultrasonic sensor variables
long duration1, duration2;
int distance1, distance2;

// IR sensor threshold
const int BLACK_THRESHOLD = 500; // Adjust based on sensor calibration

void setup() {
  // Set motor pins as outputs
  pinMode(speed_A, OUTPUT);
  pinMode(in_A1, OUTPUT);
  pinMode(in_A2, OUTPUT);
  pinMode(speed_B, OUTPUT);
  pinMode(in_B1, OUTPUT);
  pinMode(in_B2, OUTPUT);

  // Initialize motor speed to low
  digitalWrite(speed_A, LOW);
  digitalWrite(speed_B, LOW);

  // Set ultrasonic sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Set IR sensor pin
  pinMode(IR_SENSOR, INPUT);

  // Initialize serial communication
  Serial.begin(9600);

  // Set sensor pins as inputs
  pinMode(IN_A0, INPUT);
  pinMode(IN_D0, INPUT);
  pinMode(IN_A1, INPUT);
  pinMode(IN_D1, INPUT);
  pinMode(speedpin1, INPUT);
  pinMode(speedpin2, INPUT);
}

void loop() {
  // Measure distances using ultrasonic sensors
  distance1 = measureDistance(trigPin1, echoPin1);
  distance2 = measureDistance(trigPin2, echoPin2);

  // Check IR sensor for black line detection
  int irValue = analogRead(IR_SENSOR);
  if (irValue > BLACK_THRESHOLD) { // Black line detected
    Serial.println("Black line detected! Stopping the robot.");
    stopMotors(); // Stop both motors
    delay(1000);  // Wait for 1 second
    return;       // Skip further actions in this loop iteration
  }

  // Check for obstacles
  if (distance1 < 20) { // Object detected by sensor 1
  
    Serial.println("Obstacle detected by sensor 1!");
    stopMotorA();     // Stop Motor A
    rotateMotorB();   // Rotate Motor B to change direction
  } else if (distance2 < 20) { // Object detected by sensor 2
    Serial.println("Obstacle detected by sensor 2!");
    stopMotorB();     // Stop Motor B
    rotateMotorA();   // Rotate Motor A to change direction
  } else {
    // Driving forward
    digitalWrite(in_A1, HIGH);
    digitalWrite(in_A2, LOW);
    digitalWrite(in_B1, LOW);
    digitalWrite(in_B2, HIGH);
    analogWrite(speed_A, 127);  // Adjust speed as needed
    analogWrite(speed_B, 127);  // Adjust speed as needed
  }

  delay(100); // Short delay to avoid rapid sensor polling
}

// Function to measure distance using an ultrasonic sensor
int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; // Convert to distance in cm
  return distance;
}

// Function to stop all motors
void stopMotors() {
  digitalWrite(in_A1, LOW);
  digitalWrite(in_A2, LOW);
  digitalWrite(in_B1, LOW);
  digitalWrite(in_B2, LOW);
  analogWrite(speed_A, 0);
  analogWrite(speed_B, 0);
}

// Function to stop Motor A
void stopMotorA() {
  digitalWrite(in_A1, LOW);
  digitalWrite(in_A2, LOW);
  analogWrite(speed_A, 0);
}

// Function to stop Motor B
void stopMotorB() {
  digitalWrite(in_B1, LOW);
  digitalWrite(in_B2, LOW);
  analogWrite(speed_B, 0);
}

// Function to rotate Motor A for changing direction
void rotateMotorA() {
  digitalWrite(in_A1, LOW);
  digitalWrite(in_A2, HIGH);
  analogWrite(speed_A, 125); // Rotate Motor A
  delay(500);               // Adjust delay for rotation
  stopMotorA();             // Stop after rotation
}

// Function to rotate Motor B for changing direction
void rotateMotorB() {
  digitalWrite(in_B1, LOW);
  digitalWrite(in_B2, HIGH);
  analogWrite(speed_B, 125); // Rotate Motor B
  delay(500);               // Adjust delay for rotation
  stopMotorB();             // Stop after rotation
}
