#include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define TONE_PIN 8
#define BUTTON_PIN 2

SR04 sr04(ECHO_PIN, TRIG_PIN);

// --- MOVING AVERAGE FILTER SETUP ---
const int numReadings = 20;     // Number of inputs to average
long readings[numReadings];      // The history array
int readIndex = 0;              // The index of the current reading
long total = 0;                  // The running total
long averageDistance = 0;        // The final filtered result

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initialize all readings to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // 1. Subtract the oldest reading from the total
  total = total - readings[readIndex];
  
  // 2. Read from the sensor
  long currentDist = sr04.Distance();
  
  // 3. Simple error handling: if sensor misses, don't add 0 to the average
  if (currentDist > 0 && currentDist < 200) {
    readings[readIndex] = currentDist;
  }
  
  // 4. Add the new reading to the total
  total = total + readings[readIndex];
  
  // 5. Advance to the next position in the array
  readIndex = readIndex + 1;

  // 6. If we're at the end of the array, wrap around to the beginning
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // 7. Calculate the average
  averageDistance = total / numReadings;

  // --- LOGIC USING THE SMOOTHED AVERAGE ---
  if (averageDistance > 60 || averageDistance <= 0) {
    noTone(TONE_PIN);
  } else {
    long cleanDistance = constrain(averageDistance, 2, 60);
    int frequency;

    if (digitalRead(BUTTON_PIN) == LOW) {
      frequency = map(cleanDistance, 2, 60, 200, 1000); 
    } else {
      frequency = map(cleanDistance, 2, 60, 1001, 1800);
    }

    tone(TONE_PIN, frequency);
    
    Serial.print("Smoothed Dist: ");
    Serial.println(averageDistance);
  }
}


/*
#include "SR04.h"
#include "pitches.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define TONE_PIN 8

SR04 sr04(ECHO_PIN, TRIG_PIN);

int duration = 300;

void setup() {
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  long distance = sr04.Distance();

  Serial.print("Distance: ");
  Serial.println(distance);

  // Convert distance into a zone number
  int zone = -1;

  if (distance > 1 && distance < 7)       zone = 0;
  else if (distance < 14)                  zone = 1;
  else if (distance < 21)                  zone = 2;
  else if (distance < 28)                  zone = 3;
  else if (distance < 35)                  zone = 4;
  else if (distance < 42)                  zone = 5;
  else if (distance < 50)                  zone = 6;
  else if (distance < 57)                  zone = 7;

  // Play note based on zone
  switch (zone) {

    case 0:
      Serial.println("C5");
      tone(TONE_PIN, NOTE_C5, duration);
      break;

    case 1:
      Serial.println("D5");
      tone(TONE_PIN, NOTE_D5, duration);
      break;

    case 2:
      Serial.println("E5");
      tone(TONE_PIN, NOTE_E5, duration);
      break;

    case 3:
      Serial.println("F5");
      tone(TONE_PIN, NOTE_F5, duration);
      break;

    case 4:
      Serial.println("G5");
      tone(TONE_PIN, NOTE_G5, duration);
      break;

    case 5:
      Serial.println("A5");
      tone(TONE_PIN, NOTE_A5, duration);
      break;

    case 6:
      Serial.println("B5");
      tone(TONE_PIN, NOTE_B5, duration);
      break;

    case 7:
      Serial.println("C6");
      tone(TONE_PIN, NOTE_C6, duration);
      break;

    default:
      Serial.println("No note");
      noTone(TONE_PIN);
      break;
  }

  delay(250);
}*\

/*   
    Ultrasonic distance calibration sketch
     #include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 11

SR04 sr04(ECHO_PIN, TRIG_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("Ultrasonic distance calibration");
  Serial.println("Move your hand slowly and read values in cm");
  delay(1000);
}

void loop() {
  long distance = sr04.Distance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(200);   // slow enough to read, fast enough to be responsive
}
    */

