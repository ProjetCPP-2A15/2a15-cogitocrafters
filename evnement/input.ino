// Define pin numbers for the HC-SR04 sensor
const int trigPin = 9;
const int echoPin = 10;

// Define pin numbers for the RGB LED
const int pinRed = 5;    // Red Pin
const int pinGreen = 6;  // Green Pin
const int pinBlue = 3;   // Blue Pin

char data;
int prog = 0;

// Variables to store the duration of the echo pulse and the calculated distance
long duration;
int distance;

// Safety distance threshold in centimeters
const int safetyDistance = 5;

// Variables to store the last time distance was printed
unsigned long lastPrintTime = 0;
// Interval between distance readings (in milliseconds)
const unsigned long printInterval = 500;  // 500 milliseconds for more frequent updates

void setup() {
  // Initialize the trigPin as an output and the echoPin as an input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize RGB LED pins as outputs
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);

  // Start serial communication at 115200 baud rate
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    data = Serial.read();
    if (data == '1') {
      prog = 1;
    } else if (data == '2') {
      prog = 0;
    }
  }

  if (prog == 1) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echoPin; pulseIn returns the duration in microseconds
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    if (distance <= safetyDistance) {
      setColor(255, 0, 0); // Red for close distance
    } else if (distance <= 10) {
      setColor(0, 0, 255); // Blue for medium distance
    } else {
      setColor(0, 255, 0); // Green for safe distance
    }

    if (millis() - lastPrintTime >= printInterval) {
      Serial.println(distance);
      lastPrintTime = millis();
    }
  } else {
    setColor(0, 0, 0); // Turn off RGB LED
  }

  delay(100);
}

void setColor(int red, int green, int blue) {
  analogWrite(pinRed, red);
  analogWrite(pinGreen, green);
  analogWrite(pinBlue, blue);
}
