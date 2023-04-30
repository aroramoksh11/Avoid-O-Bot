// Pin definitions
const int trigPin = 9;    // Trigger pin for the ultrasonic sensor
const int echoPin = 10;   // Echo pin for the ultrasonic sensor
const int motor1Pin = 3;  // Pin for motor 1
const int motor2Pin = 5;  // Pin for motor 2

// Distance threshold in cm
const int distanceThreshold = 20;

// Motor speed
const int motorSpeed = 200;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
}

void loop() {
  // Send a 10 microsecond pulse to the ultrasonic sensor to trigger a reading
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse, which is proportional to the distance
  int duration = pulseIn(echoPin, HIGH);

  // Convert the duration to distance in cm
  int distance = duration / 58;

  // Print the distance to the serial monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an obstacle is detected within the threshold distance, stop and turn
  if (distance < distanceThreshold) {
    // Stop the motors
    analogWrite(motor1Pin, 0);
    analogWrite(motor2Pin, 0);

    // Turn left by reversing one motor
    analogWrite(motor1Pin, motorSpeed);
    delay(1000);

    // Resume forward motion
    analogWrite(motor1Pin, motorSpeed);
    analogWrite(motor2Pin, motorSpeed);
  }
  // Otherwise, continue moving forward direction 
  else {
    analogWrite(motor1Pin, motorSpeed);
    analogWrite(motor2Pin, motorSpeed);
  }
}
