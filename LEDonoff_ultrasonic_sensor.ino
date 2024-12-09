#include <Servo.h>

Servo myServo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 7;
const int distanceThreshold = 20; // Distance in cm to trigger the servo
const int delayBetweenStates = 1000; // 1 second delay

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.write(0); // Initial position of the servo at 0 degrees
}

void loop() {
  long duration, distance;

  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distance = (duration * 0.034) / 2; // Convert to cm
  
  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Check if a hand is detected within the threshold
  if (distance < distanceThreshold && distance > 0) { 
    myServo.write(90); // Move servo to 75 degrees
    delay(delayBetweenStates); // Stay at 75 degrees for 1 second
  } else {
    myServo.write(0); // Move servo back to 0 degrees
  }
  
  delay(100); // Small delay for stability
}
