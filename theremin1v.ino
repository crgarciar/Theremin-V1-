#include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define TONE_PIN 8    // Keep Buzzer on Pin 8
#define BUTTON_PIN 2  // MOVE BUTTON TO PIN 2

SR04 sr04(ECHO_PIN, TRIG_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
}

void loop() {
  long distance = sr04.Distance();
  long cleanDistance = constrain(distance, 2, 60);

  if (distance > 60 || distance <= 0) {
    noTone(TONE_PIN);
  } else {
    int frequency;
    
    // Check the button to decide the "Octave" or Range
    if (digitalRead(BUTTON_PIN) == HIGH) {
      // Range 1: Lower frequencies (200 - 1000 Hz)
      frequency = map(cleanDistance, 2, 60, 200, 1000); 
    } else {
      // Range 2: Higher frequencies (1001 - 1800 Hz)
      frequency = map(cleanDistance, 2, 60, 1001, 1800);
    }

    tone(TONE_PIN, frequency);
    
    Serial.print("Dist: ");
    Serial.print(cleanDistance);
    Serial.print(" cm | Freq: ");
    Serial.println(frequency);
  }

  delay(50); 
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

